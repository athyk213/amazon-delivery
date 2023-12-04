#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

double TOL = 1e-10;

class Address {
private:
    int i, j;
    std::string Last_possible_delivery_date;
    bool prime_member;
public:
    // Constructor
    Address(int i, int j, std::string Last_possible_delivery_date = "No_Date" , bool prime_member = false) : i(i), j(j), Last_possible_delivery_date(Last_possible_delivery_date) , prime_member(prime_member) {}
    Address(){}; // why do we need this?
    double get_i() const {
        return i;
    }

    double get_j() const {
        return j;
    }

    // manhattan_distance and straight line mehtod
    double distance(const Address& additional_addresses, bool manhattan_distance = false) const {
        if (manhattan_distance) {
            return std::abs(i - additional_addresses.i) + std::abs(j - additional_addresses.j);
        } else {
            return std::sqrt(std::pow(i - additional_addresses.i, 2) + std::pow(j - additional_addresses.j, 2));
        }
    }

    // check if addresses are equal
    bool operator==(const Address& other) const {
        return i == other.get_i() && j == other.get_j();
    }

    // defined lexicographical order for addresses
    bool operator<(const Address& other) const {
        if (i == other.get_i()){
            return j < other.get_j();
        }
        else {
            return i < other.get_i();
        }

    }


    string as_string() const {
        stringstream ss;
        ss << "(" << i << ", " << j << ")";
        return ss.str();
    }

    bool is_prime_member() const {
        return prime_member;
    }
};

class AddressList{
    protected:
        std::vector<Address> address_list;
    public:

        virtual void add_address(Address address){
            // add address to address list
            address_list.push_back(address);
        };

        // Calculate the total distance to visit all addresses in order
        virtual double length(){
            double total_distance = 0.0;
            for (int i = 0; i < address_list.size() - 1; ++i) {
                total_distance += address_list[i].distance(address_list[i + 1]);
            }
            return total_distance;
        };

        // Find the index of the address in the list closest to the target_address
        Address index_closest_to(Address address) {
            double min_distance = INFINITY;
            Address closest_address;

            for (int i = 0; i < address_list.size(); ++i) {
                double current_distance = address.distance(address_list[i]);
                if (current_distance < min_distance) {
                    min_distance = current_distance;
                    closest_address = address_list[i];
                }
            }

            return closest_address;
        }

        string as_string() const {
            std::stringstream ss;

            for (const auto& addr : address_list) {
                ss << addr.as_string() << " ";
            }

            return ss.str();
        }
};


class Route: public AddressList{
    public:
        Route(){
            address_list.push_back(Address(0,0));
            address_list.push_back(Address(0,0));
        }

        Route(vector<Address> addresses){
            address_list.push_back(Address(0,0));
            address_list.push_back(Address(0,0));
            for (int i = 0; i < addresses.size(); i++){
                add_address(addresses[i]);
            }
        }

        void add_address(Address address) override {
            // Ensure the address is not already in the list
            for (const auto& addr : address_list) {
                if (addr == address) {
                    return;
                }
            }

            // Keep first and last element the same
            address_list.insert(address_list.begin() + address_list.size() - 1, address);
        }

        // construct a greedy route based on the next closest address
        Route greedy_route() {

            // initialize a new route starting at the depot
            Route new_route;
            Address current_address = address_list[0];

            // remove the last stop (the depot)
            address_list.pop_back();

            // continue until all addresses are visited
            // At the end address list will only contain the next address, which is added to new_route
            while (address_list.size() > 1) {

                // remove current_address from address_list
                // TODO find a cleaner way to do this
                for (int i = 0; i < address_list.size(); i++){
                    if (address_list[i] == current_address){
                        address_list.erase(address_list.begin()+i);
                        break;
                    }
                }

                // the next address in the route is the address closest to current
                Address next_address = index_closest_to(current_address);
                new_route.add_address(next_address);
                current_address = next_address;
            }
            return new_route;
        }
        // 2-opt heuristic
        void apply_2_opt() {

            bool improvement = true;

            while (improvement) {
                cout << "in apply_2_opt \n";
                improvement = false;

                for (size_t i = 1; i < address_list.size() - 2; ++i) {
                    for (size_t j = i + 1; j < address_list.size() - 1; ++j) {
                        // Check if the new connection is shorter
                        double delta_distance = address_list[i - 1].distance(address_list[j]) +
                                                address_list[i].distance(address_list[j + 1]) -
                                                address_list[i - 1].distance(address_list[i]) -
                                                address_list[j].distance(address_list[j + 1]);

                        cout << delta_distance << '\n';

                        if (delta_distance + TOL < 0) {
                            // If the new connection is shorter, reverse the portion of the tour
                            reverse(address_list.begin() + i, address_list.begin() + j + 1);
                            improvement = true;
                        }
                    }
                }
            }
        }
        
        // Returns the improvement for a potential swap
        // i_1, i_2: start and end indicies of 1 segement in rt1
        // j_1, j_2: start and end indicies of 1 segement in rt2
        // leaves the segements unswapped
        double swap_improvement(Route &rt2, int i_1, int i_2, int j_1, int j_2){
            Route rt1 = Route(*this);
            
            double initial_length = rt1.length() + rt2.length();

            // swap segements
            std::swap(rt1.address_list[i_1], rt2.address_list[j_1]);
            std::swap(rt1.address_list[i_2], rt2.address_list[j_2]);

            double improvement = initial_length - (rt1.length() + rt2.length());

            // swap back segements
            std::swap(rt1.address_list[i_1], rt2.address_list[j_1]);
            std::swap(rt1.address_list[i_2], rt2.address_list[j_2]);

            return improvement;
        }

        // Given the two segements in two routes, perform the action that maxmizes improvement
        // Checks all possible directions of tours
        // returns bool, True if swapping causes improvement, False if no swaps.
        bool do_best_swap(Route &rt2, int i_1, int i_2, int j_1, int j_2){
            Route rt1 = Route(*this);
            
            // Get the improvement for each potential swap direction
            vector<vector<int>> swaps_to_test = {
                {i_1,i_2,j_1,j_2}, 
                //{i_2,i_1,j_1,j_2},
                //{i_1,i_2,j_2,j_1},
                //{i_2,i_1,j_2,j_1}
            };
            
            vector<double> improvements;

            for (vector<int> potential_swap: swaps_to_test){
                int rt1_start = potential_swap[0];
                int rt1_end = potential_swap[1];
                int rt2_start = potential_swap[2];
                int rt2_end = potential_swap[3];
                double potential_improvement = swap_improvement(rt2, rt1_start,rt1_end,rt2_start,rt2_end);
                improvements.push_back(potential_improvement);
            }
            
            // perform the best action (maxmial improvement)
            auto max_improvement = std::max_element(improvements.begin(),improvements.end());

            // don't swap if there's no improvement
            if (*max_improvement <= 0 ){
                return false;
            }
            int maxIndex = std::distance(improvements.begin(), max_improvement);
            vector<int> best_swap = swaps_to_test[maxIndex];
            int rt1_start = best_swap[0];
            int rt1_end = best_swap[1];
            int rt2_start = best_swap[2];
            int rt2_end = best_swap[3];

            std::swap(rt1.address_list[rt1_start], rt2.address_list[rt2_start]);
            std::swap(rt1.address_list[rt1_end], rt2.address_list[rt2_end]);
            cout << "swapped between routes \n";
            return true;
        }

       // search through all possible routes
        void apply_total_search(){
            std::vector<Address> best_route = address_list; // Store the initial route as the best
            double best_length = length(); // Calculate its length

            // Copy the initial order of addresses for permutation
            std::vector<Address> original_order = address_list;

            // Find permutations and track the best route and length
            sort(address_list.begin() + 1, address_list.end() - 1);
            do {
                double test_length = length(); // Calculate the length for the current permutation

                if (test_length < best_length) {
                    best_length = test_length; // Update the best length
                    best_route = address_list; // Update the best route
                }

            } while (std::next_permutation(address_list.begin() + 1, address_list.end() - 1)); // Exclude the depot addresses

            // Update the address_list to the best route found
            address_list = best_route;
        }

        void save_routes(string file_name, Route &rt2) {
            // Open the file for writing
            std::ofstream file(file_name);

            // Check if the file is open
            if (!file.is_open()) {
                std::cerr << "Error opening file: " << file_name << std::endl;
                return;
            }

            // Write each address to the file
            for (const auto& addr : address_list) {
                file << addr.as_string() << std::endl;
            }

            for (const auto& addr : rt2.address_list) {
                file << addr.as_string() << std::endl;
            }

            // Close the file
            file.close();
        }

        // Check if any address is amazon prime
        bool has_prime_member(Address &rt1) const {
        for (const auto& addr : address_list) {
            if (addr.is_prime_member()) {
                return true;
            }
        }
        return false;
        }

        friend std::vector<Route> multi_path_apply_2_opt(Route &rt1, Route &rt2);
};

std::vector<Route> multi_path_apply_2_opt(Route &rt1, Route &rt2) {

    bool improvement = true;
    cout << "Now apply 2 opt between 2 routes (multi_path_apply_2_opt)\n";
    cout << "\tInitial Rt1: " << rt1.as_string() << '\n';
    cout << "\tInitial Rt2: " << rt2.as_string() << '\n';

    // Keep swapping segements until no more improvement is found
    while (improvement) {
        improvement = false;

        // select any two segements both routes
        for (size_t i = 1; i < rt1.address_list.size() - 2; ++i) {
            for (size_t j = 1; j < rt2.address_list.size() - 2; ++j){

                // Don't swap if any of the addresses are amazon prime (have to stay on the same route)
                if (rt1.address_list[i].is_prime_member() or
                    rt1.address_list[i+1].is_prime_member() or
                    rt2.address_list[j].is_prime_member() or
                    rt2.address_list[j+1].is_prime_member()){
                        continue;
                }

                double initial_length = rt1.length() + rt2.length();

                /////////////////////////////////////////////
                // try swapping segements - flip neither segment
                std::swap(rt1.address_list[i], rt2.address_list[j]);
                std::swap(rt1.address_list[i+1], rt2.address_list[j+1]);

                // keep the swap and flag improvement if swap decreases length
                if ((rt1.length() + rt2.length()) < initial_length){
                    improvement = true;
                }

                // otherwise swap back 
                else{
                    std::swap(rt1.address_list[i], rt2.address_list[j]);
                    std::swap(rt1.address_list[i+1], rt2.address_list[j+1]);
                    continue;
                }
                /////////////////////////////////////////////
                // try swapping segements - flip both segment
                std::swap(rt1.address_list[i], rt2.address_list[j+1]);
                std::swap(rt1.address_list[i+1], rt2.address_list[j]);

                // keep the swap and flag improvement if swap decreases length
                if ((rt1.length() + rt2.length()) < initial_length){
                    improvement = true;
                }

                // otherwise swap back
                else{
                    std::swap(rt1.address_list[i], rt2.address_list[j+1]);
                    std::swap(rt1.address_list[i+1], rt2.address_list[j]);
                    continue;
                }
                /////////////////////////////////////////////
                // try swapping segements - only 1 segment
                // swap route 1's segmenet
                std::swap(rt1.address_list[i],rt1.address_list[i+1]);

                // swap between route 1 and route 2
                std::swap(rt1.address_list[i], rt2.address_list[i+1]);
                std::swap(rt1.address_list[j], rt2.address_list[j+1]);

                // keep the swap and flag improvement if swap decreases length
                if ((rt1.length() + rt2.length()) < initial_length){
                    improvement = true;
                }

                // otherwise swap back: just apply the original swap procedures in reverse order
                else{
                    // swap addresses
                    std::swap(rt1.address_list[i], rt2.address_list[j+1]);
                    std::swap(rt1.address_list[i+1], rt2.address_list[j]);

                    // swap route 1's segmenet
                    std::swap(rt1.address_list[i],rt1.address_list[i+1]);
                    continue;
                }

                /////////////////////////////////////////////
                // try swapping segements - only 1 segment
                // swap route 2's segmenet
                std::swap(rt2.address_list[j],rt2.address_list[j+1]);

                // swap between route 1 and route 2
                std::swap(rt1.address_list[i], rt2.address_list[i+1]);
                std::swap(rt1.address_list[j], rt2.address_list[j+1]);

                // keep the swap and flag improvement if swap decreases length
                if ((rt1.length() + rt2.length()) < initial_length){
                    improvement = true;
                }

                // otherwise swap back: just apply the original swap procedures in reverse order
                else{
                    // swap addresses
                    std::swap(rt1.address_list[i], rt2.address_list[j+1]);
                    std::swap(rt1.address_list[i+1], rt2.address_list[j]);

                    // swap route 2's segmenet
                    std::swap(rt2.address_list[j],rt2.address_list[j+1]);
                    continue;
                }
            }
        }
    }
    cout << "\tFinal Rt1: " << rt1.as_string() << '\n';
    cout << "\tFinal Rt2: " << rt2.as_string() << '\n';
    return {rt1, rt2};
}


// 0)
// AB
// EF

// 1)
// BA
// EF swap(j, j+1)

// 2)
// EF
// BA
// swap(i,j) swap(i+1,j+1)



// -----------

// 0)
// AB
// EF

// 1) - swap one path
// AB swap(i, i+1)
// FE

// 1) - swap between addresses
// FE
// AB
// swap(i,j) swap(i+1,j+1)
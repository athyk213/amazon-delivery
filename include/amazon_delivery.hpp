#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class Address {
private:
    int i, j;
    std::string Last_possible_delivery_date;
public:
    // Constructor
    Address(int i, int j, std::string Last_possible_delivery_date = "No_Date") : i(i), j(j), Last_possible_delivery_date(Last_possible_delivery_date) {}
    Address(){}
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


        void save_route(string file_name) {
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

            // Close the file
            file.close();
        }
};


class Route: public AddressList {
    public:
        Route(){
            address_list.push_back(Address(0,0));
            address_list.push_back(Address(0,0));
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
                improvement = false;

                for (size_t i = 1; i < address_list.size() - 2; ++i) {
                    for (size_t j = i + 1; j < address_list.size() - 1; ++j) {
                        // Check if the new connection is shorter
                        double delta_distance = address_list[i - 1].distance(address_list[j]) +
                                                address_list[i].distance(address_list[j + 1]) -
                                                address_list[i - 1].distance(address_list[i]) -
                                                address_list[j].distance(address_list[j + 1]);

                        if (delta_distance < 0) {
                            // If the new connection is shorter, reverse the portion of the tour
                            reverse(address_list.begin() + i, address_list.begin() + j + 1);
                            improvement = true;
                        }
                    }
                }
            }
        }

        // Multiple trucks
        std::vector<Route> multi_path_apply_2_opt(Route &rt2) {
            Route rt1 = Route(*this);
            rt1.apply_2_opt();
            rt2.apply_2_opt();
            double sum_lengths = rt1.length() + rt2.length();
            double curr_length = INFINITY;

            bool improvement = true;

            while (improvement) {
                improvement = false;

                for (size_t i = 1; i < rt1.address_list.size() - 2; ++i) {
                    // Check if the new connection is shorter
                    std::swap(rt1.address_list[i], rt2.address_list[i]);
                    std::swap(rt1.address_list[i + 1], rt2.address_list[i + 1]);

                    // Calculate the current length
                    curr_length = rt1.length() + rt2.length();

                    // Check if the current length is better than the sum of lengths
                    if (curr_length < sum_lengths) {
                        sum_lengths = curr_length;
                        improvement = true;
                    } else {
                        // If not, swap elements back to the original state
                        std::swap(rt1.address_list[i], rt2.address_list[i]);
                        std::swap(rt1.address_list[i + 1], rt2.address_list[i + 1]);
                    }
                }
            }

            return {rt1, rt2};
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
};

// int main() {
//     // Create addresses
//     Address address1(1, 0, "2023-12-01");
//     Address address2(0, 1, "2023-12-02");
//     Address address3(1, 1, "2023-12-03");

//     // Create a Route
//     Route route;

//     // Add addresses to the route
//     route.add_address(address1);
//     route.add_address(address2);
//     route.add_address(address3);

//     // Display the initial route
//     std::cout << "Initial Route: " << route.as_string() << std::endl;

//     // Apply the 2-opt heuristic
//     route.apply_2_opt();

//     // Display the optimized route
//     std::cout << "Optimized Route: " << route.as_string() << std::endl;

//     return 0;
// }
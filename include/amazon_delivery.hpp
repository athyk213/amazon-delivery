#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <sstream>
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
    double distance(const Address& additional_addresses, bool manhattan_distance = true) const {
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

                
                cout << "curr: " << current_address.as_string() << ", next:" <<next_address.as_string() << '\n';
                
                current_address = next_address;
            }            
            return new_route;
        }

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
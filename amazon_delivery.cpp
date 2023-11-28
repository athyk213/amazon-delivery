#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

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
};

class Route:AddressList {
    public:
        void add_address(Address address) override {
            // Ensure the address is not already in the list
            for (const auto& addr : address_list) {
                if (addr == address) {
                    return;
                }
            }

            // Ensure the depot is not affected
            if (address_list.size() > 0) {
                address_list.insert(address_list.begin() + address_list.size() - 1, address);
            } else {
                address_list.push_back(address); // Add the first element (depot)
            }
        }
};

int main() {
    // Test Case 1: Add addresses to AddressList
    AddressList addressList;
    addressList.add_address(Address(1, 2, "2023-12-01"));
    addressList.add_address(Address(3, 4, "2023-12-02"));

    // Test Case 2: Calculate the total distance in AddressList
    std::cout << "Total distance in AddressList: " << addressList.length() << std::endl;

    // Test Case 3: Add addresses to Route
    Route route;
    route.add_address(Address(1, 2, "2023-12-01"));
    route.add_address(Address(3, 4, "2023-12-02"));

    // Test Case 4: Calculate the total distance in Route
    std::cout << "Total distance in Route: " << route.length() << std::endl;

    // Test Case 5: Add duplicate address to AddressList
    addressList.add_address(Address(1, 2, "2023-12-01")); // Adding a duplicate address

    // Test Case 6: Add duplicate address to Route
    route.add_address(Address(1, 2, "2023-12-01")); // Adding a duplicate address

    // Test Case 7: Find the closest address in AddressList
    Address targetAddress1(10, 10);
    Address closestAddress1 = addressList.index_closest_to(targetAddress1);
    std::cout << "Closest address in AddressList: (" << closestAddress1.get_i() << ", " << closestAddress1.get_j() << ")" << std::endl;

    // Test Case 8: Find the closest address in Route
    Address targetAddress2(10, 10);
    Address closestAddress2 = route.index_closest_to(targetAddress2);
    std::cout << "Closest address in Route: (" << closestAddress2.get_i() << ", " << closestAddress2.get_j() << ")" << std::endl;

    return 0;
}
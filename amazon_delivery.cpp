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
    private:
        std::vector<Address> address_list;
    public:
        
        void add_address(Address address){
            // Ensure the address is not already in the list
            for (const auto& addr : address_list) {
                if (addr == address) {
                    return;
                }
            }

            // add address to address list
            address_list.push_back(address);
        };

        // Calculate the total distance to visit all addresses in order
        double length(){
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

int main() {
    // Create addresses
    Address address1(1, 2, "2023-12-01");
    Address address2(3, 4, "2023-12-02");
    Address address3(5, 6, "2023-12-03");
    Address address4(7, 8, "2023-12-04");

    // Create an AddressList
    AddressList addressList;

    // Add addresses to the list
    addressList.add_address(address1);
    addressList.add_address(address2);
    addressList.add_address(address3);
    addressList.add_address(address4);

    // Calculate and print the total distance to visit all addresses in order
    std::cout << "Total distance: " << addressList.length() << std::endl;

    // Find the address closest to a target address
    Address targetAddress(10, 10);
    Address closestAddress = addressList.index_closest_to(targetAddress);

    std::cout << "Closest address to target: (" << closestAddress.get_i() << ", " << closestAddress.get_j() << ")" << std::endl;

    return 0;
}
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

    string get_address() const {
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
                ss << addr.get_address() << " ";
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

        Route greedy_route() {
        Route new_route;
        std::vector<Address> address_list_greedy;
        address_list_greedy = address_list;

        Address current_address = address_list_greedy[0];

        auto start = address_list_greedy.begin() + 1;
        auto end = address_list_greedy.begin() ;

        address_list_greedy.pop_back();

        
        //this goes to the closest then erases the index after
        while (address_list.size()-1 > 0) {
            address_list_greedy.erase(std::find(address_list_greedy.begin(),address_list_greedy.end(),current_address));
            Address next_address = index_closest_to(current_address);
            new_route.add_address(next_address);
            current_address = next_address;
        }

        new_route.address_list.push_back(address_list_greedy[0]);
        
        return new_route;
    }
};

int main() {
    Route route;
    route.add_address(Address(1, 2, "2023-12-01"));
    route.add_address(Address(3, 4, "2023-12-02"));
    route.add_address(Address(5, 6, "2023-12-02"));

    cout << route.as_string();

    // Test case 1
    Route route1;
    route1.add_address(Address(1, 2, "2023-12-01"));
    route1.add_address(Address(3, 4, "2023-12-02"));
    route1.add_address(Address(5, 6, "2023-12-02"));

    cout << "Original Route 1: " << route1.as_string() << endl;

    Route greedyRoute1 = route1.greedy_route();

    cout << "Greedy Route 1: " << greedyRoute1.as_string() << endl;
    cout << "Original Route 1 Length: " << route1.length() << endl;
    cout << "Greedy Route 1 Length: " << greedyRoute1.length() << endl;

    return 0;
}
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

class Address {
public:
    int i, j;
    std::string Last_possible_delivery_date;

    // Constructor
    Address(int i, int j, std::string Last_possible_delivery_date = "No_Date") : i(i), j(j), Last_possible_delivery_date(Last_possible_delivery_date) {}

    // manhattan_distance and straight line mehtod
    double distance(const Address& additional_addresses, bool manhattan_distance = true) const {
        if (manhattan_distance) {
            return std::abs(i - additional_addresses.i) + std::abs(j - additional_addresses.j);
        } else {
            return std::sqrt(std::pow(i - additional_addresses.i, 2) + std::pow(j - additional_addresses.j, 2));
        }
    }
};

class AddressList{
    private:
        std::vector<Address> address_list;
    public:
        
        void add_address(){};

        double length(){};

        Address index_closest_to(){};
};

int main() {

    // test code from chatgpt
    Address baseaddress(0,0, "2023-1-1");
    Address address1(2, 4, "2023-11-30");
    Address address2(6, 7, "2023-11-25");

    double manhattan_distance = baseaddress.distance(address1);
    double straight_line_distance = baseaddress.distance(address1, false);

    double manhattan_distance1 = baseaddress.distance(address2);
    double straight_line_distance1 = baseaddress.distance(address2, false);

    std::cout << "Manhattan Distance: " << manhattan_distance << std::endl;
    std::cout << "Straight-Line Distance: " << straight_line_distance << std::endl;
    std::cout << "Manhattan Distance: " << manhattan_distance1 << std::endl;
    std::cout << "Straight-Line Distance: " << straight_line_distance1 << std::endl;

    return 0;
};

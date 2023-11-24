#include <iostream>
#include <algorithm>
#include <cmath>

class Address {
public:
    int i, j;
    std::string Last_possible_delivery_date;

    // Constructor
    Address(int i, int j, std::string Last_possible_delivery_date) : i(i), j(j), Last_possible_delivery_date(Last_possible_delivery_date) {}

    // Distance calculation method
    double distance(const Address& additional_addresses, bool manhattan_distance = true) const {
        if (manhattan_distance) {
            return std::abs(i - additional_addresses.i) + std::abs(j - additional_addresses.j);
        } else {
            return std::sqrt(std::pow(i - additional_addresses.i, 2) + std::pow(j - additional_addresses.j, 2));
        }
    }
};

int main() {

    // test code from chatgpt
    Address address1(1, 2, "2023-11-30");
    Address address2(3, 5, "2023-11-25");

    double manhattan_distance = address1.distance(address2);
    double straight_line_distance = address1.distance(address2, false);

    std::cout << "Manhattan Distance: " << manhattan_distance << std::endl;
    std::cout << "Straight-Line Distance: " << straight_line_distance << std::endl;

    return 0;
};

#include "amazon_delivery.hpp"

int main() {
    // Create addresses
    Address address1(1, 0, "2023-12-01");
    Address address2(0, 1, "2023-12-02");
    Address address3(1, 1, "2023-12-03");

    // Create a Route
    Route route;

    // Add addresses to the route
    route.add_address(address1);
    route.add_address(address2);
    route.add_address(address3);

    // Display the initial route
    std::cout << "Initial Route: " << route.as_string() << std::endl;

    // Apply the 2-opt heuristic
    route.apply_2_opt();

    // Display the optimized route
    std::cout << "Optimized Route: " << route.as_string() << std::endl;

    return 0;
}
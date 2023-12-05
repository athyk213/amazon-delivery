#include "amazon_delivery.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>  // for rand function

// Function to generate a random address
Address generate_random_address() {
    int x = rand() % 10;  // Random x coordinate (adjust range as needed)
    int y = rand() % 10;  // Random y coordinate (adjust range as needed)
    return Address(x, y, "");
}

// Function to generate n random addresses and create a route
Route generate_random_route(int n) {
    Route route;
    for (int i = 0; i < n; ++i) {
        route.add_address(generate_random_address());
    }
    return route;
}

int main() {
    // Seed the random number generator
    srand(0);

    int n = 9;  // Adjust the number of random addresses as needed

    // Generate n random addresses and create a route
    Route rt1 = generate_random_route(n);

    Route rt2 = rt1;
    std::cout << "Initial Route: " << rt1.as_string() << std::endl;

    // Display the initial route and length
    std::cout << "Length of Initial Route: " << rt1.length() << std::endl;


    // Apply the 2-opt algorithm and display the route and length
    rt1.apply_2_opt();
    std::cout << "Length of 2-opt Optimized Route: " << rt1.length() << std::endl;
    std::cout << "Length of Copied Route: " << rt2.length() << std::endl;

    rt1 = generate_random_route(n);
    std::cout << "Initial Route: " << rt1.as_string() << std::endl;

    // Apply the total search algorithm and display the route and length
    rt1.apply_total_search();
    std::cout << "Length of Total Search Optimized Route: " << rt1.length() << std::endl;

    // Apply the greedy algorithm and display the route and length
    Route greedy_optimized_route = rt1.greedy_route();
    std::cout << "Length of Greedy Optimized Route: " << greedy_optimized_route.length() << std::endl;


    return 0;
}
#include "amazon_delivery.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// Function to generate a random address
Address generate_random_address() {
    double x = static_cast<double>(rand()) / RAND_MAX * 10.0;  // Random x coordinate in [0, 10)
    double y = static_cast<double>(rand()) / RAND_MAX * 10.0;  // Random y coordinate in [0, 10)
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

    int n = 10;  // Adjust the number of random addresses as needed

    // Generate n random addresses and create a route
    Route rt1 = generate_random_route(n);
    Route rt2 = rt1;
    Route rt3 = rt1;
    std::cout << "Initial Route: " << rt1.as_string() << std::endl;

    // Display the initial route and length
    std::cout << "Length of Initial Route: " << rt1.length() << std::endl;

    rt1.save_route("../saved_routes/initial_route.txt");
    
    // Apply the greedy algorithm and display the route and length
    Route greedy_optimized_route = rt1.greedy_route();
    std::cout << "Length of Greedy Optimized Route: " << greedy_optimized_route.length() << std::endl;

    greedy_optimized_route.save_route("../saved_routes/greedy_route.txt");

    // Apply the 2-opt algorithm and display the route and length
    rt2.apply_2_opt();
    std::cout << "Length of 2-opt Optimized Route: " << rt2.length() << std::endl;

    // Apply the total search algorithm and display the route and length
    rt3.apply_total_search();
    std::cout << "Length of Total Search Optimized Route: " << rt3.length() << std::endl;

    rt2.save_route("../saved_routes/opt2_route.txt");
    rt3.save_route("../saved_routes/best_route.txt");
    return 0;
}
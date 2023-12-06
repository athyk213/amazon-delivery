// Comparisons of 2-opt and total search run times

#include "amazon_delivery.hpp"
#include <iostream>
#include <chrono>
#include <thread>


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

    // total Search
    std::ofstream outputFile("total_search.txt"); // Open a file for writing
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }


    int n = 10; // Set the desired value of n
    for (int i = 2; i < n; i++) {
        std::cout << "Addresses in Route: " << i + 2 << '\n';

        // Variable to store the total duration for 5 routes
        long long total_duration = 0;

        for (int j = 0; j < 5; j++) {
            Route rt1 = generate_random_route(i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            auto total_search_start = std::chrono::high_resolution_clock::now();
            rt1.apply_total_search();
            auto total_search_end = std::chrono::high_resolution_clock::now();
            auto total_search_duration = std::chrono::duration_cast<std::chrono::microseconds>(total_search_end - total_search_start).count();

            //std::cout << "\tTime taken by apply_total_search (Route " << j + 1 << "): " << total_search_duration << " microseconds" << std::endl;

            // Accumulate the duration for averaging
            total_duration += total_search_duration;
        }

        // Calculate and output the average duration
        long long average_duration = total_duration / 5;
        std::cout << "\tAverage time taken by apply_total_search: " << average_duration << " microseconds" << std::endl;
        outputFile << i+2 << ", " << average_duration << '\n';
    }
    outputFile.close(); // Close the file


    // 2_opt
    std::ofstream outputFile2("two_opt.txt"); // Open a file for writing
    if (!outputFile2.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    n = 400; // Set the desired value of n
    for (int i = 8; i < n; i += 10) {
        std::cout << "Addresses in Route: " << i + 2 << '\n';

        // Variable to store the total duration for 5 routes
        long long total_duration = 0;

        for (int j = 0; j < 10; j++) {
            Route rt1 = generate_random_route(i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            auto total_search_start = std::chrono::high_resolution_clock::now();
            rt1.apply_2_opt();
            auto total_search_end = std::chrono::high_resolution_clock::now();
            auto total_search_duration = std::chrono::duration_cast<std::chrono::microseconds>(total_search_end - total_search_start).count();

            std::cout << "\tTime taken by apply_2_opt (Route " << j + 1 << "): " << total_search_duration << " microseconds" << std::endl;

            // Accumulate the duration for averaging
            total_duration += total_search_duration;
        }

        // Calculate and output the average duration
        long long average_duration = total_duration / 10;
        std::cout << "\tAverage time taken by apply_2_opt: " << average_duration << " microseconds" << std::endl;
        outputFile2 << i+2 << ", " << average_duration << '\n';
    }
    outputFile2.close();
    return 0;
}

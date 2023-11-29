// Runs our routing algorithims on a random set of addresses

#include "amazon_delivery.hpp"
#include <cstdlib>
#include <ctime>

int main(){
    int number_of_addresses = 100;

    Route route;

    // seeding rng
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate random doubles between -10 and 10
    for (int i = 1; i <= number_of_addresses; i++){
        double randomDouble1 = -10 + static_cast<double>(std::rand()) / (RAND_MAX / 20.0);
        double randomDouble2 = -10 + static_cast<double>(std::rand()) / (RAND_MAX / 20.0);
        Address rand_address(randomDouble1, randomDouble2);

        route.add_address(rand_address);
    }

    // Display the initial route
    std::cout << "Initial Route: " << route.as_string() << std::endl;

    // Apply the 2-opt heuristic
    route.apply_2_opt();

    // Display the optimized route
    std::cout << "Optimized Route: " << route.as_string() << std::endl;

    return 0;

}
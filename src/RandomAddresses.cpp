// Runs our routing algorithims on a random set of addresses

#include "amazon_delivery.hpp"
#include <random>
#include <ctime>

int main(){
    int number_of_addresses = 12;

    Route route;

    // rng seed and distribution
    std::default_random_engine generator(std::time(nullptr));
    std::uniform_real_distribution<double> distribution(-1000,1000);


    // Generate random doubles between -10 and 10
    for (int i = 1; i <= number_of_addresses; i++){
        double randomDouble1 = distribution(generator);
        double randomDouble2 = distribution(generator);
        Address rand_address(randomDouble1, randomDouble2);

        route.add_address(rand_address);
    }

    // Display the initial route
    std::cout << "Initial Route: " << route.as_string() << std::endl;
    route.save_route("../saved_routes/initial_route.txt");
    cout << "Length: " << route.length() << '\n';

    // Apply the 2-opt heuristic
    route.apply_2_opt();

    // Display the optimized route
    std::cout << "Optimized Route: " << route.as_string() << std::endl;
    route.save_route("../saved_routes/opt2_route.txt");
    cout << "Length: " << route.length() << '\n';

    // Apply the total search alg
    route.apply_total_search();
    std::cout << "Best Route: " << route.as_string() << std::endl;
    route.save_route("../saved_routes/best_route.txt");
    cout << "Length: " << route.length() << '\n';

    // Apply the greedy route algorithim
    Route greedy_route = route.greedy_route();
    std::cout << "Greedy Route: " << greedy_route.as_string() << std::endl;
    greedy_route.save_route("../saved_routes/greedy_route.txt");
    cout << "Length: " << greedy_route.length() << '\n';

    return 0;

}
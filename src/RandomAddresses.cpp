// Runs our routing algorithims on a random set of addresses

#include "amazon_delivery.hpp"
#include <random>
#include <ctime>

int main(){
    int number_of_addresses = 12;

    Route rt1, rt2;

    // rng seed and distribution
    std::default_random_engine generator(std::time(nullptr));
    std::uniform_real_distribution<double> distribution(-1000,1000);
    double randomDouble1, randomDouble2;

    // Generate random doubles between -10 and 10
    for (int i = 1; i <= number_of_addresses; i++){
        randomDouble1 = distribution(generator);
        randomDouble2 = distribution(generator);
        Address rand_address1(randomDouble1, randomDouble2);
        rt1.add_address(rand_address1);

        randomDouble1 = distribution(generator);
        randomDouble2 = distribution(generator);
        Address rand_address2(randomDouble1, randomDouble2);
        rt2.add_address(rand_address2);
    }

    // Display the initial route
    std::cout << "Initial Routes: " << "\n" << rt1.as_string() << "\n" << rt2.as_string() << std::endl;
    rt1.save_routes("../saved_routes/initial_route.txt",rt2);
    cout << "Lengths: " << "\n" << rt1.length() << '\n' << rt2.length() << "\n" << (rt1.length()+rt2.length());

    // Apply the 2-opt heuristic
    std::vector<Route> optimized_routes = rt1.multi_path_apply_2_opt(rt2);

    // Display the optimized route
    std::cout << "\nOptimized Routes: " << "\n" << optimized_routes[0].as_string() << "\n" << optimized_routes[1].as_string() << std::endl;
    optimized_routes[0].save_routes("../saved_routes/opt2_route.txt",optimized_routes[1]);
    cout << "Lengths: " << "\n" << rt1.length() << '\n' << rt2.length() << "\n" << (rt1.length()+rt2.length());

    // Apply the total search alg
    // route.apply_total_search();
    // std::cout << "Best Route: " << route.as_string() << std::endl;
    // route.save_route("../saved_routes/best_route.txt");
    // cout << "Length: " << route.length() << '\n';

    // Apply the greedy route algorithim
    // Route greedy_route = route.greedy_route();
    // std::cout << "Greedy Route: " << greedy_route.as_string() << std::endl;
    // greedy_route.save_route("../saved_routes/greedy_route.txt");
    // cout << "Length: " << greedy_route.length() << '\n';

    return 0;

}
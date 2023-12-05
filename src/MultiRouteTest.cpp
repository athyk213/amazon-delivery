#include "multi_route.hpp"
#include <random>
#include <ctime>


int main(){
    int number_of_addresses = 30;

    // rng seed and distribution
    std::default_random_engine generator(0);
    std::uniform_real_distribution<double> distribution(-10,10);
    double randomDouble1, randomDouble2;

    // Generate three routes, the first route will be amazon prime
    Route route1, route2, route3;

    vector<Address> address_vec;
    for (int i = 1; i <= number_of_addresses; i++){
        randomDouble1 = distribution(generator);
        randomDouble2 = distribution(generator);
        if(i < 10){
            Address rand_address1(randomDouble1,randomDouble2,"dsafa", true);
            route1.add_address(rand_address1);
        }else if (i < 20){
            Address rand_address1(randomDouble1, randomDouble2,"dsafa");
            route2.add_address(rand_address1);
        }
        else {
            Address rand_address1(randomDouble1, randomDouble2,"dsafa");
            route3.add_address(rand_address1);
        }
    }

    vector<Route> routes = {route1, route2, route3};

    // multi route testing
    MultiRoute mrt(routes);
    cout << "3 route Unoptimized Length: " << mrt.total_length() << '\n';
    mrt.save_routes("../saved_routes/MultiRouteUnOpt.txt");
    
    
    mrt.optimize_routes();
    cout << "3 route Optimized Length: " << mrt.total_length() << '\n';
    mrt.save_routes("../saved_routes/MultiRouteOpt.txt");
    return 0;
}
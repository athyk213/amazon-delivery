#include "multi_route.hpp"
#include <random>
#include <ctime>


int main(){
    int number_of_addresses = 30;

    // rng seed and distribution
    std::default_random_engine generator(std::time(nullptr));
    std::uniform_real_distribution<double> distribution(0,1000);
    double randomDouble1, randomDouble2;

    // Generate random doubles between -10 and 10
    vector<Address> address_vec;
    for (int i = 1; i <= number_of_addresses; i++){
        randomDouble1 = distribution(generator);
        randomDouble2 = distribution(generator);
        Address rand_address1(randomDouble1, randomDouble2);
        address_vec.push_back(rand_address1);
    }

    // multi route testing
    MultiRoute mrt(3, address_vec);
    cout << "2 route Unoptimized Length: " << mrt.total_length() << '\n';
    mrt.save_routes("../saved_routes/MultiRouteUnOpt.txt");
    
    
    mrt.optimize_routes();
    cout << "2 route Optimized Length: " << mrt.total_length() << '\n';
    mrt.save_routes("../saved_routes/MultiRouteOpt.txt");

    // single route testing on same addresses
    MultiRoute mrt1(1, address_vec);
    cout << "1 route Unoptimized Length: " << mrt1.total_length() << '\n';
    mrt1.save_routes("../saved_routes/SingleRouteUnOpt.txt");
    
    
    mrt1.optimize_routes();
    cout << "1 route Optimized Length: " << mrt1.total_length() << '\n';
    mrt1.save_routes("../saved_routes/SingleRouteOpt.txt");

    return 0;
}
#include "multi_route.hpp"
#include <random>
#include <ctime>


int main(){
    int number_of_addresses = 40;

    // rng seed and distribution
    std::default_random_engine generator(std::time(nullptr));
    std::uniform_real_distribution<double> distribution(-1000,1000);
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
    MultiRoute mrt(4, address_vec);
    mrt.show_routes();
    mrt.optimize_routes();
    mrt.show_routes();

    return 0;
}
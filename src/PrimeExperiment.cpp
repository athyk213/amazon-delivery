#include "multi_route.hpp"
#include <fstream>

// ratio of prime addresses to all addresses
//double const ratio_prime = 0.5;

Address generate_random_address(bool prime) {
    int x = rand() % 1000;  // Random x coordinate (adjust range as needed)
    int y = rand() % 1000;  // Random y coordinate (adjust range as needed)
    return Address(x, y,"", prime);
}

vector<Address> generate_addresses(int num_addresses, int num_prime) {
    vector<Address> res;
    for (int i = 0; i < num_addresses; ++i) {
        bool is_prime = i < num_prime;
        res.push_back(generate_random_address(is_prime));
    }
    return res;
}


int main(){
    std::ofstream File("../saved_routes/PrimeExperiment/lengths.txt");

    for (int i = 0; i <= 10; i++){
        srand(2); // we want to generate the same random addresses each time
        double ratio = double(i)/10;
        int addresses_per_route = 100;
        int n_prime = ratio*addresses_per_route;
        cout << n_prime << '\n';

        Route rt1(generate_addresses(addresses_per_route,n_prime));
        Route rt2(generate_addresses(addresses_per_route,n_prime));


        MultiRoute routes({rt1,rt2});
        routes.show_routes();
        cout << routes.total_length() << '\n';
        routes.optimize_routes();
        cout << routes.total_length() << '\n';

        File << routes.total_length() << '\n';

        string file_name = to_string(i) + "0_percent_PrimeAddresses.mrt";
        routes.save_routes("../saved_routes/PrimeExperiment/" + file_name);
    }
    return 0;
}
#include "amazon_delivery.hpp"

int main() {
    // Create addresses and routes
    Address address1(0, 2, "2023-12-01", false);
    Address address2(2, 3, "2023-12-02", false);
    Address address3(3, 2, "2023-12-03", false);
    Address address4(2, 0, "2023-12-03", false);
    Address address5(1, 3, "2023-12-03");
    Address address6(1, 2, "2023-12-03");
    Address address7(2, 1, "2023-12-03");
    Address address8(3, 1, "2023-12-03");

    Route route1;
    route1.add_address(address1);
    route1.add_address(address2);
    route1.add_address(address3);
    route1.add_address(address4);

    Route route2;
    route2.add_address(address8);
    route2.add_address(address7);
    route2.add_address(address6);
    route2.add_address(address5);

    // Display the initial routes and lengths of each
    std::cout << "Initial Route 1: " << route1.as_string() << std::endl;
    std::cout << "Initial Route 2: " << route2.as_string() << std::endl;
    std::cout << "Length of Route 1: " << route1.length() << std::endl;
    std::cout << "Length of Route 2: " << route2.length() << std::endl;
    std::cout << "Length of Route 1 + 2: " << (route1.length() + route2.length()) << std::endl;

    std::vector<Route> optimized_routes = multi_path_apply_2_opt(route1, route2);

    // Display the optimized routes and lengths of false
    std::cout << "Optimized Route 1: " << optimized_routes[0].as_string() << std::endl;
    std::cout << "Optimized Route 2: " << optimized_routes[1].as_string() << std::endl;
    std::cout << "Length of Route 1: " << optimized_routes[0].length() << std::endl;
    std::cout << "Length of Route 2: " << optimized_routes[1].length() << std::endl;
    std::cout << "Length of Route 1 + 2: " << (optimized_routes[0].length() + optimized_routes[1].length()) << std::endl;

    return 0;
}
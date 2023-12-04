#include "multi_route.hpp"


int main(){

    Address address1(0, 2, "2023-12-01");
    Address address2(2, 3, "2023-12-02");
    Address address3(3, 2, "2023-12-03");
    Address address4(2, 0, "2023-12-03");
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
    route2.add_address(address5);
    route2.add_address(address6);
    route2.add_address(address7);
    route2.add_address(address8);
    
    vector<Route> routes = {route1,route2};
    MultiRoute mrt(routes);

    cout << "2 route Unoptimized Length: " << mrt.total_length() << '\n';
    mrt.save_routes("../saved_routes/MultiRouteUnOpt.txt");
    
    
    mrt.optimize_routes();
    cout << "2 route Optimized Length: " << mrt.total_length() << '\n';
    mrt.save_routes("../saved_routes/MultiRouteOpt.txt");

    return 0;
}
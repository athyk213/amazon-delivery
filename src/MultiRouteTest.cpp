#include "multi_route.hpp"

int main(){
    Address addr1(1,1);
    Address addr2(4,5);
    Address addr3(2,3);
    Address addr4(8,7);   
    Address addr5(5,9);
    Address addr6(-2,-7);    

    vector<Address> addr_vec = {addr1,addr2,addr3,addr4,addr5,addr6};

    Route rt1, rt2;
    rt1.add_address(addr1);
    rt1.add_address(addr2);
    rt1.add_address(addr3);
    rt2.add_address(addr4);
    rt2.add_address(addr5);
    rt2.add_address(addr6);

    vector<Route> rt_vec = {rt1,rt2};

    MultiRoute multi_rt_a(rt_vec);
    MultiRoute multi_rt_b(2,addr_vec);

    cout << "multi route A\n";
    multi_rt_a.show_routes();
    cout << "multi route B\n";
    multi_rt_b.show_routes();
}
// multiple Traveling Salesmen Problem application to Amazon Delivery

#include "amazon_delivery.hpp"

class MultiRoute{
    private:
        int num_routes;
        vector<Route> all_routes;
    
    public:
        // constructor: if vector of routes is known
        MultiRoute(vector<Route> routes): 
            num_routes(routes.size()), all_routes(routes) {}
        
        // constructor if only addresses are known
        MultiRoute(int n, vector<Address> addresses){
            num_routes = n;
            
            // needed to grab a subset of the addresses for each new route.
            int addresses_per_route = addresses.size() / n;
            vector<Address>::const_iterator first = addresses.begin();
            vector<Address>::const_iterator last;
            
            // construct n routes;
            for (int i = 0; i < n; i++){
                
                // get addresses for this new route
                if (i == n-1){
                    last = addresses.end();
                }else {
                    last = first + addresses_per_route;
                }
                vector<Address> rt_addresses(first,last);

                first  = last;
                // add new route
                Route new_rt(rt_addresses);
                all_routes.push_back(new_rt);
            }
        }
        void show_routes(){
            for (int i = 0; i < num_routes; i++){
                Route rt = all_routes[i];
                cout << "Route_" << i << ": " << rt.as_string() << '\n';
            }
        }
};

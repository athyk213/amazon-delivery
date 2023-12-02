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
        
        // display method
        void show_routes(){
            for (int i = 0; i < num_routes; i++){
                Route rt = all_routes[i];
                cout << "Route_" << i << ": " << rt.as_string() << '\n';
            }
        }

        // save method
        // all routes are saved in one folder
        void save_routes(string file_name) {
            // Open the file for writing
            std::ofstream file(file_name);

            // Check if the file is open
            if (!file.is_open()) {
                std::cerr << "Error opening file: " << file_name << std::endl;
                return;
            }

            // Write each address to the file
            for (int i = 0; i < num_routes; i++){
                file << all_routes[i].as_string() << std::endl;
            }

            // Close the file
            file.close();
        }

        // length
        double total_length(){
            double length = 0;
            for (int i = 0; i < num_routes; i++){
                length += all_routes[i].length();
            }
            return length;
        }

        // apply 2-opt for multiple routes
        void optimize_routes(){

            if (num_routes == 1){
                all_routes[0].apply_2_opt();
                return;
            }
            
            // keep optimizing until no more improvement
            double initial_length;
            bool improvement = true;
            while (improvement == true){
                
                improvement = false;
                initial_length = total_length();

                // apply 2 opt individually
                // TODO: Paralleize this
                for (int i = 0; i < num_routes ; i++){
                    all_routes[i].apply_2_opt();
                }
                
                // apply 2 opt between all routes
                // Idea : for all combinations of 2 routes, apply 2-opt for 2 routes
                for (int i = 0; i < num_routes - 1; i++){
                    for (int j = i+1 ; j < num_routes; j++){
                        Route rt1 = all_routes[i];
                        Route rt2 = all_routes[j];
                        vector<Route> _ = rt1.multi_path_apply_2_opt(rt2);
                    }
                }

                // check if there was improvement
                if (total_length() > initial_length){
                    improvement = true;
                }

            }
            return;
        }
};

#include <iostream> 
#include <algorithm> 
#include <cmath> 

class Address{
public:

int i, j; 

std::string Last_possible_delivery_date;
//constructor 
address(int &i, int &j, std::string Last_possible_delivery_date) : i(i), j(j), Last_possible_delivery_date(Last_possible_delivery_date){}

    // so do we do 2 methods and just choose the best? 
    // implementing the straight line/manhattan method
    double distance( const address& additional_addresses, bool manhattan_distance = true){
        if (manhattan_distance) {
            double manhattan_distance_value = abs(i - additional_addresses.i) + abs(j - additional_addresses.j);
            return manhattan_distance_value;    
        } else { 
            // straight line approach
            return sqrt(pow(i - additional_addresses.i,2) + pow(j - additional_addresses.j,2));
        }
        }
    };
    

   int main(){
    Address address1(1, 2, "2023-11-30");
    Address address2(3, 5, "2023-11-25");

    double manhattan_distance = address1.distance(address2);
    double straight_line_distance = address1.distance(address2, false);

    std::cout << "Manhattan Distance: " << manhattan_distance << std::endl;
    std::cout << "Straight-Line Distance: " << straight_line_distance << std::endl;

    return 0;

   } 



#include "DieCast.h"
#include <iostream>

// die::literal namespace exports a literal "# of rolls"_D(int sides)
// returns a facade to the die_cast object that can be concatenated.
int main() {

    using namespace die::literal;
    die::die_cast res = 4_D(6)+5 << 3_D(8) << 10_D(2)-30 << 1_D(6);
    
    for(auto& i : res) {
        std::cout << "Rolled a " << i.sides << " sided die ";
        std::cout << i.roll << ((i.roll == 1)? " time " : " times");

        if(i.modifier != 0) {
            std::cout << " with a modifier of " << i.modifier << "!";
        } else {
            std::cout << "!";
        }
        
        std::cout << " => " << i.result << std::endl;
    }

    std::cout << "\nResults only:" << std::endl;
    
    // Dissolve into integer result set only
    // if you just want the final value
    for(auto& i : res) {
        std::cout << "Final value: " << i << std::endl;
    }
}

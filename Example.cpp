#include "DieCast.h"
#include <iostream>

// die:: namespace has one function: cast()
// returns a chainable object that is also an iterable result set
int main() {
    // Roll a 6 sided die 3 times 
    // Roll a 8 sided die 2 times and then add 10 to the result
    // e.g. roll 3D6 2D8+10
    auto res = die::cast<3,6>().cast<2,8>(+10);

    // iterable die_cast_info object can tell you
    // the following properties about a roll:
    // count of sides on die, roll #, modifier, and the result
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

/*
Output
----------------------------------------------------------

$g++ -o main Example.cpp
$main

Rolled a 6 sided die 1 time ! => 5
Rolled a 6 sided die 2 times! => 3
Rolled a 6 sided die 3 times! => 1
Rolled a 8 sided die 1 time  with a modifier of 10! => 17
Rolled a 8 sided die 2 times with a modifier of 10! => 14

Results only:
Final value: 5
Final value: 3
Final value: 1
Final value: 17
Final value: 14
*/

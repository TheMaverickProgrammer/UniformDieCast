# UniformDieCast
Provides chainable and iterable object for uniformly distributed die casts. 
Useful for stastics or table top RPG simulations.

# Signature
```cpp
die::die_cast result = die::cast<int N, int M>();
```

Rolls an _M_ sided die _N_ times 

The signature comes from the common convention "3D8" meaning "roll an 8 sided dice 3 times"

What about something like "2D20-4" or "1D8+10"?

To add modifiers to a roll, supply the modifier as an additional argument like so:

```cpp
auto result = die::cast<2, 20>(-4).cast<1, 8>(+10);
```

Rolls a 20 sided die 2 times and subtracts 4 from each result in the group.

Then it rolls an 8 sided die once and adds 10 to the result;

# Iterable
You can keep chaining the cast function for complex rolls or invoke them independantly
one the `die_cast` object. The object stores each roll in an internal list. 

Here's how to fetch the result:

```cpp
auto result = die::cast<4, 6>();

for(auto& i : res) {
    std::cout << "Final value: " << i << std::endl;
}
```

You can copy the result list for dynamic lookups like so:

```cpp
auto result = die::cast<3, 5>(+1);

// only the final results dissolve into a vector
std::vector<int> final_values = result;
```

# More info
You can get more information about the roll after the fact. 
Properties like the roll number, how many sides the die had, and any modifiers.
See below for a full example.

```cpp
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
```

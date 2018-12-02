12/1/2018

Due to feedback about compile-time limitations, the api has been changed since release.
The api now supports user-defined literals which makes the coding experience even more intuitive.

# UniformDieCast
Provides chainable and iterable object for uniformly distributed die casts. 
Useful for statistics or table top RPG simulations.

# Signature
```cpp
using namespace die::literal;
die::die_cast result = #N_D(int M);
```

Rolls an _M_ sided die _N_ number of times 

The signature comes from the common convention "3D8" meaning "roll an 8 sided dice 3 times".

# Throws

Both _N_ and _M_ must be greater than or equal to 1 otherwise an instance of `std::invalid_argument` is thrown.

# Modifiers

What about something like "2D20-4" or "1D8+10"?

To add modifiers to a roll, do so like this:

```cpp
auto result = 2_D(20)-4 << 1_D(8)+10;
```

Rolls a 20 sided die 2 times and subtracts 4 from each result in the group.

Then it rolls an 8 sided die once and adds 10 to the result. 

# Iterable
You can keep chaining the cast function for complex rolls or invoke them independantly
on the `die_cast` object. The object stores each roll in an internal list. 

```cpp
die::die_cast chain = 10_D(6) << 1_D(20) << 3_D(4) << 1_D(8);
```

Here's how to fetch the result set:

```cpp
for(auto& i : chain) {
    std::cout << "Final value: " << i << std::endl;
}
```

You can copy the result sets for dynamic lookups like so:

```cpp
// copy from the info list. only the final result set dissolves into a vector.
std::vector<int> final_values = chain;

...

// direct assignment 
std::vector<int> final_values = 3_D(5)+1;
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
    auto res = 3_D(6) << 2_D(8)+10;

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
}

/*
Output
----------------------------------------------------------

$g++ -o main UserLiteralExample.cpp
$main

Rolled a 6 sided die 1 time ! => 5
Rolled a 6 sided die 2 times! => 3
Rolled a 6 sided die 3 times! => 1
Rolled a 8 sided die 1 time  with a modifier of 10! => 17
Rolled a 8 sided die 2 times with a modifier of 10! => 14
*/
```

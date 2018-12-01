#include <vector>
#include <random>
#include <stdexcept>

/*
Author: TheMaverickProgrammer
Date: 11/30/2018
Description:

die:: namespace has a function `cast<int rolls, int sides>(int modifier)`
that returns an iterable die_cast object that can chain multiple `cast()` calls.

The object can be directly used in a for-each loop. See accompanying README for examples.
*/

namespace die {
    struct die_cast_info {
        int result;
        int sides;
        int roll;
        int modifier;

        // dissolves into result for ease of use
        operator int() { return result; }
    };

    struct die_cast {
        public:

        /* constructor needed to construct random device and generator */
        die_cast() : generator(rand_dev()) { ; }
        
        /* custom copy needed because random devices are non copyable */
        die_cast(const die_cast& rhs) {
            rand_dev();
            generator = rhs.generator;
            list = rhs.list;
        }

        /* short hand iterable keywords */
        typedef die_cast_info* iterator;
        typedef const die_cast_info* const_iterator;
        
        /*
        iterable template syntax requirements
        */
        iterator begin() { return &list[0]; }
        const_iterator begin() const { return &list[0]; }
        iterator end() { return &list[list.size()]; }
        const_iterator end() const { return &list[list.size()]; }
        die_cast_info operator*() { return *iter; }
        void operator++() { ++iter; }
        bool operator!=(die_cast rhs) { return iter != rhs.iter;  }

        private:
        /*
        internals for iteration
        */
        std::vector<die_cast_info> list;
        iterator iter;

        /*
        internals for rand
        */
        std::random_device rand_dev;
        std::mt19937 generator;

        public:

        /* Chain function is same signature as static calls */
        die_cast& cast(int rolls, int sides, int modifier=0) {

            if(rolls < 1) {
                throw std::invalid_argument("die::die_cast number of rolls must be at least 1");
            }
            
           if(sides < 1) {
                throw std::invalid_argument("die::die_cast number of sides must be at least 1");
            }
            
            /*
             API allows for any type of die to be rolled in sequence
             and must create new distribution each time
            */

            std::uniform_int_distribution<int> distr(1, sides);
            
            for(int i = 0; i < rolls; i++) {
                list.push_back(die_cast_info({distr(generator)+modifier, sides, i+1, modifier}));
            }

            return *this;
        }

        // dissolves into only result set 
        operator std::vector<int>() {
            std::vector<int> result_set;

            for(auto& i : *this) {
                result_set.push_back(i.result);
            }

            return result_set;
        }
    };

    // primary call
    static auto cast(int rolls, int sides, int modifier=0) {
        die_cast res;
        return res.cast(rolls, sides, modifier);
    }
};

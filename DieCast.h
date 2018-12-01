#include <vector>
#include <random>

/*
Author: TheMaverickProgrammer
Date: 11/30/2018
Description:

die:: namespace has a function `cast<int rolls, int sides>(int modifier)`
that returns an iterable die_cast object that can chain multiple `cast()` calls.
*/

namespace die {
    struct die_cast_info {
        const int result;
        const int sides;
        const int roll;
        const int modifier;

        // dissolves into result for ease of use
        operator int() { return result; }
    };

    struct die_cast {
        public:
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
        std::vector<die_cast_info> list;
        iterator iter;

        public:

        // Chain function is same signature as static call
        template<int rolls, int sides>
        auto cast(int modifier=0) {
            for(int i = 0; i < rolls; i++) {
                std::random_device rand_dev;
                std::mt19937 generator(rand_dev());
                std::uniform_int_distribution<int> distr(1, sides);

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
    template<int rolls, int sides>
    static auto cast(int modifier=0) {
        die_cast res;
        return res.cast<rolls, sides>(modifier);
    }
};

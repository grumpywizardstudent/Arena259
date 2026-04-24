#ifndef RNG_H
#define RNG_H

#include <random>


class RNG {
    private:
        inline static std::random_device rd{}; // creates a unique seed value for random number generation
        inline static std::mt19937 gen{rd()}; // the classic mersenne twist
        inline static std::uniform_int_distribution<> COIN{0,1}; // creates a uniform distribution for flipCoin()
    public:
        static bool flipCoin(); // flip a coin and get a bool
        static int randomValue(int min, int max); // returns a random int from within the range
        inline static std::mt19937 generate{rd()};
};

#endif
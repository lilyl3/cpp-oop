#ifndef DICE_H
#define DICE_H

#include <ctime>
#include <random>
class Dice {
    private:
        std::mt19937 rng;
        std::uniform_int_distribution<int> dist;
    public:
        Dice() : rng(static_cast<unsigned int>(std::time(nullptr))), dist(1, 6) {}
        int roll();
};

#endif
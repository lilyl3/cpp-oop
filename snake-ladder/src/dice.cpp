#include "../include/dice.h"
#include <random>
#include <ctime>
using namespace std;

int Dice::roll(){
    return dist(rng);
}
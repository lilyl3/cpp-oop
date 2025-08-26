#include "game.h"
#include <vector>
#include <map>

int main(){
    Player playerA = Player("A"), playerB = Player("B");
    vector<Player*> players = {&playerA, &playerB};
    
    map<int, int> ladders, snakes;
    ladders = {
        {5, 8},
        {6, 10},
    };
    snakes = {
        {8, 4},
        {3, 1},
        {11, 6},
    };

    Game game = Game(players, ladders, snakes, 15);
    game.startGame();
}

// g++ -Iinclude -std=c++17 src/*.cpp -o myprogram
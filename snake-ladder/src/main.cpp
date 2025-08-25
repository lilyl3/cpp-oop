#include "game.h"
#include <vector>
#include <map>

int main(){
    Player playerA = Player("A"), playerB = Player("B");
    vector<Player*> players = {&playerA, &playerB};
    
    map<int, int> ladders, snakes;
    ladders = {
        {1, 7},
        {5, 8},
        {6, 10},
    };
    snakes = {
        {8, 4},
        {3, 1},
        {9, 4},
    };

    Game game = Game(players, ladders, snakes, 10);
    game.startGame();
}
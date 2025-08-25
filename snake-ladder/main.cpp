#include "src/game.h"
#include <vector>
#include <map>

int main(){
    Player playerA = Player("A"), playerB = Player("B");
    vector<Player*> players = {&playerA, &playerB};
    
    map<int, int> ladders, snakes;

    Game game = Game(players, ladders, snakes, 100);
    game.start();
}
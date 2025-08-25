#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "dice.h"
#include "player.h"
#include <vector>
#include <map>
#include <string>

using namespace std;
class Game {
    private:
        Board board;
        Dice dice;
        vector<Player*> players;
        int currentPlayerIdx;

        string getWinningPlayerId() const;
        Player* getCurrentPlayer() const;
        void setNextPlayer();
        void resetPlayerPositions();
        void playerMove();
        bool doesPlayerWin() const;
    public:
        Game(const vector<Player*> &, const map<int, int> &, const map<int, int> &, int);
        void startGame();
};

#endif
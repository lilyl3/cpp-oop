#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;
class Player {
    private:
        string id;
        int position;
    public:
        Player (string id) : id(id), position(1) {}
        string getPlayerId() const;
        int getPlayerPosition() const;
        void resetPlayerPosition();
        void setPlayerPosition(int newPosition);
};

#endif
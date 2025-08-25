#include "../include/player.h"
#include <string>
using namespace std;

string getPlayerId() const{
    return id;
}

int getPlayerPosition() const{
    return position;
}

void resetPlayerPosition(){
    position = 1;
}

void setPlayerPosition(int newPosition){
    position = newPosition;
}
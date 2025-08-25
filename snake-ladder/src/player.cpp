#include "player.h"
#include <string>
using namespace std;

string Player::getPlayerId() const{
    return id;
}

int Player::getPlayerPosition() const{
    return position;
}

void Player::resetPlayerPosition(){
    position = 1;
}

void Player::setPlayerPosition(int newPosition){
    position = newPosition;
}
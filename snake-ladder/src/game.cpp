#include "board.h"
#include "player.h"
#include "dice.h"
#include "game.h"

#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>
using namespace std;

Game::Game(
    const vector<Player*> &players, 
    const map<int, int> &ladderPositions, 
    const map<int, int> &snakePositions, 
    int boardSize
) : currentPlayerIdx(0), players(players), board(ladderPositions, snakePositions, boardSize), dice() {
    if (players.size() < 2) {
        throw invalid_argument("Game must have at least 2 players.");
    }
}

void Game::resetPlayerPositions(){
    for (Player* player : players){
        player->resetPlayerPosition();
    }
}

Player* Game::getCurrentPlayer() const{
    return players[currentPlayerIdx];
}

void Game::playerMove() {
    Player* player = getCurrentPlayer();
    int newPosition = player->getPlayerPosition() + dice.roll();
    if (newPosition > board.getBoardSize()) return;
    else {
        player->setPlayerPosition(board.getCellPosition(newPosition));
    }
}

bool Game::doesPlayerWin() const {
    Player* player = getCurrentPlayer();
    return player->getPlayerPosition() == board.getBoardSize();
}

void Game::setNextPlayer() {
    currentPlayerIdx += 1;
    currentPlayerIdx %= players.size();
}

string Game::getWinningPlayerId() const{
    Player* player = getCurrentPlayer();
    return player->getPlayerId();
}

void Game::startGame() {
    resetPlayerPositions();
    while (true) {
        playerMove();
        if (doesPlayerWin()) break;
        setNextPlayer();
    }
    cout << "Congratulations to " << getWinningPlayerId() << endl;
}
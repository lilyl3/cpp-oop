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
) : board(ladderPositions, snakePositions, boardSize), dice(), players(players), currentPlayerIdx(0){
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
    int step = dice.roll();
    int newPosition = player->getPlayerPosition() + step;

    cout << "\nPlayer " << player->getPlayerId() << " is currently at: " << player->getPlayerPosition() << endl;
    cout << "Player " << player->getPlayerId() << " rolls " << step << endl;

    if (newPosition > board.getBoardSize()) return;
    else {
        newPosition = board.getCellPosition(newPosition);
        player->setPlayerPosition(newPosition);
        cout << "Player " << player->getPlayerId() << " is now at position " << player->getPlayerPosition() << endl;
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
    cout << "Congratulations player " << getWinningPlayerId() << " won!" << endl;
}
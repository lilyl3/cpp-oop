#include "board.h"
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
using namespace std;

Board::Board(
    const std::map<int, int>& ladderPositions, 
    const std::map<int, int>& snakePositions, 
    int size
) : ladderPositions(ladderPositions), snakePositions(snakePositions), boardSize(size) {
    if (!isValidBoard()){
        throw invalid_argument("Invalid size or snake and/or ladder positions.");
    }
}

bool Board::isValidPosition(set<int> &configuredCells, int cellPosition, int newPosition) const{
    // All configured snake/ladder positions should be within the board
    if (cellPosition < 1 || cellPosition > boardSize) return false;
    if (newPosition < 1 || newPosition > boardSize) return false;

    // Each cell should be configured once
    if (configuredCells.find(cellPosition) != configuredCells.end()) return false;
    configuredCells.insert(cellPosition);

    return true;
}

bool Board::isValidBoard() const {
    if (boardSize < 1) return false;

    set<int> configuredCells;
    for (const auto& pair : snakePositions) {
        if (!isValidPosition(configuredCells, pair.first, pair.second)) return false;
        // check if snake reduces progress
        if (!(pair.first > pair.second)) return false;
    }

    for (const auto& pair : ladderPositions) {
        if (!isValidPosition(configuredCells, pair.first, pair.second)) return false;
        // check if ladder improves progress
        if (!(pair.first < pair.second)) return false;
    }
    return true;
}

int Board::getCellPosition(int position) const {
    if (snakePositions.find(position) != snakePositions.end()) {
        cout << "Player landed on a snake! Moving to position: " << snakePositions.at(position) << endl;
        return snakePositions.at(position);
    }
    if (ladderPositions.find(position) != ladderPositions.end()) {
        cout << "Player landed on a ladder! Moving to position: " << ladderPositions.at(position) << endl;
        return ladderPositions.at(position);
    }
    return position;
}

int Board::getBoardSize() const {
    return boardSize;
}
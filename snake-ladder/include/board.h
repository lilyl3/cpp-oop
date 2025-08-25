#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <set>
class Board {
    private:
        std::map<int, int> snakePositions, ladderPositions;
        int boardSize;
        bool isValidBoard() const;
        bool isValidPosition(set<int> &, int, int);
    public:
        Board(const std::map<int, int>&, const std::map<int, int>&, int size);
        int getCellPosition(int) const;
        int getBoardSize() const;
};
#endif
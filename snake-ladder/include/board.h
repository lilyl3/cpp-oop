#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <set>
class Board {
    private:
        std::map<int, int> snakePositions, ladderPositions;
        int boardSize;
        bool isValidBoard() const;
        bool isValidPosition(std::set<int> &, int, int) const;
    public:
        Board(const std::map<int, int>&, const std::map<int, int>&, int size);
        int getCellPosition(int) const;
        int getBoardSize() const;
};
#endif
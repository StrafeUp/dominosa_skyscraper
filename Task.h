//
// Created by bohdankol on 6/8/2022.
//

#ifndef LAB1_TASK_H
#define LAB1_TASK_H


#include <map>
#include "Tile.h"

class Task {
public:
    Task();

    virtual ~Task();
    void solve(int startX, int startY, int startIndex);
    void reset();

private:
    Tile ***gameField;
    bool isSecondHalfChecked;
    static const int TASK_HEIGHT = 5;
    static const int TASK_WIDTH = 6;
    std::map<int, std::vector<int>> stash;
    char testExample[TASK_HEIGHT][TASK_WIDTH] = {{'0', '0', ' ', '0', '0', '0'},
                                                 {' ', '0', ' ', ' ', ' ', '0'},
                                                 {'0', '0', ' ', '0', '0', '0'},
                                                 {'0', ' ', ' ', ' ', ' ', '0'},
                                                 {'0', '0', '0', '0', '0', '0'}};
    std::vector<std::vector<int>> iPossible = {{1, 2, 3},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 1},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 1, 2, 3, 4, 5, 6}};
    std::vector<std::vector<int>> jPossible = {{0, 1, 2, 3, 4, 5, 6},
                                               {1, 2},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 3}};
    char testAnswer[TASK_HEIGHT][TASK_WIDTH] = {{2,   1,   ' ', 3,   3,   3},
                                                {' ', 1,   ' ', ' ', ' ', 0},
                                                {1,   1,   ' ', 1,   0,   0},
                                                {3,   ' ', ' ', ' ', ' ', 0},
                                                {3,   2,   2,   2,   2,   0}};

    Tile ***generateGameField(char field[TASK_HEIGHT][TASK_WIDTH]);

    void resetStash();

    void resetGameField();

    void returnDominoToStash(int prevNumber, int currNum);

    void removeDominoFromStash(int prevNumber, int currNum);

    std::vector<int> getAllSecondHalvesByFirst(int firstHalf);

    void solveFirstHalfFinal(Tile *tile, int prevNumber);

    void solveSecondHalfFinal(Tile *tile, int prevNumber);

    int howManyLeftInStash();

    void printGameField();

    void printInputNumbers();

    void setPossibleNumbersToTiles();
};


#endif //LAB1_TASK_H

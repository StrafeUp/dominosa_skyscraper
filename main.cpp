#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include "Tile.h"

static const int TASK_HEIGHT = 5;
static const int TEST_TASK_HEIGHT = 5;

static const int TASK_WIDTH = 6;
static const int TEST_TASK_WIDTH = 6;
std::map<int, std::vector<int>> stash;
bool isSecondHalfOfDomino = true;
bool isSecondHalfOfDominoSolve = true;
char testExample[TEST_TASK_HEIGHT][TEST_TASK_WIDTH] = {{'0', '0', ' ', '0', '0', '0'},
                                                       {' ', '0', ' ', ' ', ' ', '0'},
                                                       {'0', '0', ' ', '0', '0', '0'},
                                                       {'0', ' ', ' ', ' ', ' ', '0'},
                                                       {'0', '0', '0', '0', '0', '0'}};
int visitedTiles = 0;
Tile ***gameField;

void printInputNumbers(char field[TASK_HEIGHT][TASK_WIDTH]);

Tile ***generateGameField(char field[TASK_HEIGHT][TASK_WIDTH]);

void printGameField(Tile ***gameField);

std::vector<int> intersection(std::vector<int> v1,
                              std::vector<int> v2);

void setPossibleNumbersToTiles(Tile ***gameField, std::vector<std::vector<int>> iPossible,
                               std::vector<std::vector<int>> jPossible);

void setAnswerToTheGameField(Tile ***gameField, char answer[TEST_TASK_HEIGHT][TEST_TASK_WIDTH]);

bool startCheck(Tile ***gameField, int startX, int startY);

bool solve(Tile ***gameField, int startX, int startY);

void resetGameField(Tile ***gameField);

std::vector<int> getAllSecondHalvesByFirst(int firstHalf);

int getPositionOfElement(std::vector<int> v, int el);

void removeDominoFromStash(int prevNumber, int currNum);

void returnDominoToStash(int prevNumber, int currNum);

void startSolvingNew(Tile ***gameField, int startX, int startY);

void solveFirstHalfFinal(Tile *tile, int prevNumber);
void solveSecondHalfFinal(Tile *tile, int prevNumber);
int main() {

    std::vector<std::string> stringStash = std::vector<std::string>();

    std::vector<std::vector<int>> iPossible = {{0, 1, 2, 3, 4, 5, 6},
                                               {4, 6},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 2, 4, 6},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {1, 3, 6},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 1, 2, 3, 4, 5, 6}};

    std::vector<std::vector<int>> jPossible = {{2, 5, 6},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 1, 4},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 3, 6},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 1, 3},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {1, 2, 4},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {0, 1, 2, 3, 4, 5, 6},
                                               {2, 3, 5, 6}};

    std::vector<std::vector<int>> test_iPossible = {{1, 2, 3},
                                                    {0, 1, 2, 3, 4, 5, 6},
                                                    {0, 1},
                                                    {0, 1, 2, 3, 4, 5, 6},
                                                    {0, 1, 2, 3, 4, 5, 6}};
    std::vector<std::vector<int>> test_jPossible = {{0, 1, 2, 3, 4, 5, 6},
                                                    {1, 2},
                                                    {0, 1, 2, 3, 4, 5, 6},
                                                    {0, 1, 2, 3, 4, 5, 6},
                                                    {0, 1, 2, 3, 4, 5, 6},
                                                    {0, 3}};


    int counter = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j <= counter; ++j) {
            stash[i].push_back(j);
        }
        counter++;
    }

    //std::set<int> secondHalves = getAllSecondHalvesByFirst(0);


    //Remove by key and by value -> key (4-6 and 6-4 are the same)

    //stash[0].erase(stash[0].begin() + 1);

    /*char field[TASK_HEIGHT][TASK_WIDTH] = {{'0', '0', '0', '0', ' ', ' ', ' ', ' ', ' ', ' ', '0', '0', '0', '0'},
                                           {' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', '0'},
                                           {' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', '0'},
                                           {'0', '0', '0', '0', '0', '0', ' ', ' ', '0', '0', '0', '0', '0', '0'},
                                           {'0', ' ', ' ', '0', ' ', '0', ' ', ' ', '0', ' ', '0', ' ', ' ', '0'},
                                           {'0', ' ', ' ', '0', '0', '0', ' ', ' ', '0', '0', '0', ' ', ' ', '0'},
                                           {'0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0'},
                                           {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'}};*/


    char testAnswer[TEST_TASK_HEIGHT][TEST_TASK_WIDTH] = {{2,   1,   ' ', 3,   3,   3},
                                                          {' ', 1,   ' ', ' ', ' ', 0},
                                                          {1,   1,   ' ', 1,   0,   0},
                                                          {3,   ' ', ' ', ' ', ' ', 0},
                                                          {3,   2,   2,   2,   2,   0}};
    printInputNumbers(testExample);
    gameField = generateGameField(testExample);
    setPossibleNumbersToTiles(gameField, test_iPossible, test_jPossible);
    printGameField(gameField);
//    setAnswerToTheGameField(gameField, testAnswer);
//    printGameField(gameField);
//    std::cout << std::boolalpha;
//    std::cout << "Is the answer correct?: " << static_cast<bool>(startCheck(gameField, 0, 0));
//    std::cout << std::endl;
//    std::cout << "Is all fields visited?: " << static_cast<bool>(startCheck(gameField, 0, 0));
    solve(gameField, 0, 0);
//    startSolvingNew(gameField, 0, 0);
    return 0;
}

void printInputNumbers(char field[TASK_HEIGHT][TASK_WIDTH]) {
    for (int i = 0; i < TASK_HEIGHT; ++i) {
        for (int j = 0; j < TASK_WIDTH; ++j) {
            std::cout << field[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printGameField(Tile ***gameField) {
    for (int i = 0; i < TASK_HEIGHT; ++i) {
        for (int j = 0; j < TASK_WIDTH; ++j) {
            if (gameField[i][j] != nullptr) {
                std::cout << gameField[i][j]->value << " ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}

void setPossibleNumbersToTiles(Tile ***gameField, std::vector<std::vector<int>> iPossible,
                               std::vector<std::vector<int>> jPossible) {
    for (int i = 0; i < TASK_HEIGHT; ++i) {
        for (int j = 0; j < TASK_WIDTH; ++j) {
            if (gameField[i][j] != nullptr) {
                gameField[i][j]->possibleNumbers = intersection(iPossible[i], jPossible[j]);
            }
        }
    }
}

Tile ***generateGameField(char field[TASK_HEIGHT][TASK_WIDTH]) {
    // Save Tiles in 2d array, fill it in 2 loops, while constructing all the pointers
    // Account for visited Tiles in walking algorithm

    Tile ***gameField = new Tile **[TASK_HEIGHT];

    //Fill the newly created space with nullptrs
    for (int i = 0; i < TASK_HEIGHT; ++i) {
        gameField[i] = new Tile *[TASK_WIDTH];
        for (int j = 0; j < TASK_WIDTH; ++j) {
            gameField[i][j] = nullptr;
        }
    }

    for (int i = 0; i < TASK_HEIGHT; ++i) {
        for (int j = 0; j < TASK_WIDTH; ++j) {
            if (field[i][j] == '0') {
                Tile *tempTile;
                //Check if Tile already was created and placed on the game field
                if (gameField[i][j] == nullptr) {
                    tempTile = new Tile(i, j);
                } else {
                    tempTile = gameField[i][j];
                }

                //Check surroundings for existing tiles or map values from input to the objects
                if (field[i - 1][j] == '0') {
                    if (gameField[i - 1][j] != nullptr && (i - 1) >= 0) {
                        tempTile->top = gameField[i - 1][j];
                    } else if ((i - 1) >= 0) {
                        Tile *newTile = new Tile(j, i - 1);
                        tempTile->top = newTile;
                        gameField[i - 1][j] = newTile;
                    }
                }
                if (field[i][j + 1] == '0') {
                    if (gameField[i][j + 1] != nullptr && (j + 1) < TASK_WIDTH) {
                        tempTile->right = gameField[i][j + 1];
                    } else if ((j + 1) < TASK_WIDTH) {
                        Tile *newTile = new Tile(j, i + 1);
                        tempTile->right = newTile;
                        gameField[i][j + 1] = newTile;
                    }
                }
                if (field[i + 1][j] == '0') {
                    if (gameField[i + 1][j] != nullptr && (i + 1) < TASK_HEIGHT) {
                        tempTile->bottom = gameField[i + 1][j];
                    } else if ((i + 1) < TASK_HEIGHT) {
                        Tile *newTile = new Tile(j + 1, i);
                        tempTile->bottom = newTile;
                        gameField[i + 1][j] = newTile;
                    }
                }
                if (field[i][j - 1] == '0') {
                    if (gameField[i][j - 1] != nullptr && (j - 1) >= 0) {
                        tempTile->left = gameField[i][j - 1];
                    } else if ((j - 1) >= 0) {
                        Tile *newTile = new Tile(j, i - 1);
                        tempTile->left = newTile;
                        gameField[i][j - 1] = newTile;
                    }

                }
                //Place new tile in the game field
                gameField[i][j] = tempTile;
            } else {
                //Place an empty tile in the game field
                gameField[i][j] = nullptr;
            }
        }
    }
    return gameField;
}

std::vector<int> intersection(std::vector<int> v1,
                              std::vector<int> v2) {
    std::vector<int> v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(), v1.end(),
                          v2.begin(), v2.end(),
                          back_inserter(v3));
    return v3;
}

void setAnswerToTheGameField(Tile ***gameField, char answer[TEST_TASK_HEIGHT][TEST_TASK_WIDTH]) {
    for (int i = 0; i < TEST_TASK_HEIGHT; ++i) {
        for (int j = 0; j < TEST_TASK_WIDTH; ++j) {
            if (answer[i][j] != ' ') {
                gameField[i][j]->value = answer[i][j];
            }
        }
    }
}

void checkNext(Tile *tile, int prevValue) {
    isSecondHalfOfDomino = !isSecondHalfOfDomino;
    tile->visited = true;
    int currVal = tile->value;
    if (std::find(tile->possibleNumbers.begin(), tile->possibleNumbers.end(), currVal) !=
        tile->possibleNumbers.end()) { //Check for the allowed numbers
        if (isSecondHalfOfDomino) {
            if (std::find(stash.at(prevValue).begin(), stash.at(prevValue).end(), currVal) !=
                stash.at(prevValue).end()) {
                // delete by first half
                stash.at(prevValue).erase(stash.at(prevValue).begin() +
                                          (std::find(stash.at(prevValue).begin(), stash.at(prevValue).end(), currVal) -
                                           stash.at(
                                                   prevValue).begin())); // it - v.begin() ot find the index of an element in vector
            }

            if (std::find(stash.at(currVal).begin(), stash.at(currVal).end(), prevValue) != stash.at(currVal).end()) {
                //delete by second half
                stash.at(currVal).erase(stash.at(currVal).begin() +
                                        (std::find(stash.at(currVal).begin(), stash.at(currVal).end(), prevValue) -
                                         stash.at(
                                                 currVal).begin())); // it - v.begin() ot find the index of an element in vector
            }
        }

        if (tile->top != nullptr && !tile->top->visited) {
            if (isSecondHalfOfDomino && currVal != tile->top->value) {
                return;
            }
            checkNext(tile->top, currVal);
        }
        if (tile->right != nullptr && !tile->right->visited) {
            if (isSecondHalfOfDomino && currVal != tile->right->value) {
                return;
            }
            checkNext(tile->right, currVal);
        }
        if (tile->bottom != nullptr && !tile->bottom->visited) {
            if (isSecondHalfOfDomino && currVal != tile->bottom->value) {
                return;
            }
            checkNext(tile->bottom, currVal);
        }
        if (tile->left != nullptr && !tile->left->visited) {
            if (isSecondHalfOfDomino && currVal != tile->left->value) {
                return;
            }
            checkNext(tile->left, currVal);
        }
    }
}

bool startCheck(Tile ***gameField, int startX, int startY) {
    checkNext(gameField[startX][startY], 0);
    int acc = 0;
    for (int i = 0; i < stash.size(); ++i) {
        acc += stash.at(i).size();
    }
    return acc == 0;
}

void solveTileTestFailed(Tile *tile, int prevNumber);

void solveFirstHalf(Tile *tile, int prevNumber, int firstHalfDeleted, bool isDeleted);

bool solve(Tile ***gameField, int startX, int startY) {
    for (int i = 0; i < stash.size(); ++i) {
        for (int j = 0; j < stash.at(i).size(); ++j) {
            solveFirstHalfFinal(gameField[startX][startY], i);
            isSecondHalfOfDominoSolve = true;
            //printGameField(gameField);
            //bool isAnswer = startCheck(gameField, 0,0);
            //std::cout << startCheck(gameField, isAnswer,0);
//            if (i == 3) {
//                return true;
//            }
            resetGameField(gameField);
//            printGameField(gameField);
        }
    }
    return true;
}

void checkIfFinished(Tile *tile) {
    if (!tile->checked) {
        tile->checked = true;
        if (tile->visited) {
            visitedTiles++;
        }
    }
    if (tile->top != nullptr && !tile->top->checked) {
        checkIfFinished(tile->top);
    }
    if (tile->right != nullptr && !tile->right->checked) {
        checkIfFinished(tile->right);
    }
    if (tile->bottom != nullptr && !tile->bottom->checked) {
        checkIfFinished(tile->bottom);
    }
    if (tile->left != nullptr && !tile->left->checked) {
        checkIfFinished(tile->left);
    }
}

bool isFinishedSolving(Tile ***gameField, int startX, int startY) {
/*    visitedTiles = 0;
    checkIfFinished(gameField[startX][startY]);
    return visitedTiles == 20;*/
    int quantity = 0;
    for (int i = 0; i < stash.size(); ++i) {
        for (int j = 0; j < stash.at(i).size(); ++j) {
            quantity++;
        }
    }
    return quantity == 0;
}

int howManyLeftInStash() {
    int quantity = 0;
    for (int i = 0; i < stash.size(); ++i) {
        for (int j = 0; j < stash.at(i).size(); ++j) {
            quantity++;
        }
    }
    return quantity;
}

void startSolvingNew(Tile ***gameField, int startX, int startY) {
    for (int i = 0; i < stash.size(); ++i) {
        for (int j = 0; j < stash.at(i).size(); ++j) {
            solveFirstHalf(gameField[startX][startY], i, i, false);
            printGameField(gameField);
            //bool isAnswer = startCheck(gameField, 0,0);
            //std::cout << startCheck(gameField, isAnswer,0);

            resetGameField(gameField);
//            printGameField(gameField);
        }
    }
}

void solveSecondHalf(Tile *tile, int prevNumber);

bool isPossible(std::vector<int> possibleNumbers, int number) {
    return std::find(possibleNumbers.begin(), possibleNumbers.end(), number) != possibleNumbers.end();
}

void solveFirstHalf(Tile *tile, int prevNumber, int firstHalfDeleted, bool isDeleted) {
    //Bruteforce possible variants for the current tile
    for (int i = 0; i < stash.size(); ++i) {
        if (i == prevNumber) {
            if (isPossible(tile->possibleNumbers, i) && !getAllSecondHalvesByFirst(i).empty()) {
                tile->value = i;
                tile->visited = true;
                printGameField(gameField);

                //Traverse to the next tile
                if (tile->top != nullptr && !tile->top->visited) {
                    solveSecondHalf(tile->top, tile->value);
                }
                if (tile->right != nullptr && !tile->right->visited) {
                    solveSecondHalf(tile->right, tile->value);
                }
                if (tile->bottom != nullptr && !tile->bottom->visited) {
                    solveSecondHalf(tile->bottom, tile->value);
                }
                if (tile->left != nullptr && !tile->left->visited) {
                    solveSecondHalf(tile->left, tile->value);
                }
            }
        } else {
            continue;
        }
    }
    if (howManyLeftInStash() == 0) {
        return;
    }
    // If we have ran out of variants for the tile value, and the game is not over
    tile->visited = false;
    //tile->value = -1;
    std::cout << "Returning at %i: %i" << tile->xCoord << tile->yCoord << std::endl;
    printGameField(gameField);
    if (isDeleted) {
        returnDominoToStash(firstHalfDeleted, prevNumber);
    }
}

void solveFirstHalfFinal(Tile *tile, int prevNumber) {
    //Bruteforce possible variants for the current tile
    for (int i = 0; i < stash.size(); ++i) {
        if (i == prevNumber) {
            if (std::find(tile->possibleNumbers.begin(), tile->possibleNumbers.end(), i) !=
                tile->possibleNumbers.end() && !getAllSecondHalvesByFirst(i).empty()) {
                if (howManyLeftInStash() == 0) {
                    return;
                }
                tile->value = i;
                tile->visited = true;
                printGameField(gameField);
                //Traverse to the next tile
                if (tile->top != nullptr && !tile->top->visited) {
                    solveSecondHalfFinal(tile->top, tile->value);
                }
                if (tile->right != nullptr && !tile->right->visited) {
                    solveSecondHalfFinal(tile->right, tile->value);
                }
                if (tile->bottom != nullptr && !tile->bottom->visited) {
                    solveSecondHalfFinal(tile->bottom, tile->value);
                }
                if (tile->left != nullptr && !tile->left->visited) {
                    solveSecondHalfFinal(tile->left, tile->value);
                }

                if (!isFinishedSolving(gameField, 0, 0)) {
                    tile->visited = false;
                    //tile->value = -1;
                    printGameField(gameField);
                    continue;
                }
            }
        } else {
            continue;
        }
    }
    //If there are no dominos left to place and is not solved yet - return dominos and try another combo
    if (howManyLeftInStash() == 0) {
        return;
    }
}

void solveSecondHalfFinal(Tile *tile, int prevNumber) {
    //Bruteforce possible variants for the current tile
    std::vector<int> leftHalves = getAllSecondHalvesByFirst(prevNumber);

    //Intersect left with possible, then for loop is !empty
    std::vector<int> variantsForTile = intersection(tile->possibleNumbers, leftHalves);
    if (!variantsForTile.empty()) {
        for (int i = 0; i < variantsForTile.size(); ++i) {
            if (howManyLeftInStash() == 0) {
                return;
            }
            tile->value = variantsForTile.at(i);
            tile->visited = true;
            int firstHalfDeleted = prevNumber;
            int secondHalfDeleted = variantsForTile.at(i);
            printGameField(gameField);
            removeDominoFromStash(firstHalfDeleted, secondHalfDeleted);

            //Traverse to the next tile
            if (tile->top != nullptr && !tile->top->visited) {
                solveFirstHalfFinal(tile->top, tile->value);
            }
            if (tile->right != nullptr && !tile->right->visited) {
                solveFirstHalfFinal(tile->right, tile->value);
            }
            if (tile->bottom != nullptr && !tile->bottom->visited) {
                solveFirstHalfFinal(tile->bottom, tile->value);
            }
            if (tile->left != nullptr && !tile->left->visited) {
                solveFirstHalfFinal(tile->left, tile->value);
            }
            if (howManyLeftInStash() == 1) {
                return;
            }

            if (!isFinishedSolving(gameField, 0, 0)) {
                tile->visited = false;
                returnDominoToStash(firstHalfDeleted, secondHalfDeleted);
                printGameField(gameField);
                continue;
            }

        }
        //If there are no dominos left to place and is not solved yet - return dominos and try another combo
    }
    if (howManyLeftInStash() == 0) {
        return;
    }
}

void solveSecondHalf(Tile *tile, int prevNumber) {
    if (howManyLeftInStash() == 0) {
        return;
    }
    int firstHalfDeleted;
    int secondHalfDeleted;
    //Bruteforce possible variants for the current tile
    std::vector<int> leftHalves = getAllSecondHalvesByFirst(prevNumber);

    //Intersect left with possible, then for loop is !empty
    std::vector<int> variantsForTile = intersection(tile->possibleNumbers, leftHalves);
    if (!variantsForTile.empty()) {
        for (int i = 0; i < variantsForTile.size(); ++i) {
            tile->value = variantsForTile.at(i);
            tile->visited = true;

            firstHalfDeleted = prevNumber;
            secondHalfDeleted = variantsForTile.at(i);

            printGameField(gameField);

            removeDominoFromStash(firstHalfDeleted, secondHalfDeleted);

            //Traverse to the next tile
            if (tile->top != nullptr && !tile->top->visited) {
                solveFirstHalf(tile->top, tile->value, firstHalfDeleted, true);
            }
            if (tile->right != nullptr && !tile->right->visited) {
                solveFirstHalf(tile->right, tile->value, firstHalfDeleted, true);
            }
            if (tile->bottom != nullptr && !tile->bottom->visited) {
                solveFirstHalf(tile->bottom, tile->value, firstHalfDeleted, true);
            }
            if (tile->left != nullptr && !tile->left->visited) {
                solveFirstHalf(tile->left, tile->value, firstHalfDeleted, true);
            }
        }
        if (howManyLeftInStash() != 0) {
            tile->visited = false;
            return;
        }

    } else {
        //If there are no dominos left to place and is not solved yet - return dominos and try another combo
        tile->visited = false;
        tile->value = -1;
        std::cout << "Returning at %i: %i" << tile->xCoord << tile->yCoord << std::endl;
        printGameField(gameField);
        return;
    }
}


void solveTileTestFailed(Tile *tile, int prevNumber) {
    isSecondHalfOfDominoSolve = !isSecondHalfOfDominoSolve;
    //If we have first half of Domino, we need to check prevNumber with new one, if the second - find any corresponding number and remove domino
    if (!isSecondHalfOfDominoSolve) {
        //Bruteforce possible variants for the current tile
        for (int i = 0; i < stash.size(); ++i) {
            if (i == prevNumber) {
                if (std::find(tile->possibleNumbers.begin(), tile->possibleNumbers.end(), i) !=
                    tile->possibleNumbers.end() && !getAllSecondHalvesByFirst(i).empty()) {
                    tile->value = i;
                    tile->visited = true;
                    printGameField(gameField);
                    //Traverse to the next tile
                    if (tile->top != nullptr && !tile->top->visited) {
                        solveTileTestFailed(tile->top, tile->value);
                    }
                    if (tile->right != nullptr && !tile->right->visited) {
                        solveTileTestFailed(tile->right, tile->value);
                    }
                    if (tile->bottom != nullptr && !tile->bottom->visited) {
                        solveTileTestFailed(tile->bottom, tile->value);
                    }
                    if (tile->left != nullptr && !tile->left->visited) {
                        solveTileTestFailed(tile->left, tile->value);
                    }
                    if (howManyLeftInStash() == 1 || howManyLeftInStash() == 0) {
                        return;
                    }

                    if (!isFinishedSolving(gameField, 0, 0)) {
                        tile->visited = false;
                        tile->value = -1;
                        printGameField(gameField);
                        continue;
                    }
                }
            } else {
                continue;
            }
        }
        //If there are no dominos left to place and is not solved yet - return dominos and try another combo
        if (howManyLeftInStash() == 0) {
            return;
        }
    } else {
        //Bruteforce possible variants for the current tile
        std::vector<int> leftHalves = getAllSecondHalvesByFirst(prevNumber);

        //Intersect left with possible, then for loop is !empty
        std::vector<int> variantsForTile = intersection(tile->possibleNumbers, leftHalves);
        if (!variantsForTile.empty()) {
            for (int i = 0; i < variantsForTile.size(); ++i) {
                tile->value = variantsForTile.at(i);
                tile->visited = true;
                int firstHalfDeleted = prevNumber;
                int secondHalfDeleted = variantsForTile.at(i);
                printGameField(gameField);
                removeDominoFromStash(firstHalfDeleted, secondHalfDeleted);

                //Traverse to the next tile
                if (tile->top != nullptr && !tile->top->visited) {
                    solveTileTestFailed(tile->top, tile->value);
                }
                if (tile->right != nullptr && !tile->right->visited) {
                    solveTileTestFailed(tile->right, tile->value);
                }
                if (tile->bottom != nullptr && !tile->bottom->visited) {
                    solveTileTestFailed(tile->bottom, tile->value);
                }
                if (tile->left != nullptr && !tile->left->visited) {
                    solveTileTestFailed(tile->left, tile->value);
                }
                if (howManyLeftInStash() == 1 || howManyLeftInStash() == 0) {
                    return;
                }

                if (!isFinishedSolving(gameField, 0, 0)) {
                    tile->visited = false;
                    //tile->value = -1;
                    returnDominoToStash(firstHalfDeleted, secondHalfDeleted);
                    printGameField(gameField);
                    continue;
                }

            }
            //If there are no dominos left to place and is not solved yet - return dominos and try another combo
            if (howManyLeftInStash() == 0) {
                return;
            }
        }
    }
    isSecondHalfOfDominoSolve = !isSecondHalfOfDominoSolve;
}

std::vector<int> getAllSecondHalvesByFirst(int firstHalf) {
    std::set<int> secondHalves(stash.at(firstHalf).begin(), stash.at(firstHalf).end());
    for (int i = 0; i < stash.size(); ++i) {
        for (int j = 0; j < stash.at(i).size(); ++j) {
            if (stash.at(i).at(j) == firstHalf) {
                if (secondHalves.find(stash.at(i).at(j)) == secondHalves.end()) {
                    secondHalves.insert(i);
                }
            }
        }
    }
    std::vector<int> v;
    std::copy(secondHalves.begin(), secondHalves.end(), std::back_inserter(v));
    return v;
}

int getPositionOfElement(std::vector<int> v, int el) {
    return static_cast<int>(std::find(v.begin(), v.end(), el) - v.begin());
}

void removeDominoFromStash(int prevNumber, int currNum) {
    if (currNum > prevNumber) {
        stash.at(currNum).erase(stash.at(currNum).begin() + getPositionOfElement(stash.at(currNum), prevNumber));
    } else if (currNum == prevNumber) {
        stash.at(currNum).erase(stash.at(currNum).begin() + getPositionOfElement(stash.at(currNum), currNum));
    } else if (currNum < prevNumber) {
        stash.at(prevNumber).erase(stash.at(prevNumber).begin() + getPositionOfElement(stash.at(prevNumber), currNum));
    }
}

void returnDominoToStash(int prevNumber, int currNum) {
    if (currNum > prevNumber) {
        stash.at(currNum).push_back(prevNumber);
        std::sort(stash.at(currNum).begin(), stash.at(currNum).end());
    } else if (currNum == prevNumber) {
        stash.at(currNum).push_back(currNum);
        std::sort(stash.at(currNum).begin(), stash.at(currNum).end());
    } else if (currNum < prevNumber) {
        stash.at(prevNumber).push_back(currNum);
        std::sort(stash.at(prevNumber).begin(), stash.at(prevNumber).end());
    }

}

void resetGameField(Tile ***gameField) {
    for (int i = 0; i < TEST_TASK_HEIGHT; ++i) {
        for (int j = 0; j < TEST_TASK_WIDTH; ++j) {
            if (testExample[i][j] == '0') {
                gameField[i][j]->value = -1;
                gameField[i][j]->checked = false;
                gameField[i][j]->visited = false;
            }
        }
    }
}


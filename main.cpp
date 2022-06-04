#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "Tile.h"

static const int TASK_HEIGHT = 5;
static const int TEST_TASK_HEIGHT = 5;

static const int TASK_WIDTH = 6;
static const int TEST_TASK_WIDTH = 6;
std::map<int, std::vector<int>> stash;
bool isSecondHalfOfDomino = true;

void printInputNumbers(char field[TASK_HEIGHT][TASK_WIDTH]);

Tile ***generateGameField(char field[TASK_HEIGHT][TASK_WIDTH]);

void printGameField(Tile ***gameField);

std::vector<int> intersection(std::vector<int> v1,
                              std::vector<int> v2);

void setPossibleNumbersToTiles(Tile ***gameField, std::vector<std::vector<int>> iPossible,
                               std::vector<std::vector<int>> jPossible);

void setAnswerToTheGameField(Tile ***gameField, char answer[TEST_TASK_HEIGHT][TEST_TASK_WIDTH]);

bool startCheck(Tile ***gameField, int startX, int startY);

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

    char testExample[TEST_TASK_HEIGHT][TEST_TASK_WIDTH] = {{'0', '0', ' ', '0', '0', '0'},
                                                           {' ', '0', ' ', ' ', ' ', '0'},
                                                           {'0', '0', ' ', '0', '0', '0'},
                                                           {'0', ' ', ' ', ' ', ' ', '0'},
                                                           {'0', '0', '0', '0', '0', '0'}};

    char testAnswer[TEST_TASK_HEIGHT][TEST_TASK_WIDTH] = {{2,   1,   ' ', 3,   3,   3},
                                                          {' ', 1,   ' ', ' ', ' ', 0},
                                                          {1,   1,   ' ', 1,   0,   0},
                                                          {3,   ' ', ' ', ' ', ' ', 0},
                                                          {3,   2,   2,   2,   2,   0}};
    printInputNumbers(testExample);
    Tile ***gameField = generateGameField(testExample);
    setPossibleNumbersToTiles(gameField, test_iPossible, test_jPossible);
    printGameField(gameField);
    setAnswerToTheGameField(gameField, testAnswer);
    printGameField(gameField);
    std::cout << std::boolalpha;
    std::cout << "Is the answer correct?: " << static_cast<bool>(startCheck(gameField, 0, 0));
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
                        Tile *newTile = new Tile(i - 1, j);
                        tempTile->top = newTile;
                        gameField[i - 1][j] = newTile;
                    }
                }
                if (field[i][j + 1] == '0') {
                    if (gameField[i][j + 1] != nullptr && (j + 1) < TASK_WIDTH) {
                        tempTile->right = gameField[i][j + 1];
                    } else if ((j + 1) < TASK_WIDTH) {
                        Tile *newTile = new Tile(i, j + 1);
                        tempTile->right = newTile;
                        gameField[i][j + 1] = newTile;
                    }
                }
                if (field[i + 1][j] == '0') {
                    if (gameField[i + 1][j] != nullptr && (i + 1) < TASK_HEIGHT) {
                        tempTile->bottom = gameField[i + 1][j];
                    } else if ((i + 1) < TASK_HEIGHT) {
                        Tile *newTile = new Tile(i + 1, j);
                        tempTile->bottom = newTile;
                        gameField[i + 1][j] = newTile;
                    }
                }
                if (field[i][j - 1] == '0') {
                    if (gameField[i][j - 1] != nullptr && (j - 1) >= 0) {
                        tempTile->left = gameField[i][j - 1];
                    } else if ((j - 1) >= 0) {
                        Tile *newTile = new Tile(i, j - 1);
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

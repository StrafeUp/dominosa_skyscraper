//
// Created by bohdankol on 6/8/2022.
//

#include <set>
#include <algorithm>
#include <iostream>
#include "Task.h"
#include "utilities.h"


Task::Task() {
    this->resetStash();
    printInputNumbers();
    this->gameField = generateGameField(testExample);
    setPossibleNumbersToTiles();
    printGameField();
}

Task::~Task() {

}

void Task::setPossibleNumbersToTiles() {
    for (int i = 0; i < TASK_HEIGHT; ++i) {
        for (int j = 0; j < TASK_WIDTH; ++j) {
            if (gameField[i][j] != nullptr) {
                gameField[i][j]->possibleNumbers = vectorIntersection(iPossible[i], jPossible[j]);
            }
        }
    }
}

void Task::solve(int startX, int startY, int startIndex) {
    solveFirstHalfFinal(gameField[startX][startY], startIndex);
    //Replace with check
    return;
}

Tile ***Task::generateGameField(char field[TASK_HEIGHT][TASK_WIDTH]) {
    // Save Tiles in 2d array, fill it in 2 loops, while constructing all the pointers

    Tile ***tempGameField = new Tile **[TASK_HEIGHT];

    //Fill the newly created space with nullpointers
    for (int i = 0; i < TASK_HEIGHT; ++i) {
        tempGameField[i] = new Tile *[TASK_WIDTH];
        for (int j = 0; j < TASK_WIDTH; ++j) {
            tempGameField[i][j] = nullptr;
        }
    }

    for (int i = 0; i < TASK_HEIGHT; ++i) {
        for (int j = 0; j < TASK_WIDTH; ++j) {
            if (field[i][j] == '0') {
                Tile *tempTile;
                //Check if Tile already was created and placed on the game field
                if (tempGameField[i][j] == nullptr) {
                    tempTile = new Tile(i, j);
                } else {
                    tempTile = tempGameField[i][j];
                }

                //Check surroundings for existing tiles or map values from input to the objects
                if (field[i - 1][j] == '0') {
                    if (tempGameField[i - 1][j] != nullptr && (i - 1) >= 0) {
                        tempTile->top = tempGameField[i - 1][j];
                    } else if ((i - 1) >= 0) {
                        Tile *newTile = new Tile(j, i - 1);
                        tempTile->top = newTile;
                        tempGameField[i - 1][j] = newTile;
                    }
                }
                if (field[i][j + 1] == '0') {
                    if (tempGameField[i][j + 1] != nullptr && (j + 1) < TASK_WIDTH) {
                        tempTile->right = tempGameField[i][j + 1];
                    } else if ((j + 1) < TASK_WIDTH) {
                        Tile *newTile = new Tile(j, i + 1);
                        tempTile->right = newTile;
                        tempGameField[i][j + 1] = newTile;
                    }
                }
                if (field[i + 1][j] == '0') {
                    if (tempGameField[i + 1][j] != nullptr && (i + 1) < TASK_HEIGHT) {
                        tempTile->bottom = tempGameField[i + 1][j];
                    } else if ((i + 1) < TASK_HEIGHT) {
                        Tile *newTile = new Tile(j + 1, i);
                        tempTile->bottom = newTile;
                        tempGameField[i + 1][j] = newTile;
                    }
                }
                if (field[i][j - 1] == '0') {
                    if (tempGameField[i][j - 1] != nullptr && (j - 1) >= 0) {
                        tempTile->left = tempGameField[i][j - 1];
                    } else if ((j - 1) >= 0) {
                        Tile *newTile = new Tile(j, i - 1);
                        tempTile->left = newTile;
                        tempGameField[i][j - 1] = newTile;
                    }

                }
                //Place new tile in the game field
                tempGameField[i][j] = tempTile;
            } else {
                //Place an empty tile in the game field
                tempGameField[i][j] = nullptr;
            }
        }
    }
    return tempGameField;
}

std::vector<int> Task::getAllSecondHalvesByFirst(int firstHalf) {
    std::set<int> secondHalves(stash.at(firstHalf).begin(), stash.at(firstHalf).end());
    for (int i = 0; i < int(stash.size()); ++i) {
        for (int j = 0; j < int(stash.at(i).size()); ++j) {
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

void Task::removeDominoFromStash(int prevNumber, int currNum) {
    //Remove by key and by value -> key (4-6 and 6-4 are the same)
    if (currNum > prevNumber) {
        stash.at(currNum).erase(stash.at(currNum).begin() + getPositionOfElement(stash.at(currNum), prevNumber));
    } else if (currNum == prevNumber) {
        stash.at(currNum).erase(stash.at(currNum).begin() + getPositionOfElement(stash.at(currNum), currNum));
    } else if (currNum < prevNumber) {
        stash.at(prevNumber).erase(stash.at(prevNumber).begin() + getPositionOfElement(stash.at(prevNumber), currNum));
    }
}

void Task::returnDominoToStash(int prevNumber, int currNum) {
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

void Task::resetStash() {
    stash.clear();
    int counter = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j <= counter; ++j) {
            stash[i].push_back(j);
        }
        counter++;
    }
}

void Task::resetGameField() {
    for (int i = 0; i < TASK_HEIGHT; ++i) {
        for (int j = 0; j < TASK_WIDTH; ++j) {
            if (testExample[i][j] == '0') {
                gameField[i][j]->value = -1;
                gameField[i][j]->checked = false;
                gameField[i][j]->visited = false;
            }
        }
    }
}

int Task::howManyLeftInStash() {
    int quantity = 0;
    for (int i = 0; i < int(stash.size()); ++i) {
        for (int j = 0; j < int(stash.at(i).size()); ++j) {
            quantity++;
        }
    }
    return quantity;
}

void Task::solveFirstHalfFinal(Tile *tile, int prevNumber) {
    //Bruteforce possible variants for the current tile
    for (int i = 0; i < int(stash.size()); ++i) {
        if (i == prevNumber) {
            if (vectorContains(tile->possibleNumbers, i) && !getAllSecondHalvesByFirst(i).empty()) {
                if (howManyLeftInStash() == 0) {
                    return;
                }
                tile->value = i;
                tile->visited = true;
                printGameField();
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

                if (howManyLeftInStash() != 0) {
                    tile->visited = false;
                    printGameField();
                    continue;
                }
            }
        } else {
            continue;
        }
    }
    if (howManyLeftInStash() == 0) {
        return;
    }
}

void Task::solveSecondHalfFinal(Tile *tile, int prevNumber) {
    //Bruteforce possible variants for the current tile
    std::vector<int> leftHalves = getAllSecondHalvesByFirst(prevNumber);

    //Intersect left with possible, then for loop is !empty
    std::vector<int> variantsForTile = vectorIntersection(tile->possibleNumbers, leftHalves);
    if (!variantsForTile.empty()) {
        for (int i = 0; i < int(variantsForTile.size()); ++i) {
            if (howManyLeftInStash() == 0) {
                return;
            }
            tile->value = variantsForTile.at(i);
            tile->visited = true;
            int firstHalfDeleted = prevNumber;
            int secondHalfDeleted = variantsForTile.at(i);
            printGameField();
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

            if (howManyLeftInStash() != 0) {
                tile->visited = false;
                returnDominoToStash(firstHalfDeleted, secondHalfDeleted);
                printGameField();
                continue;
            }

        }
    }
    if (howManyLeftInStash() == 0) {
        return;
    }
}

void Task::printInputNumbers() {
    for (int i = 0; i < TASK_HEIGHT; ++i) {
        for (int j = 0; j < TASK_WIDTH; ++j) {
            std::cout << testExample[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Task::printGameField() {
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

void Task::reset() {
    resetStash();
    resetGameField();
}

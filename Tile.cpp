//
// Created by bohdankol on 6/2/2022.
//

#include <set>
#include "Tile.h"

Tile::Tile(int xCoord, int yCoord) : xCoord(xCoord), yCoord(yCoord) {
    this->top = nullptr;
    this->right = nullptr;
    this->bottom = nullptr;
    this->left = nullptr;
    this->visited = false;
    this->value = -1;
}

Tile::~Tile() {
}

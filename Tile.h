//
// Created by bohdankol on 6/2/2022.
//

#ifndef LAB1_TILE_H
#define LAB1_TILE_H


#include <vector>

class Tile {
public:
    Tile(int xCoord, int yCoord);

    virtual ~Tile();

public:
    Tile *top, *right, *bottom, *left;
    std::vector<int> possibleNumbers;
    bool visited;
    int xCoord;
    int yCoord;
    int value;
};


#endif //LAB1_TILE_H

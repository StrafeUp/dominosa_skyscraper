//
// Created by bohdankol on 6/8/2022.
//

#ifndef LAB1_UTILITIES_H
#define LAB1_UTILITIES_H

#include <vector>
#include <algorithm>

std::vector<int> vectorIntersection(std::vector<int> v1,
                                    std::vector<int> v2);

bool vectorContains(std::vector<int> possibleNumbers, int number);

int getPositionOfElement(std::vector<int> v, int el);
#endif //LAB1_UTILITIES_H

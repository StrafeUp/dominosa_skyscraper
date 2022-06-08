//
// Created by bohdankol on 6/8/2022.
//


#include "utilities.h"

std::vector<int> vectorIntersection(std::vector<int> v1,
                                    std::vector<int> v2) {
    std::vector<int> v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(), v1.end(),
                          v2.begin(), v2.end(),
                          back_inserter(v3));
    return v3;
}

bool vectorContains(std::vector<int> possibleNumbers, int number) {
    return std::find(possibleNumbers.begin(), possibleNumbers.end(), number) != possibleNumbers.end();
}

int getPositionOfElement(std::vector<int> v, int el) {
    return static_cast<int>(std::find(v.begin(), v.end(), el) - v.begin());
}
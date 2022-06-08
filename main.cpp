#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <thread>

#include "Task.h"
void doSomething(int index){
    Task task = Task();
    task.solve(0, 0, index);
}

int main() {
    std::vector<std::thread> tasks(3);
    for (int i = 0; i < 3; ++i) {
        tasks[i] = std::thread(doSomething, i);
    }

    for (auto& th : tasks) {
        th.join();
    }
    return 0;
}


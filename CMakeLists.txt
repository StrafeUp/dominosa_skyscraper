cmake_minimum_required(VERSION 3.22)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab1 main.cpp Tile.cpp Tile.h utilities.h utilities.cpp Task.cpp Task.h)

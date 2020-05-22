cmake_minimum_required(VERSION 3.13)
project(382)

set(CMAKE_CXX_STANDARD 14)

add_executable(382 TicTacToe/Strategy.hpp TicTacToe/TicTacToe.hpp TicTacToe/TicTacTile.hpp main.cpp
        Wumpus/Tile.hpp Wumpus/Wumpus.hpp)
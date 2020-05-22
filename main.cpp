/*
 * This file is part of project to see if we can
 * use Github classroom for the final project in 382.
 *
 * This program shows how to start two different games
 * built in two different directories.
 *
 */
#include <iostream>
#include "TicTacToe/TicTacToe.hpp"
#include "Wumpus/Wumpus.hpp"

using namespace std;

int main() {
    cout << "Which game?" << endl;
    cout << "1 Wumpus" << endl;
    cout << "2 TicTacToe" << endl;
    cout << endl;

    int choice;
    cin >> choice;

    if (choice == 1) {
        Wumpus game;
        game.startGame();
    }

    if (choice == 2) {
        TicTacToe game;
        game.startGame();
    }

    return 0;
}
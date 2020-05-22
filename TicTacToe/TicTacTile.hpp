/* Programmers: Jessmer John Palanca and Ariel Villasenor
 * This class creates a tile object for the TicTacToe board.
 * It has a data member that stores the special character of the
 * object.
 */

#ifndef INC_382_TICTACTILE_HPP
#define INC_382_TICTACTILE_HPP

#include <iostream>

using namespace std;

class TicTacTile {
private:
    string special;
public:
    TicTacTile() {
        special = "_";
    }

    void SetSpecial(string &str) {
        special = str;
    }

    string GetSpecial() const {
        return special;
    }

    void PrintSpecial() {
        cout << special << " ";
    }
};

#endif //INC_382_TICTACTILE_HPP

/* Programmers: Ariel Villaseñor and Jessmer John Palanca
 * In our "Strategy.hpp" file, we use an inheritance class. Strategy is the class
 * and RandomAI and IntermediateAI are subclasses of strategy. Some functions that are
 * in the public of Strategy are "ReturnIndex", "SetBoard" and "ChooseOpenTile".
 * "ChooseOpenTile" is a virtual function since the implementation will change between
 * classes.*/
#ifndef INC_382_STRATEGY_HPP
#define INC_382_STRATEGY_HPP

#include "TicTacTile.hpp"
#include <vector>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class Strategy {
protected:
    int index;
    vector<vector<TicTacTile>> Board;

public:
    int ReturnIndex() {
        return index;
    }

    Strategy(vector<vector<TicTacTile>> board) {
        Board = board;
    }

    virtual void ChooseOpenTile() {}

    void SetBoard(vector<vector<TicTacTile>> board) {
        Board = board;
    }


};

class RandomAI : public Strategy {
public:
    RandomAI(vector<vector<TicTacTile>> board) : Strategy(board) {//THIS WAS PREVIOUSLY "&board"
        srand(time(nullptr));
    }

    void ChooseOpenTile() {
        index = rand() % 9;
        int row = index / 3;
        int col = index % 3;
        while (Board[row][col].GetSpecial() != "_") {
            index = rand() % 9;
            row = index / 3;
            col = index % 3;
        }
    }
};

class IntermediateAI : public Strategy {
public:
    IntermediateAI(vector<vector<TicTacTile>> board) : Strategy(board) {
        srand(time(nullptr));
    }

    void CheckIfWinning() {
        string X = "O";
        string UnderScore = "_";
        for (int i = 0; i < Board.size(); i++) {
            for (int j = 0; j < Board[i].size(); j++) {
                if (Board[i][0].GetSpecial() == X and Board[i][1].GetSpecial() == X and
                    Board[i][2].GetSpecial() == UnderScore) {
                    index = i * 3 + 2;
                    return;
                } else if (Board[i][0].GetSpecial() == X and Board[i][1].GetSpecial() == UnderScore and
                           Board[i][2].GetSpecial() == X) {
                    index = i * 3 + 1;
                    return;
                } else if (Board[i][0].GetSpecial() == UnderScore and Board[i][1].GetSpecial() == X and
                           Board[i][2].GetSpecial() == X) {
                    index = i * 3;
                    return;
                } else if (Board[0][j].GetSpecial() == X and Board[1][j].GetSpecial() == X and
                           Board[2][j].GetSpecial() == UnderScore) {
                    index = 2 * 3 + j;
                    return;
                } else if (Board[0][j].GetSpecial() == X and Board[1][j].GetSpecial() == UnderScore and
                           Board[2][j].GetSpecial() == X) {
                    index = 1 * 3 + j;
                    return;
                } else if (Board[0][j].GetSpecial() == UnderScore and Board[1][j].GetSpecial() == X and
                           Board[2][j].GetSpecial() == X) {
                    index = j;
                    return;
                }
                /*******************************************************************************************************/
            }
        }
        if (Board[0][0].GetSpecial() == UnderScore and Board[1][1].GetSpecial() == X and
            Board[2][2].GetSpecial() == X) {
            index = 0;
            return;
        } else if (Board[0][0].GetSpecial() == X and Board[1][1].GetSpecial() == UnderScore and
                   Board[2][2].GetSpecial() == X) {
            index = 4;
            return;
        } else if (Board[0][0].GetSpecial() == X and Board[1][1].GetSpecial() == X and
                   Board[2][2].GetSpecial() == UnderScore) {
            index = 8;
            return;
        } else if (Board[2][0].GetSpecial() == X and Board[1][1].GetSpecial() == X and
                   Board[0][2].GetSpecial() == UnderScore) {
            index = 2;
            return;
        } else if (Board[2][0].GetSpecial() == X and Board[1][1].GetSpecial() == UnderScore and
                   Board[0][2].GetSpecial() == X) {
            index = 4;
            return;
        } else if (Board[2][0].GetSpecial() == UnderScore and Board[1][1].GetSpecial() == X and
                   Board[0][2].GetSpecial() == X) {
            index = 6;
            return;
        } else {
            ChooseOpenTile();
        }

    }

    void ChooseOpenTile() {
        string X = "X";
        string UnderScore = "_";
        for (int i = 0; i < Board.size(); i++) {
            for (int j = 0; j < Board[i].size(); j++) {
                if (Board[i][0].GetSpecial() == X and Board[i][1].GetSpecial() == X and
                    Board[i][2].GetSpecial() == UnderScore) {
                    index = i * 3 + 2;
                    return;
                } else if (Board[i][0].GetSpecial() == X and Board[i][1].GetSpecial() == UnderScore and
                           Board[i][2].GetSpecial() == X) {
                    index = i * 3 + 1;
                    return;
                } else if (Board[i][0].GetSpecial() == UnderScore and Board[i][1].GetSpecial() == X and
                           Board[i][2].GetSpecial() == X) {
                    index = i * 3;
                    return;
                } else if (Board[0][j].GetSpecial() == X and Board[1][j].GetSpecial() == X and
                           Board[2][j].GetSpecial() == UnderScore) {
                    index = 2 * 3 + j;
                    return;
                } else if (Board[0][j].GetSpecial() == X and Board[1][j].GetSpecial() == UnderScore and
                           Board[2][j].GetSpecial() == X) {
                    index = 1 * 3 + j;
                    return;
                } else if (Board[0][j].GetSpecial() == UnderScore and Board[1][j].GetSpecial() == X and
                           Board[2][j].GetSpecial() == X) {
                    index = j;
                    return;
                }
                /*******************************************************************************************************/
            }
        }
        if (Board[0][0].GetSpecial() == UnderScore and Board[1][1].GetSpecial() == X and
            Board[2][2].GetSpecial() == X) {
            index = 0;
            return;
        } else if (Board[0][0].GetSpecial() == X and Board[1][1].GetSpecial() == UnderScore and
                   Board[2][2].GetSpecial() == X) {
            index = 4;
            return;
        } else if (Board[0][0].GetSpecial() == X and Board[1][1].GetSpecial() == X and
                   Board[2][2].GetSpecial() == UnderScore) {
            index = 8;
            return;
        } else if (Board[2][0].GetSpecial() == X and Board[1][1].GetSpecial() == X and
                   Board[0][2].GetSpecial() == UnderScore) {
            index = 2;
            return;
        } else if (Board[2][0].GetSpecial() == X and Board[1][1].GetSpecial() == UnderScore and
                   Board[0][2].GetSpecial() == X) {
            index = 4;
            return;
        } else if (Board[2][0].GetSpecial() == UnderScore and Board[1][1].GetSpecial() == X and
                   Board[0][2].GetSpecial() == X) {
            index = 6;
            return;
        } else {
            index = rand() % 9;
            int row = index / 3;
            int col = index % 3;
            while (Board[row][col].GetSpecial() != "_") {
                index = rand() % 9;
                row = index / 3;
                col = index % 3;
            }
        }

    }

};

#endif //INC_382_STRATEGY_HPP

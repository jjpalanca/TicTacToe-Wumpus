/* Programmers: Jessmer John Palanca and Ariel Villaseñor
 * This file is part of project to see if we can
 * use Github classroom for the final project in 382.
 * In our TicTacToe.hpp file, it is used to run all of
 * our code. This class creates the TicTacToe game where
 * a human can play against an AI (RandomAI or IntermediateAI)
 * on a 3x3 TicTacToe game board.The human gets to move first
 * and is marked as "X" while the AI marked as "O". This game
 * prints an error message if the user enters and invalid input,
 * ie. 3 1 ("Out of range") or "Square taken" if a tile is
 * occupied. The game stops if the winner is determine (prints
 * the winner) or there is a tie.
 */
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <memory>
#include "Strategy.hpp"
#include "TicTacTile.hpp"

using namespace std;

class TicTacToe {
private:
    vector<vector<TicTacTile>> Board;
    string winner;
    string message;
    int userRow;
    int userCol;
    int AIrow;
    int AIcol;
    bool gameover;
public:
    void startGame() {
        int count = 0;
        string start;
        cout << "Play a game of Tic Tac Toe" << endl;
        cout << "Compete against a RandomAI or IntermediateAI" << endl;
        cout << "Enter 'R' for RandomAI or 'I' for IntermediateAI: ";
        cin >> start;
        gameover = false;
        GenerateBoard();
        if (start == "R") {
            while (!gameover) {
                int AIindex;
                int input1;
                int input2;
                cout << "Enter row and column: ";
                cin >> input1;
                cin >> input2;
                userRow = input1;
                userCol = input2;
                if (checkTile(userRow, userCol)) {
                    AssignTile(userRow, userCol, "X");
                    count += 1;
                    if (count < 5) {
                        RandomAI AI(Board);
                        AI.ChooseOpenTile();
                        AIindex = AI.ReturnIndex();
                        AIMove(AIindex);
                        PrintBoard();
                        if (checkWinner()) {
                            PrintWinner();
                        }
                    } else {
                        PrintBoard();
                        if (checkWinner()) {
                            PrintWinner();
                        } else {
                            cout << "GameOver" << endl;
                            gameover = true;
                        }
                    }
                }
            }
        }
        if (start == "I") {
            while (!gameover) {
                int AIindex;
                int input1;
                int input2;
                cout << "Enter row and column: ";
                cin >> input1;
                cin >> input2;
                userRow = input1;
                userCol = input2;
                if (checkTile(userRow, userCol)) {
                    AssignTile(userRow, userCol, "X");
                    count += 1;
                    if (count < 5) {
                        IntermediateAI AI(Board);
                        AI.CheckIfWinning();
                        AIindex = AI.ReturnIndex();
                        AIMove(AIindex);
                        PrintBoard();
                        if (checkWinner()) {
                            PrintWinner();
                        }
                    } else {
                        PrintBoard();
                        if (checkWinner()) {
                            PrintWinner();
                        } else {
                            cout << "GameOver" << endl;
                            gameover = true;
                        }
                    }
                }
            }
        }
    }

    void AIMove(int index) {
        AIrow = index / 3;
        AIcol = index % 3;
        AssignTile(AIrow, AIcol, "O");
    }

    void GenerateBoard() {
        vector<vector<TicTacTile>> temp(3, vector<TicTacTile>(3));
        Board = temp;
    }

    void PrintBoard() {
        for (auto x: Board) {
            for (auto y: x) {
                y.PrintSpecial();
            }
            cout << endl;
        }
    }

    void AssignTile(int row, int col, string str) {
        Board[row][col].SetSpecial(str);
    }

    bool checkTile(int row, int col) {
        if (row < 0 or row > 2 or col < 0 or col > 2) {
            message = "Out of range";
            cout << message << endl;
            return false;
        } else if (Board[row][col].GetSpecial() == "X" or
                   Board[row][col].GetSpecial() == "O") {
            message = "Square Taken";
            cout << message << endl;
            return false;
        } else {
            return true;
        }
    }

    bool checkWinner() {
        for (auto i = 0; i < 3; i++) {
            if (Board[i][0].GetSpecial() != "_" and Board[i][0].GetSpecial() == Board[i][1].GetSpecial() and
                Board[i][0].GetSpecial() == Board[i][2].GetSpecial()) {
                winner = Board[i][0].GetSpecial();
                gameover = true;
                return true;
            }
            if (Board[0][i].GetSpecial() != "_" and Board[0][i].GetSpecial() == Board[1][i].GetSpecial() and
                Board[0][i].GetSpecial() == Board[2][i].GetSpecial()) {
                winner = Board[0][i].GetSpecial();
                gameover = true;
                return true;
            }
        }
        if (Board[0][0].GetSpecial() != "_" and Board[0][0].GetSpecial() == Board[1][1].GetSpecial() and
            Board[0][0].GetSpecial() == Board[2][2].GetSpecial()) {
            winner = Board[0][0].GetSpecial();
            cout << endl;
            gameover = true;
            return true;
        }
        if (Board[2][0].GetSpecial() != "_" and Board[2][0].GetSpecial() == Board[1][1].GetSpecial() and
            Board[2][0].GetSpecial() == Board[0][2].GetSpecial()) {
            winner = Board[2][0].GetSpecial();
            gameover = true;
            return true;
        }
        return false;
    }

    void PrintWinner() {
        if (winner == "X") {
            cout << " >> The human wins" << endl;
            cout << "GameOver" << endl;
            gameover = true;
        } else if (winner == "O") {
            cout << " >> The AI wins" << endl;
            cout << "GameOver" << endl;
            gameover = true;
        }
    }

    vector<vector<TicTacTile>> ReturnBoard() {
        return Board;
    }

    string ReturnSpecial(int row, int col) {
        return Board[row][col].GetSpecial();
    }

    bool ReturnGameOver() {
        return gameover;
    }

    string ReturnWinner() {
        return winner;
    }

    string ReturnMessage() {
        return message;
    }
};
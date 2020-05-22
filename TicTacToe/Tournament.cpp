/* Programmers: Jessmer John Palanca and Ariel Villaseñor
 * The "Tournament.cpp" file makes the 2 different AI's competer against
 * each other. On average, our Intermediate AI wins 90% of the time, will
 * our Random AI wins 1%-2% of the time. There is usually a tie 10% of the
 * time.
 * */
#include <iostream>
#include "TicTacToe.hpp"

int main() {
    cout << "Works" << endl;
    int i = 0;
    int NumberOfSmartWins = 0;
    int NumberOfDumbWins = 0;
    int ties = 0;
    TicTacToe game;
    IntermediateAI Smart(game.ReturnBoard());
    RandomAI Dumb(game.ReturnBoard());
    while (i < 1000) {
        game.GenerateBoard();
        bool GameOver = false;
        int count = 0;
        while (!GameOver) {
            Smart.SetBoard(game.ReturnBoard());
            Smart.CheckIfWinning();
            int row = Smart.ReturnIndex() / 3;
            int col = Smart.ReturnIndex() % 3;
            game.AssignTile(row, col, "O");
            count += 1;
            if (game.checkWinner()) {
                GameOver = true;
                NumberOfSmartWins++;
            } else if (count == 5) {
                ties++;
                GameOver = true;
            } else {
                Dumb.SetBoard(game.ReturnBoard());
                Dumb.ChooseOpenTile();
                row = Dumb.ReturnIndex() / 3;
                col = Dumb.ReturnIndex() % 3;
                game.AssignTile(row, col, "X");
                if (game.checkWinner()) {
                    GameOver = true;
                    NumberOfDumbWins++;
                }
            }
        }
        i++;
    }
    double TotalSmartWins = (NumberOfSmartWins / 10.0);
    double TotalDumbWins = (NumberOfDumbWins / 10.0);
    double TotalTies = (ties / 10.0);
    cout << "IntermediateAI wins: " << TotalSmartWins << "%" << endl;
    cout << "RandomAI wins: " << TotalDumbWins << "%" << endl;
    cout << "Ties: " << TotalTies << "%" << endl;
    return 0;
}


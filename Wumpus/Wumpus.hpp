#ifndef INC_382_WUMPUS_HPP
#define INC_382_WUMPUS_HPP

#include <iostream>
#include <vector>
#include "Tile.hpp"
#include <ctime>
/* Programmer: Ariel Villasenor and Jessmer John Palanca
 *
 * This class creates a Wumpus game object that initially creates a 12x12 grid of Tile objects,
 * assign the coordinates of the Wumpus, n number of SlimePits, and the Hunter randomly. The Wumpus is
 * surrounded by blood, each slimepit is surrounded by slime. A goop is placed when there is
 * an overlapping between blood and slime. The hunter is initially placed on a tile that there is no
 * blood, slime, pits, goop, and wumpus. This class has a move function that lets the hunter moves one cell
 * in 4 directions(n, s, w, e). If the hunter moves to a cell that has blood, slime, or goop,
 * it prints a warning message. If the hunter moves into a cell that has a pit or wumpus, the hunter dies and
 * the game is over. This class also has a shoot arrow function that lets the hunter shoots an arrow in 4 directions
 * (n, s, w, e). If the hunter shoots the arrow and hits the wumpus, the hunter wins and the game is over, otherwise,
 * the hunter lost because the arrow wraps around and kills the hunter and the game is over.
 */
using namespace std;

class Wumpus {
private:
    vector<vector<Tile>> Board;
    bool endgame;
    string message;
    int WumpusIndex;
    int Hunter_Row_Pos;
    int Hunter_Col_Pos;
    int Wrow;
    int Wcol;

public:
    void startGame() {
        cout << "Play a game of Wumpus!\n";
        GenerateBoard();
        assignTiles();
        print();
        endgame = false;
        while (!endgame) {
            Move();
            if (!endgame) {
                print();
                CheckTile();
            }
        }
    }

    void GenerateBoard() {
        vector<vector<Tile>> temp(12, vector<Tile>(12));
        Board = temp;
    }

    void assignTiles() {
        srand(time(nullptr));
        int Prow;
        int Pcol;
        WumpusIndex = rand() % 144;
        Wrow = WumpusIndex / 12;
        Wcol = WumpusIndex % 12;
        string W = "W";
        Board[Wrow][Wcol].SetSpecial(W);
        setBlood(Wrow, Wcol);
        setSlimePits();
        setHunter();
    }

    void print() const {
        for (auto row:Board) {
            for (auto col: row) {
                col.PrintSpecial();
            }
            cout << endl;
        }
    }

    void setHunter() {
        srand(time(nullptr));
        string O = "O";
        int hunterIndex;
        hunterIndex = rand() % 144;
        Hunter_Row_Pos = hunterIndex / 12;
        Hunter_Col_Pos = hunterIndex % 12;
        while (Board[Hunter_Row_Pos][Hunter_Col_Pos].getSpecial() == "W" or
               Board[Hunter_Row_Pos][Hunter_Col_Pos].getSpecial() == "B" or
               Board[Hunter_Row_Pos][Hunter_Col_Pos].getSpecial() == "P" or
               Board[Hunter_Row_Pos][Hunter_Col_Pos].getSpecial() == "S" or
               Board[Hunter_Row_Pos][Hunter_Col_Pos].getSpecial() == "G") {
            hunterIndex = rand() % 144;
            Hunter_Row_Pos = hunterIndex / 12;
            Hunter_Col_Pos = hunterIndex % 12;
        }
        Board[Hunter_Row_Pos][Hunter_Col_Pos].SetHunterOn(true);
        Board[Hunter_Row_Pos][Hunter_Col_Pos].SetBeenHere();

    }

    void setSlimePits() {
        srand(time(nullptr));
        int numPits = rand() % 3 + 3;
        int pitIndex;
        string P = "P";
        for (auto i = 0; i < numPits; i++) {
            int Prow;
            int Pcol;
            pitIndex = rand() % 144;
            while (WumpusIndex == pitIndex) {
                pitIndex = rand() % 144;
            }
            Prow = pitIndex / 12;
            Pcol = pitIndex % 12;
            Board[Prow][Pcol].SetSpecial(P);
            setSlime(Prow, Pcol);

        }
    }

    void setSlime(int Prow, int Pcol) {
        if ((Prow >= 1 and Prow <= 10) and (Pcol >= 1 and Pcol <= 10)) {
            Tile top = Board[Prow - 1][Pcol];
            Tile bot = Board[Prow + 1][Pcol];
            Tile left = Board[Prow][Pcol - 1];
            Tile right = Board[Prow][Pcol + 1];
            slimeOrGoop(top, Prow - 1, Pcol);
            slimeOrGoop(bot, Prow + 1, Pcol);
            slimeOrGoop(left, Prow, Pcol - 1);
            slimeOrGoop(right, Prow, Pcol + 1);
        } else if (Prow == 0 and Pcol >= 1 and Pcol <= 10) {
            Tile top = Board[11][Pcol];
            Tile bot = Board[Prow + 1][Pcol];
            Tile left = Board[Prow][Pcol - 1];
            Tile right = Board[Prow][Pcol + 1];
            slimeOrGoop(top, 11, Pcol);
            slimeOrGoop(bot, Prow + 1, Pcol);
            slimeOrGoop(left, Prow, Pcol - 1);
            slimeOrGoop(right, Prow, Pcol + 1);
        } else if (Prow == 11 and Pcol >= 1 and Pcol <= 10) {
            Tile top = Board[Prow - 1][Pcol];
            Tile bot = Board[0][Pcol];
            Tile left = Board[Prow][Pcol - 1];
            Tile right = Board[Prow][Pcol + 1];
            slimeOrGoop(top, Prow - 1, Pcol);
            slimeOrGoop(bot, 0, Pcol);
            slimeOrGoop(left, Prow, Pcol - 1);
            slimeOrGoop(right, Prow, Pcol + 1);
        } else if (Pcol == 0 and Prow >= 1 and Prow <= 10) {
            Tile top = Board[Prow - 1][Pcol];
            Tile bot = Board[Prow + 1][Pcol];
            Tile left = Board[Prow][11];
            Tile right = Board[Prow][Pcol + 1];
            slimeOrGoop(top, Prow - 1, Pcol);
            slimeOrGoop(bot, Prow + 1, Pcol);
            slimeOrGoop(left, Prow, 11);
            slimeOrGoop(right, Prow, Pcol + 1);
        } else if (Pcol == 11 and Prow >= 1 and Prow <= 10) {
            Tile top = Board[Prow - 1][Pcol];
            Tile bot = Board[Prow + 1][Pcol];
            Tile left = Board[Prow][Pcol - 1];
            Tile right = Board[Prow][0];
            slimeOrGoop(top, Prow - 1, Pcol);
            slimeOrGoop(bot, Prow + 1, Pcol);
            slimeOrGoop(left, Prow, Pcol - 1);
            slimeOrGoop(right, Prow, 0);
        } else if (Prow == 0 and Pcol == 0) {
            Tile top = Board[11][0];
            Tile bot = Board[1][0];
            Tile left = Board[0][11];
            Tile right = Board[0][1];
            slimeOrGoop(top, 11, 0);
            slimeOrGoop(bot, 1, 0);
            slimeOrGoop(left, 0, 11);
            slimeOrGoop(right, 0, 1);
        } else if (Prow == 0 and Pcol == 11) {
            Tile top = Board[11][11];
            Tile bot = Board[1][11];
            Tile left = Board[0][10];
            Tile right = Board[0][0];
            slimeOrGoop(top, 11, 11);
            slimeOrGoop(bot, 1, 11);
            slimeOrGoop(left, 0, 10);
            slimeOrGoop(right, 0, 0);
        } else if (Prow == 11 and Pcol == 0) {
            Tile top = Board[10][0];
            Tile bot = Board[0][0];
            Tile left = Board[11][11];
            Tile right = Board[11][1];
            slimeOrGoop(top, 10, 0);
            slimeOrGoop(bot, 0, 0);
            slimeOrGoop(left, 11, 11);
            slimeOrGoop(right, 11, 1);
        } else if (Prow == 11 and Pcol == 11) {
            Tile top = Board[10][11];
            Tile bot = Board[0][11];
            Tile left = Board[11][10];
            Tile right = Board[11][0];
            slimeOrGoop(top, 10, 11);
            slimeOrGoop(bot, 0, 11);
            slimeOrGoop(left, 11, 10);
            slimeOrGoop(right, 11, 0);
        }

    }

    void slimeOrGoop(Tile pos, int Prow, int Pcol) {
        string G = "G";
        string S = "S";
        if (pos.getSpecial() == "B") {
            Board[Prow][Pcol].SetSpecial(G);
        } else if (pos.getSpecial() != "W" and pos.getSpecial() != "P") {
            Board[Prow][Pcol].SetSpecial(S);
        }
    }

    void setBlood(int Wrow, int Wcol) {
        string B = "B";
        if ((Wrow >= 2 and Wrow <= 9) && (Wcol >= 2 and Wcol <= 9)) {
            Board[Wrow - 2][Wcol].SetSpecial(B);
            Board[Wrow - 1][Wcol - 1].SetSpecial(B);
            Board[Wrow - 1][Wcol].SetSpecial(B);
            Board[Wrow - 1][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol - 2].SetSpecial(B);
            Board[Wrow][Wcol - 1].SetSpecial(B);
            Board[Wrow][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol + 2].SetSpecial(B);
            Board[Wrow + 1][Wcol - 1].SetSpecial(B);
            Board[Wrow + 1][Wcol].SetSpecial(B);
            Board[Wrow + 1][Wcol + 1].SetSpecial(B);
            Board[Wrow + 2][Wcol].SetSpecial(B);
        } else if (Wrow == 0 && (Wcol >= 2 and Wcol <= 9)) {
            Board[10][Wcol].SetSpecial(B);
            Board[11][Wcol - 1].SetSpecial(B);
            Board[11][Wcol].SetSpecial(B);
            Board[11][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol - 2].SetSpecial(B);
            Board[Wrow][Wcol - 1].SetSpecial(B);
            Board[Wrow][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol + 2].SetSpecial(B);
            Board[Wrow + 1][Wcol - 1].SetSpecial(B);
            Board[Wrow + 1][Wcol].SetSpecial(B);
            Board[Wrow + 1][Wcol + 1].SetSpecial(B);
            Board[Wrow + 2][Wcol].SetSpecial(B);
        } else if (Wrow == 1 && (Wcol >= 2 and Wcol <= 9)) {
            Board[11][Wcol].SetSpecial(B);
            Board[0][Wcol - 1].SetSpecial(B);
            Board[0][Wcol].SetSpecial(B);
            Board[0][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol - 2].SetSpecial(B);
            Board[Wrow][Wcol - 1].SetSpecial(B);
            Board[Wrow][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol + 2].SetSpecial(B);
            Board[Wrow + 1][Wcol - 1].SetSpecial(B);
            Board[Wrow + 1][Wcol].SetSpecial(B);
            Board[Wrow + 1][Wcol + 1].SetSpecial(B);
            Board[Wrow + 2][Wcol].SetSpecial(B);
        } else if (Wrow == 10 && (Wcol >= 2 and Wcol <= 9)) {
            Board[8][Wcol].SetSpecial(B);
            Board[9][Wcol - 1].SetSpecial(B);
            Board[9][Wcol].SetSpecial(B);
            Board[9][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol - 2].SetSpecial(B);
            Board[Wrow][Wcol - 1].SetSpecial(B);
            Board[Wrow][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol + 2].SetSpecial(B);
            Board[Wrow + 1][Wcol - 1].SetSpecial(B);
            Board[Wrow + 1][Wcol].SetSpecial(B);
            Board[Wrow + 1][Wcol + 1].SetSpecial(B);
            Board[0][Wcol].SetSpecial(B);
        } else if (Wrow == 11 && (Wcol >= 2 and Wcol <= 9)) {
            Board[9][Wcol].SetSpecial(B);
            Board[10][Wcol - 1].SetSpecial(B);
            Board[10][Wcol].SetSpecial(B);
            Board[10][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol - 2].SetSpecial(B);
            Board[Wrow][Wcol - 1].SetSpecial(B);
            Board[Wrow][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol + 2].SetSpecial(B);
            Board[0][Wcol - 1].SetSpecial(B);
            Board[0][Wcol].SetSpecial(B);
            Board[0][Wcol + 1].SetSpecial(B);
            Board[1][Wcol].SetSpecial(B);
        } else if (Wcol == 0 && ((Wrow >= 2) and (Wrow <= 9))) {
            Board[Wrow - 2][Wcol].SetSpecial(B);
            Board[Wrow - 1][11].SetSpecial(B);
            Board[Wrow - 1][Wcol].SetSpecial(B);
            Board[Wrow - 1][Wcol + 1].SetSpecial(B);
            Board[Wrow][10].SetSpecial(B);
            Board[Wrow][11].SetSpecial(B);
            Board[Wrow][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol + 2].SetSpecial(B);
            Board[Wrow + 1][11].SetSpecial(B);
            Board[Wrow + 1][0].SetSpecial(B);
            Board[Wrow + 1][1].SetSpecial(B);
            Board[Wrow + 2][0].SetSpecial(B);
        } else if (Wcol == 1 && (Wrow >= 2 and Wrow <= 9)) {
            //cout<<"1"<<endl;
            Board[Wrow - 2][Wcol].SetSpecial(B);
            Board[Wrow - 1][Wcol - 1].SetSpecial(B);
            Board[Wrow - 1][Wcol].SetSpecial(B);
            Board[Wrow - 1][Wcol + 1].SetSpecial(B);
            Board[Wrow][11].SetSpecial(B);
            Board[Wrow][Wcol - 1].SetSpecial(B);
            Board[Wrow][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol + 2].SetSpecial(B);
            Board[Wrow + 1][Wcol - 1].SetSpecial(B);
            Board[Wrow + 1][Wcol].SetSpecial(B);
            Board[Wrow + 1][Wcol + 1].SetSpecial(B);
            Board[Wrow + 2][Wcol].SetSpecial(B);
        } else if (Wcol == 10 && (Wrow >= 2 and Wrow <= 9)) {
            Board[Wrow - 2][Wcol].SetSpecial(B);
            Board[Wrow - 1][Wcol - 1].SetSpecial(B);
            Board[Wrow - 1][Wcol].SetSpecial(B);
            Board[Wrow - 1][Wcol + 1].SetSpecial(B);
            Board[Wrow][Wcol - 2].SetSpecial(B);
            Board[Wrow][Wcol - 1].SetSpecial(B);
            Board[Wrow][Wcol + 1].SetSpecial(B);
            Board[Wrow][0].SetSpecial(B);
            Board[Wrow + 1][Wcol - 1].SetSpecial(B);
            Board[Wrow + 1][Wcol].SetSpecial(B);
            Board[Wrow + 1][Wcol + 1].SetSpecial(B);
            Board[Wrow + 2][Wcol].SetSpecial(B);
        } else if (Wcol == 11 && (Wrow >= 2 and Wrow <= 9)) {
            Board[Wrow - 2][Wcol].SetSpecial(B);
            Board[Wrow - 1][Wcol - 1].SetSpecial(B);
            Board[Wrow - 1][Wcol].SetSpecial(B);
            Board[Wrow - 1][0].SetSpecial(B);
            Board[Wrow][Wcol - 2].SetSpecial(B);
            Board[Wrow][Wcol - 1].SetSpecial(B);
            Board[Wrow][0].SetSpecial(B);
            Board[Wrow][1].SetSpecial(B);
            Board[Wrow + 1][Wcol - 1].SetSpecial(B);
            Board[Wrow + 1][Wcol].SetSpecial(B);
            Board[Wrow + 1][0].SetSpecial(B);
            Board[Wrow + 2][Wcol].SetSpecial(B);

        } else if (Wrow == 0 and Wcol == 0) {
            Board[10][0].SetSpecial(B);
            Board[11][11].SetSpecial(B);
            Board[11][0].SetSpecial(B);
            Board[11][1].SetSpecial(B);
            Board[0][10].SetSpecial(B);
            Board[0][11].SetSpecial(B);
            Board[0][1].SetSpecial(B);
            Board[0][2].SetSpecial(B);
            Board[1][11].SetSpecial(B);
            Board[1][0].SetSpecial(B);
            Board[1][1].SetSpecial(B);
            Board[2][0].SetSpecial(B);
        } else if (Wrow == 0 and Wcol == 1) {
            Board[10][1].SetSpecial(B);
            Board[11][0].SetSpecial(B);
            Board[11][1].SetSpecial(B);
            Board[11][2].SetSpecial(B);
            Board[0][11].SetSpecial(B);
            Board[0][0].SetSpecial(B);
            Board[0][2].SetSpecial(B);
            Board[0][3].SetSpecial(B);
            Board[1][0].SetSpecial(B);
            Board[1][1].SetSpecial(B);
            Board[1][2].SetSpecial(B);
            Board[2][1].SetSpecial(B);
        } else if (Wrow == 0 and Wcol == 10) {
            Board[10][10].SetSpecial(B);
            Board[11][9].SetSpecial(B);
            Board[11][10].SetSpecial(B);
            Board[11][11].SetSpecial(B);
            Board[0][8].SetSpecial(B);
            Board[0][9].SetSpecial(B);
            Board[0][11].SetSpecial(B);
            Board[0][0].SetSpecial(B);
            Board[1][9].SetSpecial(B);
            Board[1][10].SetSpecial(B);
            Board[1][11].SetSpecial(B);
            Board[2][10].SetSpecial(B);
        } else if (Wrow == 0 and Wcol == 11) {
            Board[10][11].SetSpecial(B);
            Board[11][10].SetSpecial(B);
            Board[11][11].SetSpecial(B);
            Board[11][0].SetSpecial(B);
            Board[0][9].SetSpecial(B);
            Board[0][10].SetSpecial(B);
            Board[0][0].SetSpecial(B);
            Board[0][1].SetSpecial(B);
            Board[1][10].SetSpecial(B);
            Board[1][11].SetSpecial(B);
            Board[1][0].SetSpecial(B);
            Board[2][11].SetSpecial(B);
        } else if (Wrow == 1 and Wcol == 0) {
            Board[11][0].SetSpecial(B);
            Board[0][11].SetSpecial(B);
            Board[0][0].SetSpecial(B);
            Board[0][1].SetSpecial(B);
            Board[1][10].SetSpecial(B);
            Board[1][11].SetSpecial(B);
            Board[1][1].SetSpecial(B);
            Board[1][2].SetSpecial(B);
            Board[2][11].SetSpecial(B);
            Board[2][0].SetSpecial(B);
            Board[2][1].SetSpecial(B);
            Board[3][0].SetSpecial(B);
        } else if (Wrow == 1 and Wcol == 1) {
            Board[11][1].SetSpecial(B);
            Board[0][0].SetSpecial(B);
            Board[0][1].SetSpecial(B);
            Board[0][2].SetSpecial(B);
            Board[1][11].SetSpecial(B);
            Board[1][0].SetSpecial(B);
            Board[1][2].SetSpecial(B);
            Board[1][3].SetSpecial(B);
            Board[2][0].SetSpecial(B);
            Board[2][1].SetSpecial(B);
            Board[2][2].SetSpecial(B);
            Board[3][1].SetSpecial(B);
        } else if (Wrow == 1 and Wcol == 10) {
            Board[11][10].SetSpecial(B);
            Board[0][9].SetSpecial(B);
            Board[0][10].SetSpecial(B);
            Board[0][11].SetSpecial(B);
            Board[1][8].SetSpecial(B);
            Board[1][9].SetSpecial(B);
            Board[1][11].SetSpecial(B);
            Board[1][0].SetSpecial(B);
            Board[2][9].SetSpecial(B);
            Board[2][10].SetSpecial(B);
            Board[2][11].SetSpecial(B);
            Board[3][10].SetSpecial(B);
        } else if (Wrow == 1 and Wcol == 11) {
            Board[11][11].SetSpecial(B);
            Board[0][10].SetSpecial(B);
            Board[0][11].SetSpecial(B);
            Board[0][0].SetSpecial(B);
            Board[1][9].SetSpecial(B);
            Board[1][10].SetSpecial(B);
            Board[1][0].SetSpecial(B);
            Board[1][1].SetSpecial(B);
            Board[2][10].SetSpecial(B);
            Board[2][11].SetSpecial(B);
            Board[2][0].SetSpecial(B);
            Board[3][11].SetSpecial(B);
        } else if (Wrow == 10 and Wcol == 0) {
            Board[8][0].SetSpecial(B);
            Board[9][11].SetSpecial(B);
            Board[9][0].SetSpecial(B);
            Board[9][1].SetSpecial(B);
            Board[10][10].SetSpecial(B);
            Board[10][11].SetSpecial(B);
            Board[10][1].SetSpecial(B);
            Board[10][2].SetSpecial(B);
            Board[11][11].SetSpecial(B);
            Board[11][0].SetSpecial(B);
            Board[11][1].SetSpecial(B);
            Board[0][0].SetSpecial(B);
        } else if (Wrow == 10 and Wcol == 1) {
            Board[8][1].SetSpecial(B);
            Board[9][0].SetSpecial(B);
            Board[9][1].SetSpecial(B);
            Board[9][2].SetSpecial(B);
            Board[10][11].SetSpecial(B);
            Board[10][0].SetSpecial(B);
            Board[10][2].SetSpecial(B);
            Board[10][3].SetSpecial(B);
            Board[11][0].SetSpecial(B);
            Board[11][1].SetSpecial(B);
            Board[11][2].SetSpecial(B);
            Board[0][1].SetSpecial(B);
        } else if (Wrow == 10 and Wcol == 10) {
            Board[8][10].SetSpecial(B);
            Board[9][9].SetSpecial(B);
            Board[9][10].SetSpecial(B);
            Board[9][11].SetSpecial(B);
            Board[10][8].SetSpecial(B);
            Board[10][9].SetSpecial(B);
            Board[10][11].SetSpecial(B);
            Board[10][0].SetSpecial(B);
            Board[11][9].SetSpecial(B);
            Board[11][10].SetSpecial(B);
            Board[11][11].SetSpecial(B);
            Board[0][10].SetSpecial(B);
        } else if (Wrow == 10 and Wcol == 11) {
            Board[8][11].SetSpecial(B);
            Board[9][10].SetSpecial(B);
            Board[9][11].SetSpecial(B);
            Board[9][0].SetSpecial(B);
            Board[10][9].SetSpecial(B);
            Board[10][10].SetSpecial(B);
            Board[10][0].SetSpecial(B);
            Board[10][1].SetSpecial(B);
            Board[11][10].SetSpecial(B);
            Board[11][11].SetSpecial(B);
            Board[11][0].SetSpecial(B);
            Board[0][11].SetSpecial(B);
        } else if (Wrow == 11 and Wcol == 0) {
            Board[9][0].SetSpecial(B);
            Board[10][11].SetSpecial(B);
            Board[10][0].SetSpecial(B);
            Board[10][1].SetSpecial(B);
            Board[11][10].SetSpecial(B);
            Board[11][11].SetSpecial(B);
            Board[11][1].SetSpecial(B);
            Board[11][2].SetSpecial(B);
            Board[0][11].SetSpecial(B);
            Board[0][0].SetSpecial(B);
            Board[0][1].SetSpecial(B);
            Board[1][0].SetSpecial(B);
        } else if (Wrow == 11 and Wcol == 1) {
            Board[9][1].SetSpecial(B);
            Board[10][0].SetSpecial(B);
            Board[10][1].SetSpecial(B);
            Board[10][2].SetSpecial(B);
            Board[11][11].SetSpecial(B);
            Board[11][0].SetSpecial(B);
            Board[11][2].SetSpecial(B);
            Board[11][3].SetSpecial(B);
            Board[0][0].SetSpecial(B);
            Board[0][1].SetSpecial(B);
            Board[0][2].SetSpecial(B);
            Board[1][1].SetSpecial(B);
        } else if (Wrow == 11 and Wcol == 10) {
            Board[9][10].SetSpecial(B);
            Board[10][9].SetSpecial(B);
            Board[10][10].SetSpecial(B);
            Board[10][11].SetSpecial(B);
            Board[11][8].SetSpecial(B);
            Board[11][9].SetSpecial(B);
            Board[11][11].SetSpecial(B);
            Board[11][0].SetSpecial(B);
            Board[0][9].SetSpecial(B);
            Board[0][10].SetSpecial(B);
            Board[0][11].SetSpecial(B);
            Board[1][10].SetSpecial(B);
        } else if (Wrow == 11 and Wcol == 11) {
            Board[9][11].SetSpecial(B);
            Board[10][10].SetSpecial(B);
            Board[10][11].SetSpecial(B);
            Board[10][0].SetSpecial(B);
            Board[11][9].SetSpecial(B);
            Board[11][10].SetSpecial(B);
            Board[11][0].SetSpecial(B);
            Board[11][1].SetSpecial(B);
            Board[0][10].SetSpecial(B);
            Board[0][11].SetSpecial(B);
            Board[0][0].SetSpecial(B);
            Board[1][11].SetSpecial(B);
        }
    }

    void Move() {
        string direction;
        while (direction != "n" and direction != "s" and direction != "w" and direction != "e" and
               direction != "arrow") {
            cout << "Move (n, e, s, w, arrow)?" << endl;
            cin >> direction;
            cout << endl;
        }
        Board[Hunter_Row_Pos][Hunter_Col_Pos].SetHunterOn(false);
        if (direction == "n") {
            MoveUp();
        } else if (direction == "e") {
            MoveRight();
        } else if (direction == "s") {
            MoveDown();
        } else if (direction == "w") {
            MoveLeft();
        } else {
            ShootArrow(direction);
        }
    }

    void MoveUp() {
        if (Hunter_Row_Pos == 0) {
            Hunter_Row_Pos = 11;
        } else {
            Hunter_Row_Pos -= 1;
        }
        Board[Hunter_Row_Pos][Hunter_Col_Pos].SetHunterOn(true);
    }

    void MoveDown() {
        if (Hunter_Row_Pos == 11) {
            Hunter_Row_Pos = 0;
        } else {
            Hunter_Row_Pos += 1;
        }
        Board[Hunter_Row_Pos][Hunter_Col_Pos].SetHunterOn(true);
    }

    void MoveRight() {
        if (Hunter_Col_Pos == 11) {
            Hunter_Col_Pos = 0;
        } else {
            Hunter_Col_Pos += 1;
        }
        Board[Hunter_Row_Pos][Hunter_Col_Pos].SetHunterOn(true);
    }

    void MoveLeft() {
        if (Hunter_Col_Pos == 0) {
            Hunter_Col_Pos = 11;
        } else {
            Hunter_Col_Pos -= 1;
        }
        Board[Hunter_Row_Pos][Hunter_Col_Pos].SetHunterOn(true);
    }

    void ShootArrow(string &direction) {
        while (direction != "n" and direction != "s" and direction != "w" and direction != "e") {
            cout << "Shoot (n, e, s, w)?" << endl;
            cin >> direction;
        }
        if (direction == "n" or direction == "s") {
            if (Wcol == Hunter_Col_Pos) {
                message = "Your arrow hit the Wumpus. You win!";
                cout << message;
            } else {
                message = "You just shot yourself. You lose!";
                cout << message;
            }
        } else if (direction == "e" or direction == "w") {
            if (Wrow == Hunter_Row_Pos) {
                message = "Your arrow hit the Wumpus. You win!";
                cout << message;
            } else {
                message = "You just shot yourself. You lose!";
                cout << message;
            }
        }
        endgame = true;
    }

    void CheckTile() {
        int x = Hunter_Row_Pos;
        int y = Hunter_Col_Pos;
        Board[x][y].PrintMessage();
        endgame = Board[x][y].EndGame();
    }

    vector<vector<Tile>> ReturnBoard() {
        return Board;
    }

    bool ReturnHunterPosition(int row, int col) {
        return Board[row][col].ReturnHunterOn();
    }

    bool EndOfGame() {
        return endgame;
    }

    string ReturnMessage() {
        return message;
    }
};

#endif
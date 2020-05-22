#define CATCH_CONFIG_MAIN
#include "Wumpus.hpp"
#include "catch.hpp"
#include <iostream>

//Programmer: Ariel Villasenor and Jessmer John Palanca
// Generated Fixed Board for each Test Case
//  0 1 2 3 4 5 6 7 8 9 10 11
//0     B         S
//1   B B B     S P S
//2 B B W B B     S
//3   B B G
//4     G P S
//5       S
//6           O
//7       S
//8     S P S
//9       S
//10
//11
Wumpus Test;
vector <vector<Tile>> TestBoard;

TEST_CASE("TEST_1") {
    Test.GenerateBoard();
    Test.assignTiles();
    TestBoard = Test.ReturnBoard();
    REQUIRE(TestBoard[2][2].getSpecial() == "W");
    REQUIRE(TestBoard[0][2].getSpecial() == "B");
    REQUIRE(TestBoard[1][2].getSpecial() == "B");
    REQUIRE(TestBoard[4][2].getSpecial() == "G");
    REQUIRE(TestBoard[4][3].getSpecial() == "P");
    REQUIRE(TestBoard[4][4].getSpecial() == "S");
    REQUIRE(TestBoard[3][5].getSpecial() == " ");
    REQUIRE(TestBoard[8][3].getSpecial() == "P");
    Test.MoveUp();
    REQUIRE(Test.ReturnHunterPosition(5, 5) == true);
    Test.MoveUp();
    REQUIRE(Test.ReturnHunterPosition(4, 5) == true);
    Test.MoveLeft();
    REQUIRE(Test.ReturnHunterPosition(4, 4) == true);
    REQUIRE(TestBoard[4][4].getSpecial() == "S");
    REQUIRE(Test.EndOfGame() == false);
    Test.MoveLeft();
    Test.CheckTile();
    REQUIRE(TestBoard[4][3].getSpecial() == "P");
    REQUIRE(Test.ReturnHunterPosition(4, 3) == true);
    REQUIRE(Test.EndOfGame() == true);
}

Wumpus Test2;
vector <vector<Tile>> TestBoard2;

TEST_CASE("Test_2") {
    Test2.GenerateBoard();
    Test2.assignTiles();
    TestBoard2 = Test2.ReturnBoard();
    Test2.MoveLeft();
    REQUIRE(Test2.ReturnHunterPosition(6, 4) == true);
    Test2.MoveLeft();
    REQUIRE(Test2.ReturnHunterPosition(6, 3) == true);
    Test2.MoveLeft();
    REQUIRE(Test2.ReturnHunterPosition(6, 2) == true);
    REQUIRE(Test2.EndOfGame() == false);
    Test2.MoveDown();
    REQUIRE(Test2.ReturnHunterPosition(7, 2) == true);
    Test2.MoveRight();
    REQUIRE(Test2.ReturnHunterPosition(7, 3) == true);
    REQUIRE(TestBoard2[7][3].getSpecial() == "S");
    Test2.MoveLeft();
    Test2.MoveUp();
    Test2.MoveUp();
    Test2.MoveUp();
    REQUIRE(TestBoard2[4][2].getSpecial() == "G");
    Test2.MoveUp();
    REQUIRE(TestBoard2[3][2].getSpecial() == "B");
    REQUIRE(Test2.EndOfGame() == false);
    Test2.MoveUp();
    Test2.CheckTile();
    REQUIRE(Test2.EndOfGame() == true);
}

Wumpus Test3;
vector <vector<Tile>> TestBoard3;

TEST_CASE("Test_3") {
    Test3.GenerateBoard();
    Test3.assignTiles();
    TestBoard3 = Test3.ReturnBoard();
    Test3.MoveLeft();
    REQUIRE(Test3.ReturnHunterPosition(6, 4) == true);
    REQUIRE(Test3.EndOfGame() == false);
    string str = "e";
    Test3.ShootArrow(str);
    REQUIRE(Test3.EndOfGame() == true);
    string lost = "You just shot yourself. You lose!";
    REQUIRE(Test3.ReturnMessage() == lost);
}

Wumpus Test4;
vector <vector<Tile>> TestBoard4;

TEST_CASE("Test_4") {
    Test4.GenerateBoard();
    Test4.assignTiles();
    TestBoard4 = Test4.ReturnBoard();
    Test4.MoveLeft();
    Test4.MoveLeft();
    Test4.MoveLeft();
    REQUIRE(Test4.ReturnHunterPosition(6, 2) == true);
    string str = "n";
    REQUIRE(Test4.EndOfGame() == false);
    Test4.ShootArrow(str);
    REQUIRE(Test4.EndOfGame() == true);
    string win = "Your arrow hit the Wumpus. You win!";
    REQUIRE(Test4.ReturnMessage() == win);
    REQUIRE(Test4.EndOfGame() == true);
}
#endif
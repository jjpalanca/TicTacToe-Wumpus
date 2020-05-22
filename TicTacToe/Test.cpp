/*Jessmer John Palanca and Ariel Villaseñor*/
/*This file test our code to see if everything is operational.
 * We use catch.hpp to use REQUIRE'S and check sections of our code.*/
#ifndef INC_382_TEST_CPP
#define INC_382_TEST_CPP

#define CATCH_CONFIG_MAIN
#include "TicTacToe.hpp"
#include "TicTacTile.hpp"
#include "catch.hpp"
#include <iostream>

TicTacToe Test;
vector<vector<TicTacTile>> Board;
RandomAI AI(Board);
TEST_CASE("Check RandomAI"){
    Test.GenerateBoard();
    Board=Test.ReturnBoard();
    REQUIRE(Board[0][0].GetSpecial()=="_");
    REQUIRE(Board[0][1].GetSpecial()=="_");
    REQUIRE(Board[0][2].GetSpecial()=="_");
    REQUIRE(Board[1][0].GetSpecial()=="_");
    REQUIRE(Board[1][1].GetSpecial()=="_");
    REQUIRE(Board[1][2].GetSpecial()=="_");
    REQUIRE(Board[2][0].GetSpecial()=="_");
    REQUIRE(Board[2][1].GetSpecial()=="_");
    REQUIRE(Board[2][2].GetSpecial()=="_");
    REQUIRE(Test.checkTile(0,0));
    Test.AssignTile(0, 0, "X");
    REQUIRE(Test.ReturnSpecial(0,0)=="X");
    AI.SetBoard(Test.ReturnBoard());
    AI.ChooseOpenTile();
    int index = AI.ReturnIndex();
    int row=index/3;
    int col=index%3;
    Test.AIMove(AI.ReturnIndex());
    REQUIRE(Test.ReturnSpecial(row, col)=="O");
    REQUIRE(!Test.checkWinner());
}

TicTacToe Test2;
vector<vector<TicTacTile>> Board2;
IntermediateAI AI2(Board);
TEST_CASE("Check IntermediateAI"){
    Test2.GenerateBoard();
    Board=Test.ReturnBoard();
    REQUIRE(Test2.checkTile(0,0));
    Test2.AssignTile(0, 0, "X");
    REQUIRE(!Test2.checkTile(3,3));
    REQUIRE(Test2.ReturnMessage()=="Out of range");
    REQUIRE(Test2.ReturnSpecial(0,0)=="X");
    AI2.SetBoard(Test2.ReturnBoard());
    AI2.CheckIfWinning();
    int index = AI2.ReturnIndex();
    int row=index/3;
    int col=index%3;
    Test2.AIMove(AI2.ReturnIndex());
    REQUIRE(Test2.ReturnSpecial(row, col)=="O");
    if(Test2.ReturnSpecial(0,1)!="O"){
        REQUIRE(Test2.checkTile(0,1));
        Test2.AssignTile(0,1,"X");
        AI2.SetBoard(Test2.ReturnBoard());
        AI2.CheckIfWinning();
        Test2.AIMove(AI2.ReturnIndex());
        REQUIRE(Test2.ReturnSpecial(0,2)=="O");
    }
    else if(Test2.ReturnSpecial(1,0)!="O"){
        REQUIRE(Test2.checkTile(1,0));
        Test2.AssignTile(1,0,"X");
        AI2.SetBoard(Test2.ReturnBoard());
        AI2.CheckIfWinning();
        Test2.AIMove(AI2.ReturnIndex());
        REQUIRE(Test2.ReturnSpecial(2,0)=="O");
    }
}
//
// X X _
// _ X _
// _ O O
//
TicTacToe Test3;
vector<vector<TicTacTile>> Board3;
IntermediateAI AI3(Board);
TEST_CASE("Check AI will win"){
    Test3.GenerateBoard();
    REQUIRE(Test3.ReturnSpecial(0,0) == "_");
    Test3.AssignTile(0, 0, "X");
    REQUIRE(Test3.ReturnSpecial(0,0) == "X");
    REQUIRE(Test3.ReturnSpecial(2,2) == "_");
    Test3.AssignTile(2, 2, "O");
    REQUIRE(Test3.ReturnSpecial(2,2) == "O");
    Test3.AssignTile(1, 1, "X");
    REQUIRE(!Test3.checkTile(1,1));
    REQUIRE(Test3.ReturnMessage()=="Square Taken");
    REQUIRE(Test3.checkTile(2,1));
    Test3.AssignTile(2, 1, "O");
    REQUIRE(Test3.checkTile(0,1));
    Test3.AssignTile(0, 1, "X");
    REQUIRE(Test3.ReturnSpecial(2,0) == "_");
    REQUIRE(!Test3.ReturnGameOver());
    REQUIRE(!Test3.checkWinner());
    AI3.SetBoard(Test3.ReturnBoard());
    AI3.CheckIfWinning();
    Test3.AIMove(AI3.ReturnIndex());
    REQUIRE(Test3.ReturnSpecial(2,0) == "O");
    REQUIRE(Test3.checkWinner());
    REQUIRE(Test3.ReturnWinner()=="O");
    REQUIRE(Test3.ReturnGameOver());
}
//
// X O X
// _ O X
// O _ X
//
TicTacToe Test4;
vector<vector<TicTacTile>> Board4;
IntermediateAI AI4(Board);
TEST_CASE("Check Human will win"){
    Test4.GenerateBoard();
    Test4.AssignTile(0, 0, "X");
    REQUIRE(!Test4.checkTile(0,0));
    REQUIRE(Test4.ReturnMessage()=="Square Taken");
    Test4.AssignTile(2, 0, "O");
    Test4.AssignTile(2, 2, "X");
    REQUIRE(Test4.ReturnSpecial(1,1) == "_");
    AI4.SetBoard(Test4.ReturnBoard());
    AI4.CheckIfWinning();
    REQUIRE(!Test4.ReturnGameOver());
    Test4.AIMove(AI4.ReturnIndex());
    REQUIRE(Test4.ReturnSpecial(1,1) == "O");
    Test4.AssignTile(0, 2, "X");
    AI4.SetBoard(Test4.ReturnBoard());
    AI4.CheckIfWinning();
    Test4.AIMove(AI4.ReturnIndex());
    REQUIRE(Test4.ReturnSpecial(0,1) == "O");
    REQUIRE(Test4.ReturnSpecial(1,2) == "_");
    REQUIRE(!Test4.ReturnGameOver());
    REQUIRE(!Test4.checkWinner());
    Test4.AssignTile(1, 2, "X");
    REQUIRE(Test4.ReturnSpecial(1,2) == "X");
    REQUIRE(Test4.checkWinner());
    REQUIRE(Test4.ReturnWinner()=="X");
    REQUIRE(Test4.ReturnGameOver());
}


#endif
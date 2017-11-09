//
//  main.cpp
//  Project1
//
//  Created by Haroon Iftikhar on 9/25/16.
//  Copyright © 2016 Haroon Iftikhar. All rights reserved.

/* In this problem we are calculating the number of moves possible by a checker considering what moves are legal, where the opponent pieces are located and what route would take down the most opponent checkers*/

//

#include <iostream>
#include <string>
#include <cmath>
#include "Definitions.h"

using namespace std;

struct Checker
{
    int row;
    int col;
};


class Board
{
public:
    Board(); //creates an empty board
    void reset( ); //clears the board
    void addChecker(char who, int row, int col);
    int numJumps(int row, int col); // num of jumps possible from row, col
    void print() ; // print the board for debugging only
    bool isJumpValid(Checker self, int rowDiff, int colDiff);
private:
    char board[8][8];
};


// the main of the program

int main(){
    int * results;
    Checker myCheckers[8];
    Board myBoard;
    Board tempBoard;
    myBoard.reset();
    int numCases;
    int row =0, col=0;
    int m, n;
    cin>> numCases;    // Here we input how many test cases we want to test
    results = new int[numCases];
    for (int TestCase=0;TestCase<numCases; TestCase++)
    {
        cin>>m>>n;     // Here we input the number of our and opponent checkers
        for (int numSelf=0; numSelf<m; numSelf++)
        {
            cin>>row>>col;     // Here we input the location of our checkers
            myBoard.addChecker('w', row, col);
            myCheckers[numSelf].row=row;
            myCheckers[numSelf].col=col;
        }
        for (int numOpponent=0; numOpponent<n; numOpponent++)
        {
            cin>>row>>col;     // Here we input the location of opponent checkers
            myBoard.addChecker('b', row, col);
        }
        
        results[TestCase] = myBoard.numJumps(myCheckers[0].row, myCheckers[0].col);
        myBoard.reset();
    

        
    }
    
    for (int TestCase = 0; TestCase < numCases; TestCase++)
        cout<<"the number of jumps is "<< results[TestCase] <<endl;

    
}




//  KenKen
//
//  Created by Haroon Iftikhar on 4/17/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
/* Description: This program mimics the logic puzzle KenKen.
 It takes in the length of the board and number of cages as input (n and c).
 It then takes n number of lines of input to record all the elements of the board (alphabets a-z)
 where elements in the same cage are represented by same letter.
 It then takes the arithmetic equation of each cage.
 The program then calculates the solution of that KenKen board and outputs it
 */

//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Cage{
    char symbol;
    int multiplier;
};

int lengthKen;
int numberOfCages;
vector<Cage> KenKenCages;
vector<vector<char>> Board;
Cage KenCage;
vector<char> row;
char square;
vector<char> Cages;
vector<pair<char,int>> numCages;
int RuleOfNumbers = 0;
vector<int> PuzzleNumbers;
vector<pair<int, Cage>> Rules;
vector<vector<int>> SolutionBoard;


void RuleOfWhat(){
    for (int i=0; i<=lengthKen; i++) {
        RuleOfNumbers = i+RuleOfNumbers;
    }
}
// Post-Condition: Calculates the rule of board to solve by i.e. the total of a row/column of the KenKen board.
//In a 3x3 board = 6, in a 6x6 board = 21

bool CageFinder(char Square, vector<char> SquareVector){
    bool found = false;
    for (int i=0; i<SquareVector.size(); i++) {
        if (SquareVector[i] == Square) {
            found = true;
        }
    }
    return found;
}
// Post-Condition: Helper function to calculate how many unique alphabets

void SaveSquares(vector<vector<char>> Board, vector<char> &Cages){
    for (int i; i<Board.size(); i++) {
        for (int j=0; j<Board.size(); j++) {
            if (!CageFinder(Board[i][j], Cages)) {
                Cages.push_back(Board[i][j]);
            }
        }
    }
}
// Post-Condition: Calculates how many unique alphabets representing cages, number of cages = number of alphabets

int numberOfEach(char letter){
    int numberOfLetters = 0;
    for (int i=0; i<Board.size(); i++) {
        for (int j=0; j<Board.size(); j++) {
            if (Board[i][j] == letter) {
                numberOfLetters++;
            }
        }
    }
    return numberOfLetters;
}
// Post-Condition: Helper function to find number of squares in each cage

// Pre-Condition: will successfully back-track until solution found
bool placeNumber(int numbersPlaced){
    if (numbersPlaced == Board.size()*Board.size()) {
        return true;
    }
    else{
        
    }
    return false;
}
// Post-Condition: Back-tracking complete
int AlphabetToNumber(char alphabet){
    int number = 0;
    switch (alphabet) {
        case 'a':
            number = 1;
            break;
        case 'b':
            number = 2;
            break;
        case 'c':
            number = 3;
            break;
        case 'd':
            number = 4;
            break;
        case 'e':
            number = 5;
            break;
        case 'f':
            number = 6;
            break;
        case 'g':
            number = 7;
            break;
        case 'h':
            number = 8;
            break;
        case 'i':
            number = 9;
            break;
        case 'j':
            number = 10;
            break;
        case 'k':
            number = 11;
            break;
        case 'l':
            number = 12;
            break;
        case 'm':
            number = 13;
            break;
        case 'n':
            number = 14;
            break;
        case 'o':
            number = 15;
            break;
        case 'p':
            number = 16;
            break;
        case 'q':
            number = 17;
            break;
        case 'r':
            number = 18;
            break;
        case 's':
            number = 19;
            break;
        case 't':
            number = 20;
            break;
        case 'u':
            number = 21;
            break;
        case 'v':
            number = 22;
            break;
        case 'w':
            number = 23;
            break;
        case 'x':
            number = 24;
            break;
        case 'y':
            number = 25;
            break;
        case 'z':
            number = 26;
            break;
            
        default:
            break;
    }
    return number;
}

void HowManyOfEach(){
    pair<char,int> CurrentCage;
    for (int i=0; i<Cages.size(); i++) {
        CurrentCage = make_pair(Cages[i],numberOfEach(Cages[i]));
        numCages.push_back(CurrentCage);
    }
}
// Post-Condition: Calculates how many squares are there in each cage
void SolutionNumbers(){
    PuzzleNumbers.clear();
    for (int i=0; i<lengthKen; i++) {
        PuzzleNumbers.push_back(i+1);
    }
}
// Post-Condition: Add value to vector that will contain all possible values in row/column of KenKen
void MakeRules(){
    pair<int, Cage> rule;
    for (int i=0; i<numCages.size(); i++) {
        rule = make_pair(numCages[i].second, KenKenCages[i]);
        Rules.push_back(rule);
    }
}
// Post-Condition: creates a vector with rules. A rule is: number of squares in cage,letter of cage,symbol of cage,and required total of cage
void NumerizeBoard(){
    vector<int> Row;
    for (int i=0; i<lengthKen; i++) {
        for (int j=0; j<lengthKen; j++) {
            Row.push_back(AlphabetToNumber(Board[i][j]));
        }
        SolutionBoard.push_back(Row);
        Row.clear();
    }
}
// Post-Condition: Helper function for creating numerized solution board

// Pre-Condition: will narrow down the possible values for a cage
vector<vector<int>> Choices(int numSquares, vector<int> Solutions, char symbol, int total){
    int Answer = 1;
    vector<int> OneOfChoices;
    vector<vector<int>> Possibilities;
    for (int i=0; i<Solutions.size(); i++) {
        if (symbol != '/' || symbol != '-') {
            for (int j=0; j<Solutions.size(); j++) {
                if (Solutions[j]>total) {
                    Solutions.erase(remove(Solutions.begin(), Solutions.end(), Solutions[j]), Solutions.end());  // removed elements greater than total in case of subtraction and division
                }
                do {
                    Answer = 1;
                    for (int k=0; k<numSquares; k++) {
                        if (symbol == '+') {
                            Answer = Answer + Solutions[k];
                            if (Answer-1 == total) {
                                for (int k=0; k<numSquares; k++) {
                                    OneOfChoices.push_back(Solutions[k]);
                                }
                                Possibilities.push_back(OneOfChoices);
                                
                            }
                        }
                        if (symbol == 'x') {
                            Answer = Answer*Solutions[k];
                            if (Answer == total) {
                                for (int k=0; k<numSquares; k++) {
                                    OneOfChoices.push_back(Solutions[k]);
                                }
                                Possibilities.push_back(OneOfChoices);
                            }
                        }
                    }
                } while (next_permutation(Solutions.begin(), Solutions.end()));
            }
        }
        else{
            do {
                Answer = 1;
                for (int k=0; k<numSquares; k++) {
                    if (symbol == '/') {
                    Answer = Solutions[k]/Solutions[k+1];
                        if (Answer == total) {
                            OneOfChoices.push_back(Solutions[k]);
                            OneOfChoices.push_back(Solutions[k+1]);
                            Possibilities.push_back(OneOfChoices);
                        }
                    }
                    if (symbol == '-') {
                    Answer = Solutions[k]-Solutions[k+1];
                        if (Answer == total) {
                            OneOfChoices.push_back(Solutions[k]);
                            OneOfChoices.push_back(Solutions[k+1]);
                            Possibilities.push_back(OneOfChoices);
                        }

                    }
                }
            } while (next_permutation(Solutions.begin(), Solutions.end()));
        }
        
    }
    return Possibilities;
}
// Pre-Condition: will define set of statements for each arithmetic operator
int Solver(int i, vector<int> Solutions, char symbol){
    int Answer = 1;
    switch (symbol) {
        case '+':
            for (int i=0; i<Solutions.size(); i++) {
                Answer = i+Answer;
            }
            Answer = Answer-1;
            break;
        case '-':
            Answer = Solutions[1]-Solutions[0];
            break;
        case 'x':
            for (int i=0; i<Solutions.size(); i++) {
                Answer = i*Answer;
            }
            break;
        case '/':
            Answer = Solutions[1]/Solutions[0];
            break;
    }
    return Answer;
}
// Post-Condition: Returns the value that should be the total of the KenKen Cage: to confirm whether the values in cage are ok


// Post-Condition: returns the set of only possible values to solve cage with
void SolvePuzzle(){
    
    
    vector<vector<int>> SetOfChoices;
    NumerizeBoard();
    //double* a = &SolutionBoard[0][0];
    
    //SolBoard = NumerizeBoard();
    
    for (int i=0; i<Rules.size(); i++) {
        SetOfChoices = Choices(Rules[i].first, PuzzleNumbers, Rules[i].second.symbol, Rules[i].second.multiplier);
        for (int j=0; j<SetOfChoices.size(); j++) {
                for (int m=0; m<SetOfChoices[j].size(); m++) {
                    for (int k=0; k<lengthKen; k++) {
                        for (int l=0; l<lengthKen; l++) {
                            if (SolutionBoard[k][l] == AlphabetToNumber(Cages[i])) {
                                SolutionBoard[k][l] = SetOfChoices[j][m];
                                m++;
                            }
                        }
                    }
                }
            }
        }
}
// Post-Condition: Empties the solution board to all zeros

int main(){
    
    cin>>lengthKen>>numberOfCages;
    for (int i=0; i<lengthKen; i++) {
        for (int j=0; j<lengthKen; j++) {
            cin >> square;
            row.push_back(square);
        }
        Board.push_back(row);
        row.clear();
    }
    for (int i=0; i<numberOfCages; i++) {
        cin >> KenCage.multiplier >> KenCage.symbol;
        KenKenCages.push_back(KenCage);
    }
    RuleOfWhat();
    SaveSquares(Board, Cages);
    HowManyOfEach();
    MakeRules();
    SolutionNumbers();
    SolvePuzzle();
    
    for (int i=0; i<lengthKen; i++) {
        for (int j=0; j<lengthKen; j++) {
    cout << SolutionBoard[i][j] << " ";
        }
        cout << endl;
    }
    /* TESTING
    for (int i=0; i<numCages.size(); i++) {
            cout << numCages[i].first << " " << numCages[i].second << "\n";
        }
    */
   // cout << "Love you";
    
    
    
    
    return 0;
}

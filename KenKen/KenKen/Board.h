//
//  Board.h
//  KenKen
//
//  Created by Haroon Iftikhar on 4/18/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

#ifndef Board_h
#define Board_h
#include "Rule.h"


class Board
{
private:
    vector<vector<int>> Grid;
    vector<Rule> rules;
public:
    Board(vector<vector<int>> Board,vector<Rule> Rules)
    {
        Grid = Board;
        rules = Rules;
    }
    vector<vector<int>> getBoard(){
        return Grid;
    }
};

#endif /* Board_h */

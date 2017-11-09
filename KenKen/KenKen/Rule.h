//
//  Rule.h
//  KenKen
//
//  Created by Haroon Iftikhar on 4/18/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

#ifndef Rule_h
#define Rule_h
#include "Board.h"

using namespace std;
enum Symbol { plus, minus, times, divide };

class Rule
{
private:
    char letter;
    int value;
    Symbol op;
public:
    Rule(char l, int v, Symbol o){
        letter = l;
        value = v;
        op = o;
    }
    Rule() { }
    bool Eval(Board board, vector<vector<int>> rows)
    {
        vector<int> vals;
        for (int row = 0; row < rows.size(); row++)
            for (int col = 0; col < rows.size(); col++)
                if (board.getBoard()[row][col] == letter)
                {
                    vals.push_back(rows[row][col]);
                }
        Debug.Assert(vals.Count>0);
        switch (op)
        {
            case Symbol.plus:
                return vals.Sum() == value;
            case Symbol.times:
                return vals.Aggregate(1, (x, y) => x * y) == value;
            case Symbol.minus:
                if(vals.Count>2)
                    throw new Exception("Can't Minus more than two cells (" + letter + ")");
                return (vals[0] - vals[1] == value) || (vals[1] - vals[0] == value);
            case Op.divide:
                if (vals.Count > 2)
                    throw new Exception("Can't Divide more than two cells (" + letter + ")");
                return (vals[0] * value == vals[1]) || (vals[1] * value == vals[0]);    //avoid int division
            default:
                Debug.Assert(false);
                return false;
        }
    }

};

#endif /* Rule_h */

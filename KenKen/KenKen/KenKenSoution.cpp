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

#include <iostream>
#include <vector>
#include "Board.h"
#include <Rule.h>

using namespace std;

class KenKenSolver
{
public:
    Board board;
    vector<int> permutations;
    vector<Rule> rulesByRow;
    vector<vector<int>> solution;
    
    void ReadGrids()
    {
        board = new Board();
        board.FillTestData();
    }
    
    void Solve()
    {
        if (!board.Validate())
            throw new exception("Grid has letter missing from Rules");
        AnalyseRules();
        CreateRowPermutations();
        solution = null;
        TryRowSolution(new int[0][]);
        Debug.WriteLine(solution==null ? "No solution" : solution.Aggregate("", (s, r) => s+r.Aggregate("", (ss,c)=> ss+","+c.ToString())+"\n"));
    }
    
    private void CreateRowPermutations()
    {
        Permute(new int[0], new int[] { 1,2,3,4,5,6} );
    }
    
    /// <summary>
    /// Create each permutation by appending each element of 'right' to 'left' and recusing
    /// </summary>
    /// <param name="left"></param>
    /// <param name="right"></param>
    private void Permute(IEnumerable<int> left, IEnumerable<int> right)
    {
        if (left.Count() == 6)
        {
            permutations.Add(left.ToArray());
            return;
        }
        for (int i = 0; i < right.Count(); i++)
            Permute( left.Concat(new int[] { right.ElementAt(i)} ), right.Where((val, index) => index != i).ToArray());
    }
    
    /// <summary>
    /// Sort rules by the last row they apply to, this means they can be checked as soon as that row is available and so fail as early as possible if nec.
    /// </summary>
    void AnalyseRules()
    {
        var rulesRemaining = board.rules.Select(r => r.letter).ToList();
        for (int row = 5; row >= 0; row--)
        {
            rulesByRow[row] = new List<Rule>();
            for (int col = 0; col < 6; col++)
                if (rulesRemaining.Contains(board.grid[row, col]))
                {
                    Rule rule = board.rules.First(r => r.letter == board.grid[row, col]);
                    rulesByRow[row].Add(rule);
                    rulesRemaining.Remove(rule.letter);
                }
        }
    }
    
    bool TryRowSolution(int[][] rows)
    {
        if (rows.Count() == 6)   //bottom-out
        {
            solution = rows.ToArray();
            return true;
        }
        int newrow = rows.Count();
        foreach (int[] permute in permutations)
        {
            if (IsValid(rows, permute)) //check new row is consistent
            {
                int[][] newgrid = rows.Concat(new int[][] { permute }).ToArray();
                if (rulesByRow[rows.Count()].All(r => r.Eval(board, newgrid.ToArray())))  //test each rule
                    if (TryRowSolution(newgrid))
                        return true;
            }
        }
        return false;
    }
    
    /// <summary>
    /// Is this permutation of numbers in the next row consistent with the existing rows so far
    /// </summary>
    /// <param name="rows"></param>
    /// <param name="permute"></param>
    /// <returns></returns>
    bool IsValid(int[][] rows, int[] nextRow)
    {
        for (int col = 0; col < 6; col++)
            for (int row = 0; row < rows.Count(); row++)
            {
                if (nextRow[col] == rows[row][col])
                    return false;
            }
        return true;
    }
}
}


//
//  FloydWarshall.cpp
//  FloydWarshallAlgorithm
//
//  Created by Haroon Iftikhar on 12/4/16.
//  Copyright © 2016 Haroon Iftikhar. All rights reserved.
//

#include <iostream>
using namespace std;

void PrintMatrix(int AdjMatrix[4][4]){
    
    for(int i=0; i<4; i++)    //This loops on the rows.
    {
        for(int j=0; j<4; j++) //This loops on the columns
        {
            
            
            if (AdjMatrix[i][j] == 100) {
                cout << "\u221E" << "  ";
            } else {
                cout << AdjMatrix[i][j]  << "  ";
            }
        }
        cout << endl;
    }}
    
void PrintPathMatrix(int PathOfMatrix[4][4]){
    
    
    for(int i=0; i<4; i++)    //This loops on the rows.
    {
        for(int j=0; j<4; j++) //This loops on the columns
        {
            
            if (PathOfMatrix[i][j] == -1) {
                cout << "\u002D" << "  ";
            } else {
                cout << PathOfMatrix[i][j]  << "  ";
            }

        }
        cout << endl;
    }
    
    cout << endl;
}


int main(){
    
   
    
     int AdjMatrix[4][4] = {
        {0,100,3,0},
        {-2,0,100,1},
        {100,100,0,5},
        {100,4,100,0}
    };
    
    int PathOfMatrix[4][4] = {
        {-1,-1,0,0},
        {1,-1,-1,1},
        {-1,-1,-1,2},
        {-1,3,-1,-1}
    };
    
    cout << "BEFORE RUNNING FLOYD-WARSHALL ALGORITHM" << endl << endl;
    
    cout << "Dist0" << endl;
    PrintMatrix(AdjMatrix);
    
    cout << endl << "Path0" << endl;
    PrintPathMatrix(PathOfMatrix);
    
    
    cout << endl << "AFTER RUNNING FLOYD-WARSHALL ALGORITHM" << endl;
    
    for (int k = 1; k <= 3; k++)
    {
        for (int i = 0; i <= 3; i++)
            for (int j = 0; j <= 3; j++)
            {
                if ( AdjMatrix[i][k] + AdjMatrix[k][j] < AdjMatrix[i][j] &&
                    AdjMatrix[i][k] + AdjMatrix[k][j]!=100
                    && AdjMatrix[i][k] + AdjMatrix[k][j] <10)
                {
                    AdjMatrix[i][j] = AdjMatrix[i][k] + AdjMatrix[k][j];
                    PathOfMatrix[i][j] = k;
                }
            }
    
        cout << endl << "Dist" << k << endl;
        PrintMatrix(AdjMatrix);
        cout << endl << "Path" << k << endl;
        PrintPathMatrix(PathOfMatrix);
    
    }
    
    return 0;
}

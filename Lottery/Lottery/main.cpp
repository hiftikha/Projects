//
//  main.cpp
//  Lottery
//
//  Created by Haroon Iftikhar on 4/8/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    // insert code here...
    
    srand ( time(NULL) );
    vector<int> LotteryNumbers;
    
    for (int i=0; i<75; i++) { // 47 pool numbers for Lotto47
        int iterator = i+1;
        LotteryNumbers.push_back(iterator);
    }
    
    vector<int> Winner;
    
    do {
       int RandomGenerator = rand() % 75;
        for (int i=0; i<Winner.size(); i++) {
            if (Winner[i] == LotteryNumbers[RandomGenerator]) {
                LotteryNumbers.erase(LotteryNumbers.begin() + RandomGenerator);
            }
        }
        Winner.push_back(LotteryNumbers[RandomGenerator]);
    } while (Winner.size()<5);
    
    sort(Winner.begin(), Winner.end());
    cout << "Your ticket numbers are" << "\n";
    
     for (int i=0; i<5; i++) { // Seven ticket numbers
    cout << Winner[i] << " ";
     }
    
    cout << "\n";
    //int id = 1;
   /* int LotteryNumbers[] = {1,2,3,4,5,6,7,8,9,0};
    vector<vector<int>> WinningNumbers;
    
    do {
        for (int i = 0; i<4; i++) {
            vector<int> Pick;
            Pick.push_back(LotteryNumbers[i]);
            WinningNumbers.push_back(Pick);
        }
        for (int i=0; i<WinningNumbers.size(); i++) {
            for (int j=0; j<WinningNumbers.size(); j++) {
                if (WinningNumbers[i] == WinningNumbers[j]) {
                    WinningNumbers[i].clear();
                }
            }
        }
        for (int i=0; i<WinningNumbers.size(); i++) {
            for (int j=0; j<4; j++) {
            cout << WinningNumbers[i][j];
            }
            cout << "\n";
        }
    } while (next_permutation(LotteryNumbers, LotteryNumbers+4));
    */
    
    return 0;
}

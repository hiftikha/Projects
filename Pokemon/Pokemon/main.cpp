//
//  main.cpp
//  PokemonA
//
//  Created by Haroon Iftikhar on 1/22/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.

/*
 
 This program takes in the input of the location and type names of pokemon and returns all possible combinations in which they can
 be acquired. One of each. It also calculates the total distance it took to collect all of them. The output is just the number of order in which
 the pokemons were entered and the total distance.
 
 */




//
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <map>
using namespace std;

struct Stop{
    int row;
    int col;
    string name;
};

int findIndex(int index, const vector<int> & uniqueNames){
    /*
     
     post:
	    Given a vector of ints, and a target int (index)
     returns the location where index is found
     returns -1 if the index is not found.
     */
    for (unsigned int i = 0; i < uniqueNames.size(); i++)
        if (index == uniqueNames[i])
            return i;
    return -1;
}

bool nextOneOfEachName(vector<int> & lastPermute, vector<vector<int> > &uniqueNames ){
    /*
     pre: lastPermuate.size() == uniqueNames.size()
     lastPermute[i] == uniqueNames[i][j] for some j
     post: lastPermute is incremented to the next possible set of integers such that
     lastPermute[i]== uniqueNames[i][j] for some j (where next is determined by the order
     the names appear in input).
     */
    bool done = false;
    int index;
    for(unsigned int i = 1 ; i < lastPermute.size()&& !done;i++){
        index = findIndex(lastPermute[i], uniqueNames[i]);
        if (index <uniqueNames[i].size()-1 ){
            lastPermute[i]= uniqueNames[i][++index];
            return true;
        }
        else if (index == uniqueNames[i].size()-1)
        {
            lastPermute[i]= uniqueNames[i][0];
        }
    }
    return done;
}

void setUpUniqueNames(const vector<Stop> & locations, vector<vector<int> > & indexUniqueNames ){
    /*
     post: locations[indexUniqueNames[i][j]].name == location[indexUnqueNames[i][k]] for all j, k
     locations[indexUniqueNames[i][j]].name == the ith unique name entered in input
     */
    vector<int> temp(1,0);
    bool placed;
    string name;
    indexUniqueNames.push_back(temp);  // the empty name is added to make set 1, 2, ...
    for (unsigned int i = 1; i < locations.size(); i++){
        name = locations[i].name;
        placed= false;
        for (unsigned int j = 0; j < indexUniqueNames.size()&& !placed; j++)
            if (name == locations[indexUniqueNames[j][0]].name){
                placed = true;
                indexUniqueNames[j].push_back(i);
            }
        if (!placed){
            temp[0]=i;
            indexUniqueNames.push_back(temp);
        }
    }
}
/*
 pre: Returns Total Distance for the permutation passed into the function, makes a copy of the permutation so it doesnt end up changing it
 */
int TotalDistance(vector<int> & lastPermute, vector<Stop> & locations){
    
    /*
     post: returns total distance amongst the permutation
     */

    vector<int> PermuteCopy = lastPermute;
    //  map<int,int> OrderOfPermute;
    
    int Distance = 0;
    // string index;
    //int size = lastPermute.size();
    int ReturnStart = 0;
    int TotalDistance = 0;
   // int j =1;
    
        for(int i=1; i<PermuteCopy.size(); i++){
            
            int x2= locations[PermuteCopy[i]].row;
            int x1= locations[PermuteCopy[i-1]].row;
            int y2= locations[PermuteCopy[i]].col;
            int y1= locations[PermuteCopy[i-1]].col;
            int ReturningToStart= locations[PermuteCopy[PermuteCopy.size()-1]].row + locations[PermuteCopy[PermuteCopy.size()-1]].col;
            
            Distance = abs(x1-x2)+abs(y1-y2)+ Distance;
            ReturnStart = ReturningToStart;
            
        }
        TotalDistance = Distance+ReturnStart;
        return TotalDistance;
    
}

    /*
     pre: TotalDistance() function should be assigned as this function uses distances of all permutations to calculate the smallest
     */
int SmallestDistance(vector<int> & lastPermute, vector<Stop> & locations){
 
    /*
     post: returns smallest possible distance amongst all permutations with those pokemon choices
     */
    
    vector<int> PermuteCopy = lastPermute;
    int FinalDistance = TotalDistance(PermuteCopy, locations);
    
    
    do{
        
        if (TotalDistance(PermuteCopy, locations) < FinalDistance) {
            
            FinalDistance = TotalDistance(PermuteCopy, locations);
        }
    } while (next_permutation(PermuteCopy.begin()+1, PermuteCopy.end()));
    
    return FinalDistance;
    
}

    /*
     pre: TotalDistance() function should be assigned as the function uses distances of all permutations to calculate the smallest
     Uses next_permutation
     */
void PokeStops(vector<int> & lastPermute, vector<Stop> & locations, int SmallestPermute){
    /*
     post: outputs the order of pokestops for which the distance == Smallest possible distance required in collecting them
     Breaks the do-while loop once it returns a combination, so if two orders have the same smallest distance, then the one that comes first numerically is output
     */
    
    vector<int> PermuteCopy = lastPermute;
  
    do{
        
        if (TotalDistance(PermuteCopy, locations) == SmallestPermute) {
            
           for(int i=1; i<PermuteCopy.size(); i++){
               
                  cout << PermuteCopy[i] << " ";
           }
            break;
        }
        
      } while (next_permutation(PermuteCopy.begin()+1, PermuteCopy.end()));
    
  }

int main(){
    int numStops;
    vector<Stop> locations;
    vector<int> permute;
    vector<vector<int> > uniqueNames;
    
    cin>> numStops;
    locations.resize(numStops+1);
    locations[0].row = 0;
    locations[0].col = 0;
    locations[0].name="";
    
    for (int i = 1; i < numStops+1; i++){
        cin>> locations[i].row>>locations[i].col>>locations[i].name;
    }
    
    setUpUniqueNames(locations,uniqueNames );
    
    for (unsigned int i = 0; i < uniqueNames.size(); i++){
        permute.push_back(uniqueNames[i][0]);
    }
    
    int SmallestPermute = SmallestDistance(permute, locations);
    
    do {
        for (unsigned int i = 1; i < permute.size();i++){
            //  cout<<permute[i]<<" ";
        }

        if (SmallestDistance(permute, locations)< SmallestPermute) {
            SmallestPermute = SmallestDistance(permute, locations);
        }
        
    }while(nextOneOfEachName(permute, uniqueNames));
    
    do{
        PokeStops(permute, locations, SmallestPermute);

    }while(nextOneOfEachName(permute, uniqueNames));
    
    cout << SmallestPermute << endl;
    
   // SmallestRoute(permute, locations, uniqueNames);
    
    
    return 0;
}

/*
 
 5
 5 9 Eevee
 50 50 Flareon
 1 1 Flareon
 1 8 Joteon
 2 8 Umbreon
 
 4
 5 9 Eevee
 1 1 Flareon
 1 8 Joteon
 2 8 Umbreon
 
 
 8
 1 2 a
 2 3 b
 3 4 c
 4 5 a
 5 6 b
 6 7 c
 7 8 a
 8 9 b
 
 */

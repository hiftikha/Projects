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

#include <iostream>
#include <string>
#include <vector>
#include <map>


using namespace std;

int NumberOfPokemons;
int x;
int y;
string PokeName;



struct Pokemon{
    int position;
    int xlocation;
    int ylocation;
    string PokeName;
};


vector <Pokemon> PokemonVector;


/* map<string,int> PokemonCount;
map<string,int>::iterator Counter;


struct Pokemon{
    int position;
    int xlocation;
    int ylocation;
    string PokeName;
};




void FillCount(map<string,int> PokemonCount, vector<Pokemon> &PokemonVector){
    
    
    for (int i=0; i<PokemonVector.size(); i++) {

 Counter = PokemonCount.find(PokemonVector.at(i).PokeName);
    
        if (Counter->first == PokemonVector.at(i).PokeName) {
            
            string Temp = PokemonVector.at(i).PokeName;
            
            PokemonCount.insert(pair<string,int>(Temp, 1));
        }
        else{
            
            string Temp = PokemonVector.at(i).PokeName;
            
            PokemonCount[Temp] +=1;
        }
            
    
    }
}


void PokemonCombination(vector<Pokemon> &PokemonVector, vector<Pokemon> Temp, int start, int end, int index, int size){
    
    size = PokemonVector.size();
    
    
    if (index == size) {
        for (int i=0; i < size; i++) {
            cout << i << " ";
        }
    }
    for (int i=start; i<= end && end-i+1 >= size-index; i++) {
            Temp.at(index) = PokemonVector.at(i);
            PokemonCombination(PokemonVector, Temp, i+1, end, index+1, size);
            while (PokemonVector[i].PokeName == PokemonVector[i+1].PokeName) {
                i++;
            }
    }
    
}


void Print(vector<Pokemon> PokemonVector, int VectorSize, int size){
    
    vector<Pokemon> Temp;
    
    PokemonCombination(PokemonVector, Temp, 0, VectorSize-1, 0, size);
}

*/

int main(){
    
   
    
    cin >> NumberOfPokemons;
    
    map <string, int> pokenmonMap;
    std::map<string,int>::iterator it;
    
    for (int i=0; i < NumberOfPokemons; i++) {
        
        Pokemon Poke;
        cin >> Poke.xlocation >> Poke.ylocation >> Poke.PokeName;
        Poke.position = i+1;
        
        // See if this key exists
        it = pokenmonMap.find(Poke.PokeName);
        
        if (it == pokenmonMap.end()) // Not found
            pokenmonMap[Poke.PokeName] = 1;
        
        else // If found, increment the count
            pokenmonMap[Poke.PokeName] = pokenmonMap[Poke.PokeName] + 1;
        
        PokemonVector.push_back(Poke);
        
        
        // TESTING OF NESTED LOOPS
    }
    
    for (int j=0; j < NumberOfPokemons; j++) {
        
        vector<int> a;
        vector<int> b;
        vector<int> c;
        
        
        if (PokemonVector.at(j).PokeName == pokenmonMap) {
            <#statements#>
        }
    }
    
    
    
    
        /*
    // TESTING OF NESTED LOOPS
    }
static const int arr[] = {1,4,7};
    vector<int> a(arr,arr+3);
static const int arr2[] = {2,5,8};
    vector<int> b(arr2,arr2+3);
    static const int arr3[] = {3,6};
    vector<int> c(arr3,arr3+2);
    
    
    for (int i=0; i<c.size(); i++) {
        for (int j=0; j<b.size(); j++) {
            for (int k=0; k<a.size(); k++) {
                cout << a.at(k) << " "<< b.at(j) << " "<< c.at(i) << endl;
            }
        }
    }
    
    */
        
    return 0;
}



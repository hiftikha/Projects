//
//  main.cpp
//  Even Flow
//
// CIS 350 Program 3a
//  Created by Haroon Iftikhar on 3/21/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
/*
 Description: This program takes in multiple data sets, where one data set is an input of the number of verices and the number of pipes connecting them followed by the designated vertics a pipe connects to from both ends and the capacity of it specific for all the pipes. When all the data sets have been input, two zeros with a space in between initiates the program run. The program then calculates and outputs  the smallest difference between the largest and smallest capacity of the best layout of minimal pipes such that every vertex is connected. If the input produces a layout where all junctions do not connect, the program outputs -1
 
 */
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n; // number of pipes
int m; // number of junctions
int N;
int M;
int source; // starting junction of pipe
int destination; // ending junction of pipe
int weight; // capacity of pipe
vector<int> Output; // output
vector<pair<int, pair<int, int>>> Edges;

int parents[10000];  // max possible number of pipes
/*
 Pre-Condition: parent array should be defined
 */
int find(int x){
    if(parents[x] == x){
        return x;
    }
    return find(parents[x]);
}
/*
 Post-Condition: finds the parent of the set passed in as arguement
 */

/*
 Pre-Condition: find function should be defined
 */
void unite(int first,int second){
    int firstvariable = find(first);
    int secondvariable = find(second);
    parents[firstvariable] = secondvariable;
}
/*
 Post-Condition: unites the two disjoint sets passed in as arguement
 */

/*
 Pre-Condition: Parent array should be initialized
 */
void InitializeParents(int Parent[]){
    for (int i=0; i<n; i++) {
        Parent[i] = i;
    }
}
/*
 Post-Condition: Fills the Parent array as much required
 */

/*
 Pre-Condition: variables n and m should be initialized
 */
void TakeInput(){
    Edges.clear();
    for (int i=0; i<m; i++) {
        cin >>source>>destination>>weight;
        Edges.push_back(make_pair(weight, make_pair(source, destination)));
    }
}
/*
 Post-Condition: defines n and m and takes in the input of m lines
 */

/*
 Pre-Condition: LowestRange function should be defined since this is LowestRange's helper function
 */
vector<pair<int, pair<int, int>>> IfExists(int iterator,int NumberOfEdges,vector<int> difference, vector<pair<int, pair<int, int>>> Edges, vector<pair<int, pair<int, int>>> &LowestRangeEdges){
    
    for (int i=iterator; i<Edges.size(); i++) {
        if (abs(Edges[i].first - Edges[i+1].first) == difference[0]) {
            for (int j=0; j<LowestRangeEdges.size(); j++) {
                if (LowestRangeEdges[j] == Edges[i+1]) {
                    IfExists(i+1,NumberOfEdges, difference, Edges,LowestRangeEdges);
                }
            }
            if (LowestRangeEdges.size() == NumberOfEdges) {
                return LowestRangeEdges;
            }
            LowestRangeEdges.push_back(Edges[i+1]);
            difference.erase(difference.begin());
            i=0;
        }
    }
    return LowestRangeEdges;
}
/*
 Post-Condition: Recursively finds the graph that contains the edges that should be used to declare the minimum splanning tree with the least range of capacities in pipes and returns it as a graph
 */

/*
 Pre-Condition: Capacity vector should be initialized by function Kruskal
 */
int CapacityDiff(vector<int> Capacity){
    int Difference = 0;
    int Size = Capacity.size();
    sort(Capacity.begin(), Capacity.end());
    Difference = abs(Capacity[Size-1]-Capacity[0]);
    return Difference;
    
}
/*
 Post-Condition: return the difference of the largest and smallest weight in the Splanning Tree
 */

/*
 Pre-Condition: The number of edges should be known as well as the complete graph */
vector<pair<int, pair<int, int>>> LowestRange(int NumberOfEdges, vector<pair<int, pair<int, int>>> Edges){
    vector<int> difference;
    vector<pair<int, pair<int, int>>> LowestRangeEdges;
    for (int i=0; i<Edges.size(); i++) {
        difference.push_back(abs(Edges[i].first-Edges[i+1].first));
    }
    sort(difference.begin(), difference.end());
    LowestRangeEdges = IfExists(0, 3, difference, Edges,LowestRangeEdges);
    
    return LowestRangeEdges;
    
}
/*
 Post-Condition: this finds the edges that should be used to declare the minimum splanning tree with the least range of capacities in pipes and returns it as a graph
 */

/*
 Pre-Condition: The graph should be filled as this function spplies the Kruskal Algorithm to find the minimum splanning tree MST of the Graph
 */
void Kruskals(vector<pair<int, pair<int, int>>> Graph){
    vector<int> Weights;
    int SpanningTreeWeight = 0;
    int SpanningTreeEdges = 0;
    int Index = 0;
    
    sort(Graph.begin(),Graph.end());
    
    while (SpanningTreeEdges < n-1 || Index < Graph.size()) {
        source = Graph[Index].second.first;
        destination = Graph[Index].second.second;
        weight = Graph[Index].first;
        
        if (find(source) != find(destination)) {
            unite(source, destination);
            SpanningTreeWeight += weight;
            Weights.push_back(weight);
           // cout <<source<< " - "<<destination<<"  "<<weight<<endl;
            SpanningTreeEdges++;
        }
        Index++;
    }
    Output.push_back(CapacityDiff(Weights));
}
/*
 Post-Condition: Outputs the smallest range of largest capacity-smallest capacity of the minimum splanning tree
 */
int main(){
    
   // do {
        cin >> N >> M;
        n=N;
        m=M;
        InitializeParents(parents);
        TakeInput();
    /*    if(N == 0 && M== 0){
            for (int i =1; i<Output.size(); i=i+2) {
                cout << Output[i];
            }
     */
        Kruskals(Edges);
    cout << endl << endl;
    InitializeParents(parents);
    Kruskals(LowestRange(n-1, Edges));
    for (int i =1; i<Output.size(); i=i+2) {
        cout << Output[i];
    }
   // } while (N != 0 && M!= 0);
    
/*
4 5
1 2 3
1 3 5
1 4 6
2 4 6
3 4 7
     */
    
    
}

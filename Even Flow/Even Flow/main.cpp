//
//  main.cpp
//  Even Flow
//
// CIS 350 Program 3a
//  Created by Haroon Iftikhar on 3/21/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
/*
 Description: This program takes in multiple data sets, where one data set is an input of the number of verices and the number of pipes connecting them followed by the designated vertics a pipe connects to from both ends and the capacity of it specific for all the pipes. When all the data sets have been input, two zeros with a space in between initiates the program run. The program then calculates and outputs  the smallest difference between the largest and smallest capacity of the best layout of minimal pipes such that every vertex is connected. If the input produces a layout where all junctions do not connect, the program outputs -1
 

//

#include <iostream>
#include <vector>

using namespace std;

int n; // number of pipes
int m; // number of junctions
vector<vector<int>> Graph; // the graph

vector<vector<int>> FillGraphMatrix(int n){
    int source;
    int destination;
    int capacity;
    vector<vector<int>> Graph(n,vector<int>(n));
    for (int i=0; i<=n; i++) {
        cin >> source >> destination >> capacity;
        Graph[source-1][destination-1]=capacity;
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
        if (Graph[i][j]!=0) {
            Graph[j][i]=Graph[i][j];
        }
    }
    }
    return Graph;
}
// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX;
    int min_index = 0;
    
    for (int v = 0; v < n; v++){
        if (mstSet[v] == false && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// A utility function to print the constructed MST stored in parent[]
void PrintTree(int Parent[], vector<vector<int>> Graph){
    cout << "Edge   Weight\n";
    for (int i = 1; i < n; i++){
        cout << Parent[i]+1<< " - " << i+1 << "  " << Graph[i][Parent[i]] << endl;
    }
}

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void primMST(vector<vector<int>> Graph)
{
    int parent[n]; // Array to store constructed MST
    int key[n];   // Key values used to pick minimum weight edge in cut
    bool mstSet[n];  // To represent set of vertices not yet included in MST
    
    // Initialize all keys as INFINITE
    for (int i = 0; i < n; i++){
        key[i] = INT_MAX;
        mstSet[i] = false;
    }
    
    // Always include first 1st vertex in MST.
    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST
    
    // The MST will have V vertices
    for (int count = 0; count < n-1; count++)
    {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet);
        
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
        
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < n; v++)
            
            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (Graph[u][v] && mstSet[v] == false && Graph[u][v] <  key[v]){
                parent[v]  = u;
                key[v] = Graph[u][v];
            }
    }
    
    // print the constructed MST
    PrintTree(parent, Graph);
}

//int main() {
 
    cin >> n >> m;
    Graph = FillGraphMatrix(n);
    primMST(Graph);
    
    
    
    
    return 0;
    
}
*/

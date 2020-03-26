//
//  main.cpp
//  Dictionary
//
//  Created by Haroon Iftikhar on 11/11/19.
//  Copyright © 2019 Haroon Iftikhar. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include <cmath>
#include <stack>

using namespace std;

class Graph{
    int V;
    list<int> *adj;
    vector<char> alphabets;
    
    
    
    public:
        Graph(int V){
            this->V = V;
            adj = new list<int>[V];
        }
        
        void addEdge(int v, int w){
            adj[v].push_back(w);
        }
        
        void topologicalSort(int v, bool visited[], stack<int> &Stack){
            
            visited[v] = true;
            
            list<int>::iterator i;
            
            for(i = adj[v].begin(); i != adj[v].end(); i++)
                if(!visited[*i])
                    topologicalSort(*i,visited,Stack);
            Stack.push(v);
        }
        
        void topoSort(){
            
            stack<int> Stack;
            
            bool *visited = new bool[V];
            for(int i = 0; i < V; i++)
                visited[i] = false;
                
            for(int i = 0; i < V; i++){
                if(visited[i] == false)
                    topologicalSort(i,visited,Stack);
            }
            
            while(!Stack.empty()){
                //cout << Stack.top() << "\n";
                alphabets.push_back(Stack.top());
                Stack.pop();
            }
        }
        
        vector<char> getAlphabets(){
            return alphabets;
        }
        
        void printAlphabets(){
            for(auto c: alphabets){
                cout << c << " ";
            }
        }
        
        int min(int x, int y){
            return (x < y)? x : y;
        }
        
};

void createGraph(vector<string> words, int size){
            Graph myGraph(size);
            
            for(int i = 0; i < words.size()-1; i++){
                
                string word1 = words[i];
                string word2 = words[i+1];
                for(int j = 0; j < min(word1.size(), word2.size()); j++){
                    if(word1[j] != word2[j]){
                        myGraph.addEdge(word1[j]-'a', word2[j]-'a');
                        break;
                    }
                }
            }
            
    myGraph.topoSort();
    //myGraph.printAlphabets();
}

int findNumberOfUniqueAlphas(vector<string> words){
            unordered_set<char> alphas;
            unordered_set<char>:: iterator it;
    
            for(int i = 0; i < words.size(); i++){
                for(int j = 0; j < words[i].size(); j++){
                    it = alphas.find(words[i][j]);
                    if(it != alphas.end()){
                        alphas.insert(words[i][j]);
                    }
                }
            }
    
    return alphas.size();
}

int main() {
    
    cout << "Hello World";
    
    vector<string> words = {"cbdke", "cbdj", "a", "ab", "b"};
    
    int numAlphas = findNumberOfUniqueAlphas(words);
    
    createGraph(words, numAlphas);
    
    
    return 0;
}

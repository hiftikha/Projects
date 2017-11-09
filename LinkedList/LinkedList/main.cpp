//
//  main.cpp
//  LinkedList
//
//  Created by Haroon Iftikhar on 6/21/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

typedef struct node{
    char data;
    node* next;
}* SammyNode ;


string alphabet;

node*current = Y;
node *makeNode = NULL;

while (current != NULL)
{
    node* newNode = new node; // first create a node (allocate memory)
    newNode->info = current->info; // then fill the info
    newNode->next = NULL;
    if (makeNode == NULL)
    {
        makeNode = newNode;
        *Z = makeNode;
    }
    else
    {
        makeNode->next = newNode;
        makeNode = makeNode->next;
    }
    current = current->next;
}


int main() {
    // insert code here...
    
}

//
//  main.cpp
//  HexMath
//
//  Created by Haroon Iftikhar on 4/2/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
/*  This program takes in input in hexadecimal and performs addition, subtraction, division, multiplication, pow on them returning the ouput in dec form
*/

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;
char OperatorFound(string Query){
    for (int i=0; i<Query.length(); i++) {
        if (Query[i] == '+') {
            return Query[i];
        }
        if (Query[i] == '-') {
            return Query[i];
        }
        if (Query[i] == '/') {
            return Query[i];
        }
        if (Query[i] == '*') {
            return Query[i];
        }
    }
    return 'a';
}
string BeforeOperation(string Query){
    char * Result;
    Result = new char[Query.length()];
    
    for (int i=0; i<Query.length(); i++) {
        if (Query[i] == '+') {
            return Result;
        }
        if (Query[i] == '-') {
            return Result;
        }
        if (Query[i] == '/') {
            return Result;
        }
        if (Query[i] == '*') {
            return Result;
        }
        Result[i] = Query[i];
    }
    return Result;
}

string AfterOperation(string Query){
    char * Result;
    Result = new char[Query.length()];
    bool OperatorFound = false;
    int j = 0;
    
    for (int i=0; i<Query.length(); i++) {
        if (Query[i] == '=') {
            OperatorFound = false;
            return Result;
        }
        if (OperatorFound) {
            Result[j] = Query[i];
            j++;
        }
        if (Query[i] == '+') {
            OperatorFound = true;
        }
        if (Query[i] == '-') {
            OperatorFound = true;
        }
        if (Query[i] == '/') {
            OperatorFound = true;
        }
        if (Query[i] == '*') {
            OperatorFound = true;
        }
    }
    return Result;
}

long long int StringToInt(string str)
{
    string temp;
    int * array;
    temp.clear();
    temp = str;
    long long int ret = 0;
    int size;
    
    size = temp.length() ;
    
    array = new int[size];
    
    for(int i = 0; i < size;i++)
    {
        switch(temp[i])
        {
            case '0': array[i] = 0; break;
            case '1': array[i] = 1; break;
            case '2': array[i] = 2; break;
            case '3': array[i] = 3; break;
            case '4': array[i] = 4; break;
            case '5': array[i] = 5; break;
            case '6': array[i] = 6; break;
            case '7': array[i] = 7; break;
            case '8': array[i] = 8; break;
            case '9': array[i] = 9; break;
            case 'a': array[i] = 10; break;
            case 'A': array[i] = 10; break;
            case 'b': array[i] = 11; break;
            case 'B': array[i] = 11; break;
            case 'c': array[i] = 12; break;
            case 'C': array[i] = 12; break;
            case 'd': array[i] = 13; break;
            case 'D': array[i] = 13; break;
            case 'e': array[i] = 14; break;
            case 'E': array[i] = 14; break;
            case 'f': array[i] = 15; break;
            case 'F': array[i] = 15; break;
        }
    }
    
    for(int i = 0,j = size;i < size;i++,j--)
    {
        ret += array[i] * pow(16,static_cast<double>(j)-1);
    }
    
    delete [] array;
    return ret;
}

void DecToHex(long long int Decimal){
    long long int Quotient;
    char hexadecimal[100];
    int i=1;
    int Helper;
    
    Quotient = Decimal;
    
    while (Quotient!=0) {
        Helper = Quotient % 16;
        
        if (Helper<10) {
            Helper = Helper + 48;
        }
        else{
            Helper = Helper + 55;
        }
        
        hexadecimal[i++] = Helper;
        Quotient = Quotient/16;
    }
    for (int j=i-1; j>0; j--) {
        cout << hexadecimal[j];
    }
}

void Divide(long long int operand1, long long int operand2){
    
    DecToHex(operand1);
    cout << "/";
    DecToHex(operand2);
    cout << " = " << "quotient ";
    DecToHex(operand1/operand2);
    cout << ", remainder ";
    DecToHex(operand1%operand2);
    cout << endl;
}
void Multiply(long long int operand1, long long int operand2){
    
    DecToHex(operand1);
    cout << "*";
    DecToHex(operand2);
    cout << " = ";
    DecToHex(operand1*operand2);
    cout << endl;
}
void Add(long long int operand1, long long int operand2){
    
    DecToHex(operand1);
    cout << "+";
    DecToHex(operand2);
    cout << " = ";
    DecToHex(operand1+operand2);
    cout << endl;
}
void Subtract(long long int operand1, long long int operand2){
    
    DecToHex(operand1);
    cout << "-";
    DecToHex(operand2);
    cout << " = ";
    DecToHex(operand1-operand2);
    cout << endl;
}
void Power(long long int operand1, long long int operand2){
    
    DecToHex(operand1);
    cout << "$";
    DecToHex(operand2);
    cout << " = ";;
    DecToHex(pow(operand1, operand2));
    cout<< endl;
}



int main() {
    // insert code here...
    string Query;
    string op1string;
    string op2string;
    long long int op1;
    long long int op2;
    char perform;
    //char equalsTo;
  
    ifstream HexFile("input.txt");
    HexFile.open("input.txt");
    do {
        HexFile >> Query;
        
        op1string = BeforeOperation(Query);
        op2string = AfterOperation(Query);
        perform = OperatorFound(Query);
        
    //cin >> op1string >> perform >> op2string >> equalsTo;
        
     op1 = StringToInt(op1string);
     op2 = StringToInt(op2string);
    
    if (perform == '/') {
        Divide(op1, op2);
    }
    else if(perform == '*'){
        Multiply(op1, op2);
    }
    else if (perform == '+'){
        Add(op1,op2);
    }
    else if (perform == '-'){
        Subtract(op1,op2);
    }
    else if (perform == '$'){
        Power(op1,op2);
    }
    } while (!HexFile.eof());
    
    HexFile.close();
    
    return 0;
}

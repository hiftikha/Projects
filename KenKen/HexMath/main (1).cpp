//
//  main.cpp
//  HexMath
//
//  Created by Haroon Iftikhar on 4/2/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
/*  This program takes in input in hexadecimal and performs addition, subtraction, division, multiplication, pow on them returning the ouput in dec form
*/

#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <conio.h>
#include <iterator>

using namespace std;
/*
unsigned long ConvertToDec(char hexa[])
{
	char *hexastr;
	int length = 0;
	const int base = 16;     // Base of Hexadecimal Number
	unsigned long decinum = 0;
	int i;

	for (hexastr = hexa; *hexastr != '\0'; hexastr++)  // Finds the length of Hexadecimal Number
	{
		length++;
	}

	hexastr = hexa;  // Now Find Hexadecimal Number
	for (i = 0; *hexastr != '\0' && i < length; i++, hexastr++)
	{
		// Compares *hexastr with ASCII values
		if (*hexastr >= 48 && *hexastr <= 57)   //*hexastr Between 0-9
		{
			decinum += (((int)(*hexastr)) - 48) * pow(base, length - i - 1);
		}
		else if ((*hexastr >= 65 && *hexastr <= 70))   //*hexastr Between A-F
		{
			decinum += (((int)(*hexastr)) - 55) * pow(base, length - i - 1);
		}
		else if (*hexastr >= 97 && *hexastr <= 102)   //*hexastr Between a-f
		{
			decinum += (((int)(*hexastr)) - 87) * pow(base, length - i - 1);
		}
		else
		{
			cout << "\n Invalid Hexadecimal Number...";
		}
	}
	return decinum;
}*/
unsigned long long int power(unsigned long long int val, unsigned long long int _pow) {
	if (_pow <= 0)
		return 1;
	return val * power(val, _pow-1);
}

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
    int size = Query.length();
    char * Result;
    Result = new char[size]();
    //memset(Result, '-', 13);
    
    for (int i=0; i<size; i++) {
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
    Result = new char[Query.length()]();
    //memset(Result, '-', 9);
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

/*unsigned long long int StringToInt(string str)
{
    string temp;
    int * array;
    temp.clear();
    temp = str;
    unsigned long long int ret = 0;
    int size;
    
    size = temp.length() ;
    
    array = new int[size]();
    
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
        ret += array[i] * power(16,j-1);
    }
    
    delete [] array;
    return ret;
}
*/
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
unsigned long long int HexToDec(string Hex) {
	unsigned long long int Decimal;
	int SizeOfHex = Hex.length();
	int Base = 16;
	int Digit = 0;
	int j = SizeOfHex - 1;
	int i = 0;
	unsigned long long int Power;

	while(j>=0)
	{
		Digit = Hex[i];
		if (Hex[i] == '1') {
			Digit = 1;
		}
		if (Hex[i] == '2') {
			Digit = 2;
		}
		if (Hex[i] == '3') {
			Digit = 3;
		}
		if (Hex[i] == '4') {
			Digit = 4;
		}
		if (Hex[i] == '5') {
			Digit = 5;
		}
		if (Hex[i] == '6') {
			Digit = 6;
		}
		if (Hex[i] == '7') {
			Digit = 7;
		}
		if (Hex[i] == '8') {
			Digit = 8;
		}
		if (Hex[i] == '9') {
			Digit = 9;
		}
		if (Hex[i] == '0') {
			Digit = 0;
		}
		if (Hex[i] == 'A'){
			Digit = 10;
		}
		if (Hex[i] == 'B'){
			Digit = 11;
		}
		if (Hex[i] == 'C'){
			Digit = 12;
		}
		if (Hex[i] == 'D'){
			Digit = 13;
		}
		if (Hex[i] == 'E'){
			Digit = 14;
		}
		if (Hex[i] == 'F'){
			Digit = 15;
		}
		Power = power(Base, j);
		Decimal = Decimal + Digit*Power;
		i++;
		j--;
	}
	return Decimal;
}

int SwitchHex(char Hex) {
	int HexVal;
	switch (Hex) {
	case '0': HexVal = 0; break;
	case '1': HexVal = 1; break;
	case '2': HexVal = 2; break;
	case '3': HexVal = 3; break;
	case '4': HexVal = 4; break;
	case '5': HexVal = 5; break;
	case '6': HexVal = 6; break;
	case '7': HexVal = 7; break;
	case '8': HexVal = 8; break;
	case '9': HexVal = 9; break;
	case 'A': HexVal = 10; break;
	case 'B': HexVal = 11; break;
	case 'C': HexVal = 12; break;
	case 'D': HexVal = 13; break;
	case 'E': HexVal = 14; break;
	case 'F': HexVal = 15; break;
	}
	return HexVal;
}

char SwitchDec(int Dec) {
	char Hex;
	switch (Dec) {
	case 0: Hex = '0'; break;
	case 1: Hex = '1'; break;
	case 2: Hex = '2'; break;
	case 3: Hex = '3'; break;
	case 4: Hex = '4'; break;
	case 5: Hex = '5'; break;
	case 6: Hex = '6'; break;
	case 7: Hex = '7'; break;
	case 8: Hex = '8'; break;
	case 9: Hex = '9'; break;
	case 10: Hex = 'A'; break;
	case 11: Hex = 'B'; break;
	case 12: Hex = 'C'; break;
	case 13: Hex = 'D'; break;
	case 14: Hex = 'E'; break;
	case 15: Hex = 'F'; break;
	}
	return Hex;
}
char* reverseChar(char* str, int len)
{
	char* Result;
	Result = str;
	for (int i = 0; i<len / 2; i++)
	{
		swap(Result[i], Result[len - i - 1]);
	}
	return Result;
}
void HexSubtraction(string op1, string op2) {

	char * Result;
	Result = new char[op1.length()]();
	char * op1char;
	op1char = new char[op1.length()]();
	char * op2char;
	op2char = new char[op2.length()]();
	char Difference[5] = { NULL };
	int op1number = 0;
	int op2number = 0;
	int op1carry = 0;
	int op2carry = 0;
	int val = 0;
	int i = op1.length() - 1;
	int j = op2.length() - 1;
	int borrow = 0;
	int difference;

	op1.copy(op1char, op1.length());
	op2.copy(op2char, op2.length());

	while(i>0)
	{
		if (j<0)
		{
			op1number = SwitchHex(op1char[i]);
			op2number = 0;
		}
		else {
		op1number = SwitchHex(op1char[i]);
		op2number = SwitchHex(op2char[j]);
		}

		difference = op1number-op2number-borrow;

		if (difference < 0)
		{
			difference += 16;
			borrow = 1;
		}
		else
			borrow = 0;
		/*if (carry)
		{
			op1number = op1number - 1;
		}
		if (op1number>op2number)
		{
			val = op1number - op2number;
			Result[i] = SwitchDec(val);
			i--;
			j--;
		}
		if (op1number<op2number)
		{
			op1carry = SwitchDec(SwitchHex(op1char[i-1]-1));
			if (op1char[i - 1] == '0')
			{
				op1carry = SwitchDec(SwitchHex(op1char[i - 1] + 9));
			}
			carry = true;
			op1number = SwitchHex(op1char[i] + 10);
		}
		*/
		
		itoa(difference, Difference, 16);
		strcat(Result, Difference);
		i--;
		j--;
	}

	reverseChar(Result, op1.length()-1);

	cout << op1 << "-" << op2 << " = ";
	for (int l = 0; l < op1.length(); l++)
	{
		Result[l] = toupper(Result[l]);
		cout << Result[l];
	}
	cout << endl;
}

int main() {
    // insert code here...
    string Query;
    string op1string;
    string op2string;
    unsigned long long int op1;
    unsigned long long int op2;
    char perform;
    //char equalsTo;
  
    ifstream HexFile;
    HexFile.open("Haroon.txt");
	    //HexFile.open("input.txt");
	    do {
		    //HexFile >> Query;
		    getline(HexFile, Query);

		    op1string = BeforeOperation(Query);
		    op2string = AfterOperation(Query);
		    perform = OperatorFound(Query);

		    stringstream HexOp1;
		    stringstream HexOp2;
/*
		    sscanf(op1string.c_str(), "%x", &op1);
		    sscanf(op2string.c_str(), "%x", &op2);
		    //cin >> op1string >> perform >> op2string >> equalsTo;
		    char *cstr = new char[op1string.length() + 1];
		    strcpy(cstr, op1string.c_str());

		    op1 = ConvertToDec(cstr);
		    delete[] cstr;

		    strcpy(cstr, op1string.c_str());
		    op2 = ConvertToDec(cstr); 
		    HexOp1 << hex << op1string;
		    HexOp2 << hex << op2string;
		    HexOp1 >> op1;
		    HexOp2 >> op2;*/
		    
		    op1 = HexToDec(op1string);
		    op2 = HexToDec(op2string);

		    if (perform == '/') {
			    Divide(op1, op2);
		    }
		    else if (perform == '*') {
			    Multiply(op1, op2);
		    }
		    else if (perform == '+') {
			    Add(op1, op2);
		    }
		    else if (perform == '-') {
			   // Subtract(op1, op2);
			  HexSubtraction(op1string, op2string);
		    }
		    else if (perform == '$') {
			    Power(op1, op2);
		    }
	    } while (HexFile.good());
	    HexFile.close();

	    system("pause");
	    return 0;
    }
    //HexFile.close();

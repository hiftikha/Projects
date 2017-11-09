//
//  main.cpp
//  DecimalToBinaryHex
//
//  Created by Haroon Iftikhar on 1/15/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Program converts a Decimal to Binary, Hexadecimal and BCD

int Dec;


int Binary[8] = {0,0,0,0,0,0,0,0};
char HexTable[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char Hex[2] = {'0','0'};
int BCD[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void DecToBinary (int Dec){
    
    if (Dec >= 128) {
        Dec = Dec - 128;
        Binary[0] = 1;
    }
    if (Dec >= 64) {
        Dec = Dec - 64;
        Binary[1] = 1;
    }
    if (Dec >= 32) {
        Dec = Dec - 32;
        Binary[2] = 1;
    }
    if (Dec >= 16) {
        Dec = Dec - 16;
        Binary[3] = 1;
    }
    if (Dec >= 8) {
        Dec = Dec - 8;
        Binary[4] = 1;
    }
    if (Dec >= 4) {
        Dec = Dec - 4;
        Binary[5] = 1;
    }
    if (Dec >= 2) {
        Dec = Dec - 2;
        Binary[6] = 1;
    }
    if (Dec >= 1) {
        Dec = Dec - 1;
        Binary[7] = 1;
    }
};

void PrintBinary(int Binary[]){
    
    for (int i =0; i<8; i++) {
        cout << Binary[i];
    }
 //   cout << endl;
}

void ResetBinary(int Binary[]){
    
    for (int i =0; i<8; i++) {
        Binary[i] = 0;
}
    
}

void DecToHex (int Dec){
    
    int Quotient;
    int Remainder;
    
    Remainder = Dec%16;
    Quotient = Dec/16;
    
    Hex[0] = HexTable[Quotient];
    Hex[1] = HexTable[Remainder];
    
}

void PrintHex(char Hex[]){
    
    for (int i =0; i<2; i++) {
        cout << Hex[i];
    }
  //  cout << endl;
}
void ResetHex(char Hex[]){
    
    for (int i =0; i<2; i++) {
        Hex[i] = 0;
    }
    
}

void DecToBCD(int Dec){
    
    string DecimalString = "";
    int DecToConvert;
    DecimalString = to_string(Dec);
    
    if (Dec < 10) {
        
        DecToBinary(Dec);
        
        BCD[8] = Binary[4];
        BCD[9] = Binary[5];
        BCD[10] = Binary[6];
        BCD[11] = Binary[7];
        
        ResetBinary(Binary);
    }
    else if (Dec < 100) {
        
        DecToConvert = DecimalString[0] - 48;
        DecToBinary(DecToConvert);
        
        BCD[4] = Binary[4];
        BCD[5] = Binary[5];
        BCD[6] = Binary[6];
        BCD[7] = Binary[7];
        
        ResetBinary(Binary);
        
        DecToConvert = DecimalString[1] - 48;
        DecToBinary(DecToConvert);
        
        BCD[8] = Binary[4];
        BCD[9] = Binary[5];
        BCD[10] = Binary[6];
        BCD[11] = Binary[7];
        
        ResetBinary(Binary);

    }
    else {
        
        DecToConvert = DecimalString[0] - 48;
        DecToBinary(DecToConvert);
      
        BCD[0] = Binary[4];
        BCD[1] = Binary[5];
        BCD[2] = Binary[6];
        BCD[3] = Binary[7];
    
         ResetBinary(Binary);
    
         DecToConvert = DecimalString[1] - 48;
         DecToBinary(DecToConvert);
    
        BCD[4] = Binary[4];
        BCD[5] = Binary[5];
        BCD[6] = Binary[6];
        BCD[7] = Binary[7];
    
           ResetBinary(Binary);

         DecToConvert = DecimalString[2] - 48;
         DecToBinary(DecToConvert);
    
        BCD[8] = Binary[4];
        BCD[9] = Binary[5];
        BCD[10] = Binary[6];
        BCD[11] = Binary[7];
    
           ResetBinary(Binary);
    }

    
}

void PrintBCD(int BCD[]){
    
    for (int i =0; i<12; i++) {
        cout << BCD[i];
    }
   // cout << endl;
}

void ResetBCD(int BCD[]){
    
    for (int i =0; i<12; i++) {
        BCD[i] = 0;
    }
    
}


int main(){
    
  //  cout << "Here is your Decimal daddy!" << endl << endl;
    
    cout << "DECIMAL" << "       " << "BINARY" << "       " << "HEXADECIMAL" << "       " << "BCD" << endl;

    
    
    
    for (int decimal = 0; decimal <= 255; decimal++) {
      
        cout << decimal;
    cout << "           ";
         DecToBinary(decimal);
        PrintBinary(Binary);
        ResetBinary(Binary);
    cout << "              ";
        
        DecToHex(decimal);
        PrintHex(Hex);
        ResetHex(Hex);
    cout << "       ";
        
        DecToBCD(decimal);
        PrintBCD(BCD);
        ResetBCD(BCD);
    cout << endl;
        
    }
    
  /*
    DecToBinary(Dec);
    PrintBinary(Binary);
   */
    
    return 0;
}

int prod(int a, int b)

{
    if ((b =0)) {
        return 0;
    }
    else
        return prod(a, b-1)+a;



}

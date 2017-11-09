//
//  Assemblers.cpp
//  2-Way Assembler C++
//
/*
        Purpose: Program 5
        Algorithms Used: Assembler 1 and Assembler 2
        
        Course: CIS 310 David Yoon
 */
//  Created by Haroon Iftikhar on 4/23/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct MachineCode{
    string instruction;
    string code;
} Instruction[15] =
    {{"MOVE","303C"},{"MOVE","33FC"},{"MOVE","3039"},{"MOVE","33C0"},
    {"ADDI","0640"},{"ADDI","0679"},{"ADD","D079"},{"ADD","D179"},
    {"SUBI","0440"},{"SUBI","0479"},{"SUB","9079"},{"SUB","9179"},
    {"TRAP","4E40"},{"TRAP","4E41"},{"TRAP","4E42"}};
string BeforeOperation(string Query, char Sign){
    char * Result;
    Result = new char[Query.length()]();
    
    for (int i=0; i<Query.length(); i++) {
        if (Query[i] == Sign) {
            return Result;
        }
        Result[i] = Query[i];
    }
    return Result;
}

string AfterSign(string Query, char Sign){
    char * Result;
    Result = new char[Query.length()]();

    bool OperatorFound = false;
    int j = 0;
    
    for (int i=0; i<Query.length(); i++) {
        if (Query[i] == ';') {
            return Result;
        }
        if (Sign == ' ' && Query[i] == ',') {
            return Result;
        }
        if (OperatorFound) {
            Result[j] = Query[i];
            j++;
        }
        if (Query[i] == Sign) {
            OperatorFound = true;
        }
    }
    return Result;
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
string DecToHex(long long int Decimal){
   
    long long int Quotient;
    char hexadecimal[3];
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
    string Hex(reverseChar(hexadecimal, 3));
    return Hex;
    /*for (int j=i-1; j>0; j--) {
        cout << hexadecimal[j];
    }
     */
}

int main(){
    
    //int WhichOne = 0;
    bool OutputOrNot = false;
    string Line;
    string MainAddress;
    string Address;
    string MachineCode;
    string Operand;
    string Instruction;
    string InstructionCheckOne;
    string InstructionCheckTwo;
    string HexHelper;
    int HexNumber;
    string Hex;
    
    ifstream ProgramInput;
    ofstream ProgramOutput;
    ProgramInput.open("/Users/harooniftikhar/Desktop/2-Way Assembler C++/2-Way Assembler C++/Input.txt");
    ProgramOutput.open("/Users/harooniftikhar/Desktop/2-Way Assembler C++/2-Way Assembler C++/Output.txt");
    ProgramOutput << "Address      Machine code     Operands       Instructions" << endl;
    while (getline(ProgramInput,Line)) {
        //cout << AfterSign(Line,'$');
        //ProgramInput >>Instruction >> InstructionCheckOne >> InstructionCheckTwo;
        Instruction = BeforeOperation(Line,' ');
        InstructionCheckOne = AfterSign(Line, ' ');
        InstructionCheckTwo = AfterSign(Line, ',');
            if (Instruction == "ORG") {
                MainAddress = InstructionCheckOne;
            }
            if (Instruction == "MOVE") {
                OutputOrNot = true;
                if (InstructionCheckOne.find("D")!= string::npos) {
                    Address = "33C0";
                }
                if (InstructionCheckOne.find("$")!= string::npos) {
                    Address = "3039";
                }
                if (InstructionCheckOne.find("#")!= string::npos) {
                    if (InstructionCheckTwo.find("D")!= string::npos) {
                        Address = "303C";
                    }
                    if (InstructionCheckTwo.find("$")!= string::npos) {
                        Address = "33FC";
                    }
                }
            }
            if (Instruction == "ADDI") {
                OutputOrNot = true;
                if (InstructionCheckTwo.find("D")!= string::npos) {
                    Address = "0640";
                }
                if (InstructionCheckTwo.find("$")!= string::npos) {
                    Address = "0679";
                }
            }
            if (Instruction == "ADD") {
                OutputOrNot = true;
                if (InstructionCheckOne.find("D")!= string::npos) {
                    Address = "D179";
                }
                if (InstructionCheckTwo.find("D")!= string::npos) {
                    Address = "D079";
                }
            }
            if (Instruction == "TRAP") {
                OutputOrNot = true;
                if (InstructionCheckOne.find("0")!= string::npos) {
                    Address = "4E40";
                }
                if (InstructionCheckOne.find("1")!= string::npos) {
                    Address = "4E41";
                }
                if (InstructionCheckOne.find("2")!= string::npos) {
                    Address = "4E42";
                }
            }
        if (Instruction == "END") {
            break;
        }
        if (Instruction != "TRAP" && InstructionCheckOne.find("#")!= string::npos) {
            HexHelper = InstructionCheckOne.substr(2,2);
            HexNumber = stoi(HexHelper);
            Hex = DecToHex(HexNumber);
        }
        else{
            Hex = "0";
        }
        if (OutputOrNot) {
            ProgramOutput << "00000500           " << Address << "           "<< Hex <<"           "<< Instruction <<"           "<<InstructionCheckOne;
            if (InstructionCheckTwo.length() != 0) {
                ProgramOutput <<","<<InstructionCheckTwo;
            }
            ProgramOutput << endl;
            OutputOrNot = false;
        }
    }
}

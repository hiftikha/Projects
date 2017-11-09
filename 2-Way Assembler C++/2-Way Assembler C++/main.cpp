//
//  main.cpp
//  2-Way Assembler C++
//
//  Created by Haroon Iftikhar on 4/23/17.
//  Copyright © 2017 Haroon Iftikhar. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>

using namespace std;

struct optab{
    char code[10];
    char objcode[10];
};
struct symtab{
    char symbol[10];
    int address;
} mysymtab[10];
int StartAddress;
int locctr;
int symcount = 0;
int length;
char line[20];
char label[8];
char opcode[8];
char operand[8];
char programname[10];
optab optablist[3] = { {"LDA","00"},{"JMP","01"},{"STA","02"}};

void CheckLabel()
{
    int k,dupsym=0;
    for(k=0;k<symcount;k++)
        if(!strcmp(label,mysymtab[k].symbol))
        {
            mysymtab[k].address=-1;
            dupsym=1;
            break;
        }
    if(!dupsym)
    {
        strcpy(mysymtab[symcount].symbol,label);
        mysymtab[symcount++].address=locctr;
    }
}
void CheckOpCode()
{
    int k=0,found=0;
    for(k=0;k<3;k++)
        if(!strcmp(opcode,optablist[k].code))
        {
            locctr+=3;
            found=1;
            break;
        }
    if(!found)
    {
        if(!strcmp( opcode,"WORD")) locctr+=3;
        else if (!strcmp(opcode,"RESW"))locctr+=(3*atoi(operand));
        else if(!strcmp(opcode,"RESB"))locctr+=atoi(operand);
    }
}
void ReadLine()
{
    char buff[8],word1[8],word2[8],word3[8];
    int i,j=0,count=0;
    label[0]=opcode[0]=operand[0]=word1[0]=word2[0]=word3[0]='\0';
    for(i=0;line[i]!='\0';i++)
    {
        if(line[i]!=' ')
            buff[j++]=line[i];
        else
        {
            buff[j]='\0';
            strcpy(word3,word2);
            strcpy(word2,word1);
            strcpy(word1,buff);
            j=0;
            count++;
        }
    }
    buff[j-1]='\0';
    strcpy(word3,word2);
    strcpy(word2,word1);
    strcpy(word1,buff);
    switch(count)
    {
        case 0:strcpy(opcode,word1);
            break;
        case 1:{strcpy(opcode,word2);strcpy(operand,word1);}
            break;
        case 2:{strcpy(label,word3);strcpy(opcode,word2);strcpy(operand,word1);}
            break;
    }
}
char* itoa(int val, int base){
    
    static char buf[32] = {0};
    
    int i = 30;
    
    for(; val && i ; --i, val /= base)
        
        buf[i] = "0123456789abcdef"[val % base];
    
    return &buf[i+1];
    
}
void AssemblerPassOne(){
    ifstream AssemblerFileInput;
    ofstream AssemblerFileOutput;
    AssemblerFileInput.open("/Users/harooniftikhar/Desktop/2-Way Assembler C++/2-Way Assembler C++/Input.txt");
    AssemblerFileOutput.open("/Users/harooniftikhar/Desktop/2-Way Assembler C++/2-Way Assembler C++/Output.txt");
    AssemblerFileInput.getline(line,20);
    ReadLine();
    
    if (!strcmp(opcode, "START")) {
        StartAddress=atoi(operand);
        locctr=StartAddress;
        strcpy(programname, label);
        AssemblerFileOutput << line << endl;
        AssemblerFileInput.getline(line,20);
    }
    else{
        programname[0] = '\0';
        StartAddress = 0;
        locctr = 0;
    }
    cout << locctr << "  " << label << "  " << opcode << "  " << operand << endl;
    
    while (strcmp(line, "END")!=0) {
        ReadLine();
        cout << locctr << "  " << label << "  " << opcode << "  " << operand << endl;
        if (label[0]!='\0') {
            CheckLabel();
        }
        CheckOpCode();
        AssemblerFileOutput << label << "  " << opcode << "  " << operand << endl;
        AssemblerFileInput.getline(line,20);
    }
    cout << locctr << " " << line;
    AssemblerFileOutput << line << endl;
    AssemblerFileInput.close();
    AssemblerFileOutput.close();
}
void AssemblerPassTwo(){
    int currtxtlen=0,foundopcode,foundoperand,chk,operandaddr,recaddr=0;
    char record[30];
    char part[8];
    char * value = nullptr;
    
    ifstream AssemblerFileInput;
    ofstream AssemblerFileOutput;
    AssemblerFileInput.open("/Users/harooniftikhar/Desktop/2-Way Assembler C++/2-Way Assembler C++/Input.txt");
    AssemblerFileOutput.open("/Users/harooniftikhar/Desktop/2-Way Assembler C++/2-Way Assembler C++/Output.txt");
    AssemblerFileInput.getline(line,20);
    ReadLine();
    
    if (!strcmp(opcode, "START")) {
        AssemblerFileInput.getline(line,20);
    }
    cout << "Corresponding object code is.." << endl;
    cout << programname << "    "<< StartAddress << "   "<< length << endl;
    AssemblerFileOutput << programname << "    "<< StartAddress << "   "<< length << endl;
    recaddr = StartAddress;
    record[0] = '\0';
    while (strcmp(line, "END")!=0) {
        operandaddr=foundoperand=foundopcode=0;
        part[0]='\0';
        ReadLine();
        for (chk = 0; chk < 3; chk++) {
            if (!strcmp(opcode, optablist[chk].code)) {
                foundopcode=1;
                strcpy(part, optablist[chk].objcode);
                if (operand[0]!='\0') {
                    for (chk=0; chk<symcount; chk++) {
                        if (!strcmp(mysymtab[chk].symbol, operand)) {
                            value = itoa(mysymtab[chk].address,10);
                            strcat(part, value);
                            foundoperand=1;
                        }
                        if (!foundoperand) {
                            strcat(part, "err");
                        }
                    }
                }
            }
        }
        if (!foundopcode) {
            if (strcmp(opcode, "BYTE")==0|| strcmp(opcode,"WORD")||strcmp(opcode,"RESB")) {
                strcat(part, operand);
            }
        }
        if (currtxtlen+strlen(part)<=8) {
            strcat(record, "^");
            strcat(record, part);
            currtxtlen+=strlen(part);
            strcpy(record, part);
        }
        AssemblerFileInput.getline(line,20);
    }
    cout << "   " << recaddr << "   " << currtxtlen << "    " << record << endl;
    AssemblerFileOutput << "   " << recaddr << "   " << currtxtlen << "    " << record << endl;
    cout << StartAddress << endl;
    AssemblerFileOutput << StartAddress << endl;
    AssemblerFileInput.close();
    AssemblerFileOutput.close();
}
int main(){
    AssemblerPassOne();
    length=locctr-StartAddress;
    AssemblerPassTwo();
    return 0;
}

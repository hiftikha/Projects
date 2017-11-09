//
//  main.cpp
//  Learning
//
//  Created by Haroon Iftikhar on 11/25/16.
//  Copyright © 2016 Haroon Iftikhar. All rights reserved.
//

#include <iostream>
#include <sstream>

using namespace std;

class Employee {
    
protected:
    string name;
    double pay;
    
public:
    Employee() {
        name = " ";
        pay = 0;
    }
    Employee(string empName, double payRate){
        name = empName;
        pay = payRate;
    }
    string getName(){
        return name;
    }
    double getPay(){
        return pay;
    }
    void setName(string empName){
        name = empName;
    }
    void setPay(double payRate){
        pay = payRate;
    }
    string toString(){
        stringstream output;
        output << name << ": " << pay;
        return output.str();
    }
    double grossPay(int hours){
        return pay* hours;
    }
    
};

// derived class

class Manager : public Employee {
    
protected:
    bool salaried;
    
public:
    Manager(string name, double payRate, bool isSalaried)
    : Employee(name, payRate)
    {
        salaried = isSalaried;
    }
    bool getSalaried(){
        return salaried;
    }
    double grossPay(int hours){
        if (salaried) {
            return pay;
        } else {
            return pay * hours;
        }
    }
    string toString(){
        stringstream output;
        string salary;
        if (salaried) {
            salary = "Salaried";
        } else {
            salary = "Hourly";
        }
        output << name << ": " << pay << ": " << salary;
        return output.str();
    }
    
};

int main(){
    
    Employee emp1("Haroon Iftikhar", 24000);
    Employee emp2("Aroosa Khan", 40000);

    
}

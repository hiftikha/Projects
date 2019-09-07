//
//  main.cpp
//  traffic
//
//  Created by Haroon Iftikhar on 4/10/18.
//  Copyright © 2018 UofM. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>

using namespace std;

typedef struct _directions {
    char dir_original;
    char dir_target;
} directions;

typedef struct carInfo{
    int cid;
    double time;
    directions dir;
} carInformation;

int CrossIntersection(directions dir){
    if (dir.dir_original == 'N') {
        if (dir.dir_target == 'E') {
            return 1;
        }
        if (dir.dir_target == 'W') {
            return 3;
        }
        if (dir.dir_target == 'N') {
            return 2;
        }
    }
    if (dir.dir_original == 'S') {
        if (dir.dir_target == 'E') {
            return 3;
        }
        if (dir.dir_target == 'W') {
            return 1;
        }
        if (dir.dir_target == 'S') {
            return 2;
        }
    }
    if (dir.dir_original == 'E') {
        if (dir.dir_target == 'E') {
            return 2;
        }
        if (dir.dir_target == 'N') {
            return 3;
        }
        if (dir.dir_target == 'S') {
            return 1;
        }
    }
    if (dir.dir_original == 'W') {
        if (dir.dir_target == 'W') {
            return 2;
        }
        if (dir.dir_target == 'N') {
            return 1;
        }
        if (dir.dir_target == 'S') {
            return 3;
        }
    }
    return 0;
}

void Car(directions dir){
    //ArriveIntersection(dir);
    cout << "Time " << CrossIntersection(dir) << " Car " << "(->" << dir.dir_original << " ->" << dir.dir_target << ") crossing" << endl;
    //ExitIntersection(dir);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int numCars = 0;
    int cid = 0;
    
    
    directions NE = {'N','E'};
    directions NW = {'N','W'};
    directions NN = {'N','N'};
    directions SE = {'S','E'};
    directions SW = {'S','W'};
    directions SS = {'S','S'};
    directions EE = {'E','E'};
    directions EN = {'E','N'};
    directions ES = {'E','S'};
    directions WW = {'W','W'};
    directions WN = {'W','N'};
    directions WS = {'W','S'};
    
    //directions possibleTurns = [NE,NW,NN,SE,SW,SS,EE,EN,ES,WW,WN,WS];
    
    
    struct carInfo cars[10];
    vector<thread> carThreads;
    ifstream fileReader;
    fileReader.open("traffic.txt");
    
    while(!fileReader.eof()) {
        fileReader >> cars[numCars].cid >> cars[numCars].time >> cars[numCars].dir.dir_original >> cars[numCars].dir.dir_target;
        cout << "Time " << cars[numCars].time << ": Car " << cars[numCars].cid << "(->" << cars[numCars].dir.dir_original << " ->" << cars[numCars].dir.dir_target << ") arriving" << endl;
        cid++;
        numCars++;
        
        if (numCars == 1) {
            this_thread::sleep_for(chrono::seconds(int(cars[numCars].time)));
        } else{
            this_thread::sleep_for(chrono::seconds(int(cars[numCars].time - cars[numCars-1].time)));
            
        }
        directions dirCar = {cars[numCars].dir.dir_original, cars[numCars].dir.dir_target};
        carThreads.push_back(thread(Car, dirCar));
    }
    fileReader.close();
    //cout << "Here: " << cars[5].time;
    //cout << "Hello, World!\n";
    return 0;
}

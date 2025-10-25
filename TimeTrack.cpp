#include <iostream>
#include<fstream>
#include <chrono>
#include "helpers.hpp"

using namespace std;
using namespace std::chrono;

int sizes[7] = {10,20,30,50,100,250,500};

void writeToFiles(){
    for (int i = 3; i < 8; i++){
        string filename = "timeTests/"+to_string(sizes[i])+".txt";
        int maxNum = sizes[i]*2;
        ofstream file(filename);
        file << sizes[i] << endl;
        for (int x = 0; x < sizes[i]; x++){
            file << rand()%maxNum<<" ";
        }
        
    }
    
}

Array<int> readInArray(string filename){
    int size;
    ifstream file(filename);
    file >> size;
    Array<int> input = Array<int>(size);
    int currentRead;
    while (file>>currentRead){
        input.add(currentRead);
    }
    file.close();
    return input;
}

void timeRecursiveFunction(function<Array<int>(Array<int>& ,int)> func ){
    ofstream file("timeTests/results.txt");
    for (int i = 0; i < 8; i++){
        Array<int> x = readInArray("timeTests/"+to_string(sizes[i])+".txt");
        int size = sizes[i];
        auto start = high_resolution_clock::now();
        for (int j = 1; j <= size; j++)
        {
            func(x,j);
        }
        
        auto end = high_resolution_clock::now();
        auto time = duration_cast<microseconds>(end-start);
        file << time.count() <<endl;
    }
    file << " --- ";
    file.close();
    
}

void timeDPfunction(function <int(Array<int>)> func){
    ofstream file("timeTests/results.txt");
    for (int i = 0; i < 8; i++){
        Array<int> x = readInArray("timeTests/"+to_string(sizes[i])+".txt");
        int size = sizes[i];
        auto start = high_resolution_clock::now();
        func(x);
        auto end = high_resolution_clock::now();
        auto time = duration_cast<nanoseconds>(end-start);
        file << time.count() <<endl;
    }
    file << " --- ";
    file.close();
}
#include <iostream>
#include "helpers.hpp"
#include "TimeTrack.cpp"

using namespace std;

int incrSubSeqDP(Array<int> A){
    Array<int> maxSequenceLens(A.len);
    for (int i = 1; i <= A.len; i++){
        maxSequenceLens.add(1);
        for (int x = 1; x <= i-1; x++){
            if( A.get(x)<A.get(i) && maxSequenceLens.get(i) < maxSequenceLens.get(x)+1 ){
                maxSequenceLens.set(i,maxSequenceLens.get(x)+1);
            }
        }   
    }
    int max = 0;
    for (int i = 1; i < A.len; i++){
        int currentMax = maxSequenceLens.get(i); 
        if(max< currentMax){
            max = currentMax;
        }
    }
    return max;
}

int main(){
    // Array<int> input = readInArray<int>();
    // int max = incrSubSeqDP(input);
    // cout<<max;
    
    timeDPfunction(&incrSubSeqDP);

    return 0;
}
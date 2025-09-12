#include <iostream>
#include <iomanip>
#include <climits>
#include "runner.h"

using namespace std;

struct sum{
    float value;
    int count = 1;
};

int n;
int uniqueSums = 0;

void addElement(sum sums[], float value){
    //Check if sum exists already
    for (int i = 0; i < uniqueSums; i++)
    {
        //If it exists increment its count
        if(sums[i].value==value){
            sums[i].count++;
            return;
        }
    }
    //otherwise make a new one
    sum newSum = {value};
    sums[uniqueSums] =  newSum;
    uniqueSums++;
}

sum findMaxPairs(float addends[], int n){
    sum* sums = new sum[(n*(n-1))/2];
    for (int index1 = 0; index1 < n; index1++)
    {
        for (int index2 = index1+1; index2 < n; index2++)
        {
            float currentSum = addends[index1] + addends[index2];
            addElement(sums,currentSum);
        }
        
    }
    
    sum maxPairs = {__FLT_MAX__, 0};
    for (int i = 0; i < uniqueSums; i++)
    {
        sum currentSum = sums[i];
        if(currentSum.count>maxPairs.count || (currentSum.count==maxPairs.count && currentSum.value<maxPairs.value) ){
            maxPairs=currentSum;
        }
    }
    sum returnedPair = maxPairs;
    delete[] sums;
    return returnedPair;
}

int main(){
    cin>>n;
    float addends[n];
    readInArray(addends,n);
    sum response = findMaxPairs(addends,n);
    cout << (response.count) << " " << fixed << setprecision(6) << response.value;
    return 0;
}
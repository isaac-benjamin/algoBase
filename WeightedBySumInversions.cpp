#include <iostream>
#include "helpers.h"

using namespace std;

struct InvOut{
    unsigned long long weight;
    Array<long long> array;
};

InvOut findInversionWeight( Array<long long> input ){
    
    long long length = input.len;
    
    //Base case
    if(length==1){
        return {0, input};
    }

    //Divide in two
    long long midpoint = length/2;
    Array<long long> left = input.subSet(1,midpoint);
    Array<long long> right = input.subSet(midpoint+1,length);

    //Recurse
    InvOut leftResult = findInversionWeight(left);
    InvOut rightResult = findInversionWeight(right);

    Array<long long> leftSorted = leftResult.array;
    Array<long long> rightSorted = rightResult.array;

    //Get sum of all left numbers
    unsigned long long leftSum = 0;
    for (size_t i = 1; i <= left.len; i++)
        leftSum += leftSorted.get(i);
    
    //Find inversion sums between each
    long long leftIndex =1, rightIndex = 1;
    unsigned long long middleWeight = 0; //Like mike tysons punch out???
    while ( leftIndex <= leftSorted.len && rightIndex <= rightSorted.len ){
        if( leftSorted.get(leftIndex) <= rightSorted.get(rightIndex) ){
            leftSum -= leftSorted.get(leftIndex);
            leftIndex++;
        }else{
            middleWeight += leftSum + rightSorted.get(rightIndex)*(1+leftSorted.len-leftIndex);
            rightIndex++;
        }
    } 
    return {leftResult.weight + rightResult.weight + middleWeight, merge(leftSorted,rightSorted)};
}

int main(){
    Array<long long> x = readInArray<long long>();
    unsigned long long weight = findInversionWeight(x).weight;
    cout << weight; 

    return 0;
}
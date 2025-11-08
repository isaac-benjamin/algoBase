#include <iostream>
#include <memory>

#include "TimeTrack.cpp"
#include "helpers.hpp"
#include <cassert>

using namespace std;

/*
incrSubseqRecursive(A, j), computes the maximum length of an increasing subsequence of the sequence a1, a2, . . . , an (stored in the array A)
that ends with the element aj
This function tries to find a previous element ai such that i < j and ai < aj
then it recursively searches for the maximum length of an increasing subsequence of a1, a2, . . . , ai ending with ai
Try up to j − 1 different i’s and choose the one that yields the maximum subsequence length

By concatenating aj to the subsequence of a1, a2, . . . , ai ending with this ai
we get a longest increasing subsequence of
a1, a2, . . . , aj
.
*/

//To whomever grades this: I am still learning C++ so this might be absolute gobshite, IM SO SORRY
//I had to look up so much stuff to stop from deleting information I needed to return lol
//Before I wasn't deleting my pointers and when I ran test case 5 my computer crashed XD

Array<int> incrSubSeqRecursive(Array<int>& A, int endIndex){

    int endElem = A.get(endIndex);
    Array< Array<int>> subsequences(endIndex-1);

    for (int i = endIndex-1; i >= 1; i--){
        if(A.get(i)<endElem){
            subsequences.add(incrSubSeqRecursive(A,i));
        }
    }

    //Include case if j is smaller than all earlier elements
    Array<int> longest = Array<int>(endIndex);
    for (int i = 1; i <= subsequences.len; i++){
        Array<int> cur = subsequences.get(i);
        if(cur.len > longest.len){
            longest.removeAll();
            longest.add( cur );
        }
    }
    longest.add(endElem);
    return longest;    
}

int main(){
    Array<int> input = readInArray<int>();
    Array<int> maxSubseq = incrSubSeqRecursive(input,input.len);
    int maxLen = maxSubseq.len;
    for (int i = 1; i <= input.len; i++)
    {
        int currentSubLen = incrSubSeqRecursive(input,i).len;
        if( maxLen < currentSubLen ){
            maxLen = currentSubLen;
        }
        // cout<<i;
    }
    
    cout << maxLen;

    // timeRecursiveFunction( &incrSubSeqRecursive );

    return 0;
}
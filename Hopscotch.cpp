#include <iostream>

#include "helpers.h"

using namespace std;

/*
    Let the weight for each stored index be the max of:
        the previous square
        the current value + index - 2
        the current value + index - 3
*/

int main(){

    Array<int> hops = readInArray<int>();
    Array<int> maxSums = Array<int>(hops.len);

    maxSums.add(hops.get(1));
    maxSums.add(hops.get(1));
    maxSums.add(hops.get(3)+hops.get(1));

    for (int i = 4; i <= hops.len; i++)
    {
        int currentWeight = hops.get(i);
        int previousMax = maxSums.get(i-1);
        int twoJump = currentWeight + maxSums.get(i-2);
        int threeJump = currentWeight + maxSums.get(i-3);
        int optimalJump = max({previousMax,twoJump,threeJump});
        maxSums.add(optimalJump);
    }
    
    cout<<maxSums.get(maxSums.len);
    return 0;
}
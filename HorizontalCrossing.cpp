#include <iostream>
#include "helpers.h"
/*
    Step 1: Make list - A - of y values. 
    Step 2: Make list - B - of y values that are sign changes (point is either higher or lower than both its neighbors)
    
    REMEMBER: make rules for when change in y is 0!
*/

struct Point{
    int current;
    int next;
};

int findCrossings(Array<int> yVals){
    int n = yVals.len;
    Array<Point> signChanges = Array<Point>(n);
    for (int i = 1; i <= n; i++){
        
    }
    
    
}

int main(){
    //Read in input
    int totalPoints;
    cin >> totalPoints;

    Array<int> yVals = Array<int>(totalPoints);

    for (int i = 1; i <=totalPoints; i++){
        cin.ignore(10,' ');
        int x;
        cin >> x;
        yVals.add(x);
    }
    int crossings = findCrossings(yVals);
    cout << crossings;
    return 0;
}
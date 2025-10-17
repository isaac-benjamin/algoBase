#include <iostream> 

#include "helpers.hpp"

using namespace std;

struct coords{
    int x;
    int y;
};

int main(){
    int size;
    cin >> size;
    Array<coords> cops = Array<coords>(size);
    int xAvg=0, yAvg =0, smallestDist = 0;
    for (int i = 0; i < size; i++){
        int x,y;

        cin>>x;
        cin>>y;
        
        xAvg+=x;
        yAvg+=y;

        cops.add({x,y});
    }
    
    xAvg/=size;
    yAvg/=size;

    for (int i = 1; i <= size; i++){
        coords currentCop = cops.get(i);
        smallestDist+= abs(xAvg - currentCop.x);
        smallestDist+= abs(yAvg - currentCop.y);
    }
    
    cout << smallestDist;

    return 0;
} 
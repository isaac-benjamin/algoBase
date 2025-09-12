#include <iostream>
#include "runner.h"

using namespace std;

struct sizeId{
    int size;
    int index;
};

int plantSize;
int containerSize;

sizeId sizeIdOfGreatest(int sizeArray[], int size){
    sizeId greatest = {0,-1};
    for (int i = 0; i < size; i++)
    {
        if (sizeArray[i]>greatest.size){
            greatest.size = sizeArray[i];
            greatest.index = i;
        }
    }
    
    return greatest;
}

void readInArrays(int plants[], int containers[]){

    //Fill plants array
    int count=0;
    do{
        cin>>plants[count];
        count++;
    }while(count<plantSize);

    count=0;
    do{
        cin>>containers[count];
        count++;
    }while(count<containerSize);
}

string findPossible(int plants[], int containers[]){
    do{
        sizeId largestPlant = sizeIdOfGreatest(plants, plantSize);
        sizeId largestContainer = sizeIdOfGreatest(containers, containerSize);

        if( largestPlant.size >= largestContainer.size ){
            return "NO";
        }else{
            //Replace largest container with plants old container
            containers[largestContainer.index]=largestPlant.size;
            //Swap places of largest plant and last item
            plants[largestPlant.index]=plants[plantSize-1];
            //Decrement Plant size
            plantSize--; 
        }
    }while(plantSize>0);
    return "YES";
}

int main(){
    
    //Set array sizes
    cin>> plantSize >> containerSize;
    int plants[plantSize];
    int containers[containerSize];

    readInArrays(plants, containers);
    string possible = findPossible(plants,containers);
    cout<<possible;
    return 0;
}
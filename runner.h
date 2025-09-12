#include <iostream>

using namespace std;


template<typename T>

void printList ( T list[], int size){
    for (int i = 0; i < size; i++)
    {
        cout << list[i] << " ";
    }
    cout<<endl;
}


template<typename X>

void readInArray( X array[], int size){
    int count=0;
    do{
        cin>>array[count];
        count++;
    }while(count<size);
}
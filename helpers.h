#include <iostream>
#include <climits> 
#include <bits/stdc++.h>

using namespace std;

// This array starts at 1 and leaves the 0th index free
template <typename T>
struct Array{
    T* pointer;
    int len; // Amount of objects currently in the array (Not including 0 index)
    int maxSize; // Max allocated size of the arrray  (Not including 0 index)

    Array(int size=0){ //Size is number of open slots after the 0 index
        pointer = new T[size+1];
        len=0;
        maxSize = size;
    }

    int add( T newItem){
        if(len == maxSize){
            return -1;
        }else{
            len++;
            pointer[len] = newItem;
            return len;
        }
    }

    // @brief Adds the contents of the passed array to the current array
    int add( Array<T> otherArray){
        if(len + otherArray.len > maxSize){
            throw out_of_range("The addend array has to many elements to fit within max size");
            return -1;
        }
        for (int i = 1; i <= otherArray.len; i++)
        {
            add(otherArray.get(i));
        }
        return len;
        
    }

    T get (int index){
        if(index >= 0 && index <= len){
            return pointer[index];
        } else {
            throw out_of_range("Invalid range, index must be between 0 and length");
            // return 0; 
        }
    }

    T remove (){
        return pointer[len--];
    }

    void set (int index, T val){
        if (index<=len && index>0){
            pointer[index]=val;
        }else{
            throw out_of_range("Invalid range, index must be between 0 and length");
        }
    }

    void removeAll(){
        len=0;
    }

    void setZeroth (T element){
        pointer[0] = element;
    }

    /*
        Start - inclusive
        end - exclusive
        Runs in O(n) time!
    */
    Array<T> subSet(int start, int end){
        Array<T> miniArray = Array( (end-start)+1 );
        for (int i = 0; i <= miniArray.maxSize; i++)
        {
            miniArray.add(pointer[start+i]);
        }
        return miniArray;
    }

    void print(bool endLines = false){
        cout << "Printing array: "<<endl;
        for(int i=1; i<=len; i++ ){
            cout << pointer[i];
            if( !(endLines || i == len) ){
                cout << ", ";
            }else
            {
                cout << endl;
            }
        }
    }

    ~Array(){
        delete[] pointer;
    }
};

template <typename T>
Array<T> mergeSort (Array<T> given){
    if(given.len==1){
        return given;
    }
    int midpoint = given.len/2;
    Array<T> left = given.subSet(1,midpoint);
    Array<T> right = given.subSet(midpoint+1,given.len);

    Array<T> leftSorted = mergeSort(left);
    Array<T> rightSorted = mergeSort(right);

    return merge(leftSorted, rightSorted);
}

template <typename T>
Array<T> merge(Array<T> left, Array<T> right){
    int leftIndex = 1;
    int rightIndex = 1;
    int mergedIndex = 1;
    Array<T> merged = Array<T>(left.len+right.len);

    while ( mergedIndex <= left.len + right.len){
        //Add if statement for when i or j > len

        //If right array is merged always add left, otherwise check to make sure left is within bounds and smaller than the right
        if( rightIndex > right.len || ( leftIndex <= left.len && left.get(leftIndex) < right.get(rightIndex) )  ){

            merged.add( left.get(leftIndex) );
            leftIndex++;

        }else{

            merged.add( right.get(rightIndex) );
            rightIndex++;

        }
        mergedIndex++;
    }

    return merged;
}

template <typename T>
Array<T> readInArray(){
    int size;
    cin>>size;
    Array<T> input = Array<T>(size);
    T currentRead;
    while (cin>>currentRead){
        input.add(currentRead);
    }
    return input;
}

template <typename T>
Array<T> readInArray( T(*f)(T) ){
    int size;
    cin>>size;
    Array<T> input = Array<T>(size);
    string currentRead; // What type is this??
    while (cin>>currentRead){
        T newAddition = f(currentRead);
        input.add(newAddition);
    }
    return input;
}
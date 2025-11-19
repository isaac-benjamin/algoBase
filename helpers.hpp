#pragma once
#include <iostream>
#include <climits> 
#include <memory>
#include <string>

using namespace std;


// This array starts at 1 and leaves the 0th index free
template <typename T>
struct Array{
    //Change this to be a unique pointer
    unique_ptr<shared_ptr<T>[]> pointer;
    int len; // Amount of objects currently in the array (Not including 0 index)
    int maxSize; // Max allocated size of the arrray  (Not including 0 index)

    Array(int size=0){ //Size is number of open slots after the 0 index
        pointer = make_unique<shared_ptr<T>[]>(size+1);
        len=0;
        maxSize = size;
    }

    /* @brief This constructor takes a  */
    Array(int size, T defaultVal):Array(size){
        for (int i = 0; i < size; i++){
            add(make_shared<T>(defaultVal));
        }
        
    }

    // @brief Copy constructor (take const ref and allocate same capacity as original)
    Array(const Array<T>& original){
        // cout<<"copy constructor "<<original.len<<endl;
        maxSize = original.maxSize;
        pointer = make_unique<shared_ptr<T>[]>(original.maxSize + 1);
        len = original.len;
        for (int i = 1; i <= original.len; i++){
            pointer[i] = original.get(i);
        }
    }

    int add (shared_ptr<T> newItem){
        if(len == maxSize){
            throw out_of_range("The array is at capacity");
        }else{
            len++;
            pointer[len] = newItem;
            return len;
        }
    }

    
    // @brief Adds the contents of the passed array to the current array
    int add(const Array<T>& otherArray){
        if(len + otherArray.len > maxSize){
            throw out_of_range("The addend array has to many elements to fit within max size");
            return -1;
        }
        for (int i = 1; i <= otherArray.len; i++){
            add(otherArray.get(i));
        }
        return len;
        
    }

    /*
    @brief removes the pointer at the index len from the list
    */
    T remove (){
        return pointer[len--];
    }

    void set (int index, shared_ptr<T> val){
        if (index<=len && index>0){
            pointer[index]=val;
        }else{
            throw out_of_range("Invalid range, index must be between 0 and length");
        }
    }

    shared_ptr<T> get (int index) const {
        if(index >= 0 && index <= len){
            return pointer[index];
        } else {
            throw out_of_range("Invalid range, index must be between 0 and length\n Supplied index: "+to_string(index));
        }
    }
    
    void removeAll(){
        len=0;
        pointer = make_unique<shared_ptr<T>[]>(maxSize+1);
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
        Array<T> miniArray(end-start);
        for (int i = 0; i < end-start; i++)
        {
            miniArray.add(pointer[start+i]);
        }
        return miniArray;
    }

    void print(bool endLines = false){
        for(int i=1; i<=len; i++ ){
            cout << *pointer[i];
            if( !(endLines || i == len) ){
                cout << ", ";
            }else{
                cout<<endl;
            }
        }
    }


    //@brief Copy assignment operator 
    Array& operator=(const Array& other){
        if(this!= &other){
            // cout<<"Copy operator";
            maxSize = other.maxSize;
            pointer = make_unique<shared_ptr<T>[]>(other.maxSize+1);
            len = other.len;

            for (int i = 1; i <= len; i++){
                pointer[i]=other.pointer[i];
            }
        }
        return *this;
    }

    //@brief Move constructor -- original array's pointer set to nullptr, len and maxSize = 0
    Array(Array<T>&& other) noexcept{
        pointer = move(other.pointer);
        maxSize = other.maxSize;
        len = other.len;

        other.pointer = nullptr;
        other.len=0;
        other.maxSize=0;
    }

    //@brief Move assignment operator -- original array's pointer set to nullptr, len and maxSize = 0
    Array<T>& operator= (Array<T>&& other) noexcept{
        if(this!= &other){
            pointer = move(other.pointer);
            len= other.len;
            maxSize=other.maxSize;

            other.pointer = nullptr;
            other.maxSize = 0;
            other.len = 0;
        }
        return *this;
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
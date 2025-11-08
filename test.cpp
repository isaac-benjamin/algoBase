#include <iostream>
#include <memory>
#include <string>

#include "helpers.hpp"

using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyz";

char randLetter(){
    return alphabet[rand()%26];
}

void randomlyPopulate(Array<char> &x){
    for (int i = 0; i < x.maxSize; i++)
    {
        x.add(randLetter());
    }
    cout<<"populated"<<endl;
}

Array<char> Skapow(){
    Array<Array<char>> parent (3);
    for (int i = 0; i < 3; i++)
    {
        Array<char> subArray(10) ;
        randomlyPopulate(subArray);
        parent.add(move(subArray));
    }
    return parent.get(1+rand()%3);
}



int main(){
    auto x = Skapow();
    
    cout<<"My printed result: "<< x.get(1) <<endl;
    return 0;
}
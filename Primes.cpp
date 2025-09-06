#include <iostream>

using namespace std;

// For a given n, list all prime numbers ≤ n, in increasing order.


int* listShrinker(int* bigList, int newListSize){
    int* newList = new int[newListSize];
    for (int i=1; i<newListSize;i++){
        newList[i]=bigList[i];
    }
    return bigList;
}

/*
    n= number to be divided
    list = list of primes
    max = amount of primes found
*/

bool divisibleByList (int n, int * list, int max){
    for (int i = 1; i <= max; i++)
    {
        if(n%list[i]==0)
            return true;
    }
    return false;
}

int listSize;
int * getPrimes(int n){
    int count = 0;
    int* primeList= new int[n];
    
    if (n<2){
        return 0;
    }

    for (int i = 2; i <= n; i++)
    {
        if(!divisibleByList(i,primeList,count)){
            primeList[++count]=i;
        }
    }
    
    int* conciseList = listShrinker(primeList, count+1);
    for (int i = 1; i < count+1; i++)
    {
        *(conciseList+i)=primeList[i];
    }
    // delete[] primeList;
    listSize=count;
    return conciseList;
}

int target;

int main() {
    cin>>target;
    int* primes = getPrimes(target);
    for (int i = 1; i <= listSize; i++)
    {
        cout<<primes[i]<<endl;
    }
    return 0;
}

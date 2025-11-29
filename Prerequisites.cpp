#include <iostream>
#include <memory>

#include "AdjacencyList.hpp"

using namespace std;

struct ClassData{
    bool discovered;
    int maxPrereqs;
    

};

typedef AdjVertex<ClassData> ClassVertex; 

int main(){
    int n;
    cin>>n;

    AdjacencyList<ClassData> graph(n,-1,true);

    //Read in
    for (int i = 1; i <= n; i++){
        
    }
    
}
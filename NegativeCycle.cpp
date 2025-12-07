#include <iostream>
#include <memory>
#include <climits>

#include "helpers.hpp"

using namespace std;

//Do belman ford algorithm, if it returns before n-1 cycles - GOTEM
/* 
    Make list of edges
    Belman ford
*/

struct Edge{
    int startVertex;
    int endVertex;
    int weight;
};

int main(){

    bool negativeCycle = false;

    int vertCount, edgeCount;
    cin>>vertCount;
    cin>>edgeCount;
    
    Array<int> minDistances(vertCount,INT32_MAX); //Array that contains the shortest distance to each vertex
    Array< shared_ptr<Edge>> edges(edgeCount); //Array that contains edge info 
    
    //Read in edges
    for (int i = 0; i < edgeCount; i++){
        int start, end, weight;
        cin>>start>>end>>weight;
        Edge x = {start,end,weight};
        edges.add( make_shared<Edge>(x) );
    }

    minDistances.set(1,0); //Set the first vertex to dist 0

    bool changeMade;
    int iterations = 0;

    do{ //continue to update shortest distances as long as changes are still being made and the iteration count is less than the amount of vertices
        changeMade = false;
        iterations++;

        for (int edgeIndex = 1; edgeIndex <= edgeCount; edgeIndex++){
            shared_ptr<Edge> edge = edges.get(edgeIndex);
            int startDist = minDistances.get(edge->startVertex);
            int endDist = minDistances.get(edge->endVertex);
            int edgeWeight = edge->weight;

            if(startDist<INT32_MAX && endDist > startDist+edgeWeight){
                minDistances.set(edge->endVertex, startDist+edgeWeight);
                changeMade=true;
            }
        }        

    }while(changeMade && iterations<=vertCount-1);

    // cout<<"iterations: "<<iterations<<endl;
    // cout<<"changeMade: "<<changeMade<<endl;
    
    if(changeMade && iterations>=vertCount){
        negativeCycle = true;
    }

    if(negativeCycle){
        cout<<"YES";
    }else{
        cout<<"NO";
    }

    return 0;
}
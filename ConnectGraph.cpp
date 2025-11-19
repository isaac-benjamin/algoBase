#include <iostream>
// #include "helpers.hpp"
// #include "graphClasses.hpp"
#include "AdjacencyList.hpp"

using namespace std;

AdjacencyList graph = AdjacencyList(0,0);
Array<bool> foundVertices;

void findConnectedComponent(shared_ptr<Vertex> startVertex){
    Array<Vertex> queue(graph.n);
    queue.add(startVertex);
    int head = 1; 
    int total = 1;

    while(total>0){

        //Get the next vertex and add its neighbors to the queue
        shared_ptr<Vertex> nextVert = queue.get(head);
        Array<Vertex> nextNeighbors = nextVert->getNeighbors();
        foundVertices.set(nextVert->id,make_shared<bool>(true));
        total--;
        for (int i = 1; i <= nextNeighbors.len; i++){

            shared_ptr<Vertex> neighbor = nextNeighbors.get(i);

            //If the neighbor has not been added already, mark it as found then increase total
            if(! *foundVertices.get(neighbor->id)){
                foundVertices.set(neighbor->id, make_shared<bool>(true));
                queue.add(neighbor); 
                total++;
            }
        }
        head++;
    }

}

int main(){
    int roadsNeeded = -1;

    int n,m;
    cin>>n>>m;
    graph = AdjacencyList(n,m);
    graph.readIn();
    // graph.print();
    // cout<<endl;
    foundVertices=Array<bool>(n);
    for (int i = 0; i < n; i++){
        foundVertices.add(make_shared<bool>(false));
    }

    for (int i = 1; i <= n; i++){
        if(!*foundVertices.get(i)){
            // cout<<i<<endl;
            roadsNeeded++;
            findConnectedComponent(graph.vertices.get(i));
            // foundVertices.print();
        }
    }
    cout<<roadsNeeded;

    return 0;
}
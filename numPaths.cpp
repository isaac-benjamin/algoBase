#include <iostream>
#include <memory>
#include <climits>

#include "LinkedList.hpp"
#include "AdjacencyList.hpp"

using namespace std;

struct DFS_Vertex{
    shared_ptr<Vertex> vertex;
    int depth;

    // DFS_Vertex(shared_ptr<Vertex> vertex, int depth):vertex(vertex), depth(depth){
        
    // }
};

int findMinPaths(AdjacencyList * graph, int startIndex, int endIndex){
    shared_ptr<Vertex> start = graph->get(startIndex);
    shared_ptr<Vertex> end = graph->get(endIndex);
    Array<bool> visited(graph->n,false);

    //DFS
    LinkedList<DFS_Vertex> queue({start,0});
    int finalDepthToCheck=INT_MAX;
    int paths = 0;

    //If the next node you are inspecting was discovered at the same depth as the goal stop searching 
    while( finalDepthToCheck < queue.head->getInfo()->depth ){
        shared_ptr<DFS_Vertex> head = queue.pop()->getInfo();
        Array<Vertex> neighbors = head->vertex->getNeighbors();
        int headDepth = head->depth;

        for (int i = 1; i <= neighbors.len; i++){
            shared_ptr<Vertex> vert = neighbors.get(i);
            auto seen = visited.get(i);
            if(!seen){
                queue.tailAdd( {vert,headDepth+1} );
                *seen = true;
            }
            if(vert==end){
                finalDepthToCheck=headDepth;
                paths++;
            }
            
        }
        
    }

    return paths;
    
}

int main(){ 

    int n,m;
    cin>>n,m;

    int s,t;
    cin>>s,t;

    AdjacencyList graph (n,m);
    graph.readIn();

    int paths = findMinPaths( &graph, s,t);

    return 0;
}
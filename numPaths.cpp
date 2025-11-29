#include <iostream>
#include <memory>
#include <climits>

#include "LinkedList.hpp"
#include "AdjacencyList.hpp"

using namespace std;

struct Depth_Info{
    int depth=0;
    int pathsTo=0;

    void addPaths(int morePaths){
        pathsTo+=morePaths;
    }

    void setDepth(int depth){
        this->depth=depth;
    }

};

int findMinPaths(AdjacencyList * graph, int startIndex, int endIndex){
    shared_ptr<Vertex> start = graph->get(startIndex);
    shared_ptr<Vertex> end = graph->get(endIndex);
    bool * visited = new bool[graph->n];
    for (int i = 0; i < graph->n; i++){
        visited[i] = false;
    }
    visited[startIndex-1]=true;

    Array<Depth_Info> depthArray = Array<Depth_Info>(graph->n, {0,1});
    
    //DFS
    LinkedList<Vertex> queue(start);
    int paths = 0;
    int depthBeforeEnd=INT_MAX;
    int lowestDepth = 0;
    
    //If the next node you are inspecting was discovered at the same depth as the goal stop searching 
    while( lowestDepth <= depthBeforeEnd && !queue.isEmpty()){
        
        shared_ptr<Vertex> head = queue.pop()->getInfo();
        Array<Vertex> neighbors = head->getNeighbors();

        shared_ptr<Depth_Info> headDepthInfo = depthArray.get(head->id);
        lowestDepth = headDepthInfo->depth;

        for (int i = 1; i <= neighbors.len; i++){
            shared_ptr<Vertex> vert = neighbors.get(i);

            int id = vert->id; //ID of the neighbor
            shared_ptr<Depth_Info> depthStats = depthArray.get(id);
            
            if(!visited[id-1]){
                queue.tailAdd(vert);
                visited[id-1]=true; 
                depthStats->depth = headDepthInfo->depth + 1;
                depthStats->pathsTo = headDepthInfo->pathsTo;
                
                if(id==endIndex){
                    depthBeforeEnd = headDepthInfo->depth;
                }

            }else if( depthStats->depth == headDepthInfo->depth+1){
                depthStats->addPaths(headDepthInfo->pathsTo);
            }
            
        }
        
    }

    delete[] visited;
    return depthArray.get(endIndex)->pathsTo;
    
}

int main(){ 
    
    int n,m;
    cin>>n>>m;

    
    int s,t;
    cin>>s>>t;

    AdjacencyList * graph = new AdjacencyList(n,m);
    graph->readIn();

    // graph->print();
    
    int paths = findMinPaths(graph, s,t);
    cout<<paths;

    delete graph;
 
    return 0;
}
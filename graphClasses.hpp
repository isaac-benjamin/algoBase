#pragma once
#include <memory>

#include "helpers.hpp"

using namespace std;

struct Vertex{
    int id;

    Vertex(int idNum){
        id = idNum;
    }

    virtual Array<Vertex> getNeighbors(){return Array<Vertex>();};
};

// struct Edge{
//     Vertex v1;
//     Vertex v2;
//     int weight;
// };

struct Graph{
    int n; //number of vertices
    int m; //number of edges

    Graph(int verts, int edges){
        n=verts;
        m=edges;
    }
};
#pragma once
#include <memory>

#include "helpers.hpp"

using namespace std;

template <typename T, typename V = shared_ptr<T>>
struct Vertex{
    int id;
    V info; //Problem specific content

    Vertex(int idNum){
        id = idNum;
    }

    Vertex(int idNum, V info){
        id = idNum;
        this->info = info;
    }

    virtual shared_ptr<Array<Vertex>> getNeighbors(){};
    virtual void addNeighbor(shared_ptr<Vertex> vert){};
    virtual void printNeighbors(){};

    void setInfo(V info){
        this->info = info;
    }

    V getInfo(){
        return info;
    }

};

struct Graph{
    int n; //number of vertices
    int m; //number of edges
    bool directed;

    Graph(int verts, int edges, bool directed=false){
        n=verts;
        m=edges;
    }
};
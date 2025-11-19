#pragma once
#include <memory>

#include "graphClasses.hpp"

using namespace std;

struct AdjVertex: public Vertex{
    Array<Vertex> neighbors;

    AdjVertex(int idNum, int n): Vertex(idNum){
        neighbors= Array<Vertex>(n);
    }

    Array<Vertex> getNeighbors() override{
        return neighbors;
    }

    void addNeighbor(shared_ptr<Vertex> vert){
        neighbors.add(vert);
    }

    void printNeighbors(){
        for (int i = 1; i <=neighbors.len; i++){
            cout<<neighbors.get(i)->id;
            if(i<neighbors.len){
                cout<<", ";
            }
        }
        
    }
};

struct AdjacencyList: public Graph{
    
    Array<AdjVertex> vertices;

    AdjacencyList(int n, int m):Graph(n,m){
        vertices = Array<AdjVertex>(n);
        for (int i = 1; i <= n; i++){
            shared_ptr<AdjVertex> x = make_shared<AdjVertex>( AdjVertex(i,n) );
            vertices.add(x);
        }
    
    }

    shared_ptr<Vertex> get(int index){
        return vertices.get(index);
    }

    void readIn(){
        int selfLoop = 0;
        for (int i = 0; i <m; i++){
            int v1, v2;
            cin>>v1;
            cin>>v2;
            if(v1 == v2){
                selfLoop++;
                continue;
            }
            shared_ptr<AdjVertex> vert1 = vertices.get(v1);
            shared_ptr<AdjVertex> vert2 = vertices.get(v2);
            vert1->addNeighbor(vert2);
            vert2->addNeighbor(vert1);
        }
        m-=selfLoop;
    }

    void print(){
        for (int i = 1; i <= n; i++){
            shared_ptr<AdjVertex> x = vertices.get(i);
            cout<<x->id<<": ";
            x->printNeighbors();
            cout<<endl;
        }
    }

};
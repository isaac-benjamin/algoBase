#pragma once
#include <memory>
#include <iostream>

#include "graphClasses.hpp"

using namespace std;

template<typename T, typename V=shared_ptr<T>>
struct AdjVertex: public Vertex<T, V>{
    Array<AdjVertex> neighbors;

    AdjVertex(int idNum, int n, V info = nullptr): Vertex<T,V>(idNum, info){
        neighbors= Array<AdjVertex>(n);
    }
    

    shared_ptr<Array<Vertex>> getNeighbors(){
        shared_ptr<Array<Vertex>> x = make_shared<Array<Vertex>>(neighbors);
        return x;
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

template <typename Info, typename T = AdjVertex<Info>> 
struct AdjacencyList: public Graph{
    
    Array<T> vertices;

    AdjacencyList(int n, int m, bool directed=false):Graph(n,m,directed){
        vertices = Array<T>(n);
        for (int i = 1; i <= n; i++){
            shared_ptr<T> x = make_shared<T>( T(i,n) );
            vertices.add(x);
        }
    }

    shared_ptr<T> get(int index){
        return vertices.get(index);
    }

    void readIn(string lineEnd){
        int selfLoop = 0;
        for (int i = 0; i <m; i++){
            int v1, v2;
            cin>>v1;
            cin>>v2;
            if(v1 == v2){
                selfLoop++;
                continue;
            }
            shared_ptr<T> vert1 = vertices.get(v1);
            shared_ptr<T> vert2 = vertices.get(v2);
            vert1->addNeighbor(vert2);
            if(!directed){
                vert2->addNeighbor(vert1);}
        }
        m-=selfLoop;
    }

    void print(){
        for (int i = 1; i <= n; i++){
            shared_ptr<T> x = vertices.get(i);
            cout<<x->id<<": ";
            x->printNeighbors();
            cout<<endl;
        }
    }

};
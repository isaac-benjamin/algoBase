#pragma once 
#include <memory>
#include <iostream>

using namespace std;

template <typename T>
struct Node{
    shared_ptr<Node> next =nullptr;
    shared_ptr<Node> prev =nullptr;
    shared_ptr<T> info;

    /*
    @brief This constructor takes a raw T value and optionally the previous node
    */
    Node(T content, shared_ptr<Node> prevNode =nullptr ){
        info = make_shared<T>(content);
        prev= prevNode;
    }

    shared_ptr<T> getInfo(){
        return info;
    }

    void setNext( shared_ptr<Node> nextNode){
        next=nextNode;        
    }

    void setPrev(shared_ptr<Node> prevNode){
        // if(prevNode==nullptr){
            
        // }
        prev=prevNode;
    }

    void nullPrev(){
        prev=nullptr;
    }

    void nullNext(){
        next=nullptr;
    }

    void insertBehind(shared_ptr<Node> nodeAhead){
        auto thisPtr = make_shared<Node>(this);
        if(nodeAhead->prev){
            setPrev(nodeAhead->prev);
            nodeAhead->setPrev(thisPtr);
        }
        setNext(nodeAhead);
    }

    void insertAheadOf(shared_ptr<Node> nodeBehind){
        auto thisPtr =  make_shared<Node>(this);
        if(nodeBehind->next){
            setNext(nodeBehind->next);
            nodeBehind->setNext(thisPtr);
        }
        setPrev(nodeBehind);
    }

};

template <typename T>
struct LinkedList{
    shared_ptr<Node<T>> head=nullptr;
    shared_ptr<Node<T>> tail=nullptr;

    /* 
    @brief This constructor takes a raw T value, used to create the head
    */
    LinkedList(T firstItem){
        shared_ptr<Node<T>> head = make_shared<Node<T>>(firstItem);
        tail = head;
    } 

    void headAdd(shared_ptr<Node<T>> newHead){
        head->setPrev(newHead);
        newHead->setNext(head);
        head=newHead;
    }

    void headAdd(shared_ptr<T>newItem){
        shared_ptr<Node<T>> node = make_shared<Node<T>>(newItem);
        headAdd(node);
    }

    void tailAdd(shared_ptr<Node<T>> newTail){
        tail->setNext(newTail);
        newTail->setPrev(tail);
        tail=newTail;
    }

    /*
    @brief Takes a raw T value and converts it to a shared pointer to a node, then appneds it to the list
    */
    void tailAdd(T newItem){
        shared_ptr<Node<T>> node = make_shared<Node<T>>(newItem);
        tailAdd(node);
    }

    shared_ptr<Node<T>> pop(int index=1){
        shared_ptr<Node<T>> selectedNode = head;

        for (int i = 1; i < index; i++){
            if(selectedNode->next){
                selectedNode = selectedNode->next;
            }else{
                throw out_of_range("Indexed beyond tail!\nSupplied index: "+to_string(index));
            }
        }

        if(selectedNode==tail){
            return popTail();
        }

        if(selectedNode!=head){
            auto previous = selectedNode->prev;
            auto nextNode = selectedNode->next;
            previous->setNext(nextNode);
            nextNode->setPrev(previous);
        }else{
            head=head->next;
            if(head){
                head->nullPrev();
            }
        }

        return selectedNode;
                
    }

    /*
    @brief Removes the last node
    */
    shared_ptr<Node<T>> popTail(){
        auto x = tail;
        tail = tail->prev;
        tail->nullNext();
        return x;
    }
};
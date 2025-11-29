#pragma once 
#include <memory>
#include <iostream>

using namespace std;

template <typename T>
struct Node{
    shared_ptr<Node> next =nullptr;
    shared_ptr<Node> prev;
    shared_ptr<T> info;

    /*
    @brief This constructor takes a raw T value and optionally the previous node
    */
    Node(T content, shared_ptr<Node> prevNode =nullptr ){
        info = make_shared<T>(content);
        prev= prevNode;
    }

    /* @brief This constructor takes a shared pointer of type T and optionally the previous node */
    Node(shared_ptr<T> info, shared_ptr<Node> prevNode=nullptr){
        this->info = info;
        prev = prevNode;
    }

    shared_ptr<T> getInfo(){
        return info;
    }

    void setInfo(T newInfo){
        info=make_shared<T>(newInfo);
    }

    void setNext( shared_ptr<Node> nextNode){
        next=nextNode;        
    }

    void setPrev(shared_ptr<Node> prevNode){
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
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;

    /* 
    @brief This constructor takes a raw T value, used to create the head
    */
    LinkedList(T firstItem){
        head = make_shared<Node<T>>(firstItem);
        tail = head;
    } 
 
    /* @brief This constructor takes a shared pointer of type T used to create the head */
    LinkedList (shared_ptr<T> firstItem){
        head = make_shared<Node<T>>(firstItem);
        tail = head;
    }

    bool isEmpty(){
        return head==nullptr;
    }

    void headAdd(shared_ptr<Node<T>> newHead){
        if(tail==nullptr){ //If the list was empty before, head = tail
            tail=newHead;
        }else{
            head->setPrev(newHead);
            newHead->setNext(head);
        }
        head=newHead;
    }

    void headAdd(shared_ptr<T>newItem){
        shared_ptr<Node<T>> node = make_shared<Node<T>>(newItem);
        headAdd(node);
    }

    /* @brief Takes a shared pointer of Node type T then appends it to the back*/
    void tailAdd(shared_ptr<Node<T>> newTail){
        if(head==nullptr){ //If the list was empty before, head = tail
            head=newTail;
            // cout<<"Head replaced"<<endl;
        }else{
            tail->setNext(newTail);
            newTail->setPrev(tail);
        }
        tail=newTail;
        // cout<<"Vertex "<<newTail->getInfo()->id<<" added to queue"<<endl;
    }

    /*
    @brief Takes a raw T value and converts it to a shared pointer to a node, then appneds it to the list
    */
    void tailAdd(T newItem){
        shared_ptr<Node<T>> node = make_shared<Node<T>>(newItem);
        tailAdd(node);
    }

    /* 
    @brief Tail add that takes a pointer of the linked list type
    */
   void tailAdd(shared_ptr<T> newItem){
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
        } //If it is not the first node pop like normal
        else if (selectedNode!=head){ 
            auto previous = selectedNode->prev;
            auto nextNode = selectedNode->next;
            previous->setNext(nextNode);
            nextNode->setPrev(previous);
        }//If it is the head, do not bother with left half
        else{
            head=head->next;
            head->nullPrev();
            //(guaranteed head and taj)
        }

        return selectedNode;
                
    }

    /*
    @brief Removes the last node
    */
    shared_ptr<Node<T>> popTail(){
        auto x = tail;
        tail = tail->prev;
        if(tail){ //If there are elements left null next
            tail->nullNext();
        }else{ //otherwise both head and tail are null
            head = nullptr;
        }
        return x;
    }
};
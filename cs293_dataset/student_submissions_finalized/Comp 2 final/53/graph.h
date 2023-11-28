#include<iostream>
using namespace std;
#include "std_headers.h"

template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

class Node{
public:
    int value;
    listOfObjects<Node *> *incoming_adj;
    listOfObjects<Node *> *tail_incoming_adj;
    listOfObjects<Node *> *outgoing_adj;
    listOfObjects<Node *> *tail_outgoing_adj;
    Node(){
        incoming_adj = nullptr;
        tail_incoming_adj = nullptr;
        outgoing_adj = nullptr;
        tail_outgoing_adj = nullptr;
    }
    Node(int value){
        this->value = value;
        incoming_adj = nullptr;
        tail_incoming_adj = nullptr;
        outgoing_adj = nullptr;
        tail_outgoing_adj = nullptr;
    }
};

class Graph{
    int numNodes,numEdges;
    Node* nodes;

public:

    Graph(int numNodes){
        this->numNodes = numNodes;
        nodes = new Node[numNodes];
        for(int i=0;i<numNodes;i++){
            nodes[i].value = i+1;
        }
        while(true){
            int x,y;
            cin >> x >> y;
            if(x == -1 || y == -1) break;
            else{
                listOfObjects<Node *> new_list_object(&nodes[y-1]);
                listOfObjects<Node *> new_list_object2(&nodes[x-1]);
                if(nodes[x-1].outgoing_adj==nullptr){
                    nodes[x-1].outgoing_adj = &new_list_object;
                    nodes[x-1].tail_outgoing_adj = &new_list_object;
                }
                else{
                    nodes[x-1].tail_outgoing_adj->next = &new_list_object;
                    new_list_object.prev = nodes[x-1].tail_outgoing_adj;
                    nodes[x-1].tail_outgoing_adj = nodes[x-1].tail_outgoing_adj->next;
                }
                if(nodes[y-1].incoming_adj==nullptr){
                    nodes[y-1].incoming_adj = &new_list_object2;
                    nodes[y-1].tail_incoming_adj = &new_list_object2;
                }
                else{
                    nodes[y-1].tail_incoming_adj->next = &new_list_object2;
                    new_list_object2.prev = nodes[y-1].tail_incoming_adj;
                    nodes[y-1].tail_incoming_adj = nodes[y-1].tail_incoming_adj->next;
                }
            }
        }
    }
    void print_sources();
};


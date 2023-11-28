#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


template <typename T>
class listStruct{ //struct for a list
public:
  T value;
  listStruct* next;
  listStruct* prev;
  listStruct(T value){this->value = value; next = nullptr; prev = nullptr;}
};

template <typename T>
class list{ //linked list with stack like functionality
public:
  listStruct<T> * root;
  list(){
    root = nullptr;
  }
  list(int val){
    root = new listStruct<T>(val);
  }
  void push_front(T val){ //pushes the element to the front of the list
    if(root!=nullptr){
      listStruct<T> * element = new listStruct<T>(val);
      listStruct<T> * presentFirst = root; //could be null
      root = element;
      element->next = presentFirst; //could be null
      if(presentFirst!=nullptr) presentFirst->prev = element;
    }
    else root = new listStruct<T>(val);
    // cout << "pushed : " << val << "at: " << root << endl;
  }

  bool Exists(T val){ //if the edge already exists in the list it will return true
    listStruct<T> * itr = root;
    while(itr!=nullptr){
      if(itr->value == val) return true;
      itr = itr->next;
    }
    return false;
  }

  void pop(int val){
    if(this->Exists(val)){
      listStruct<T> * i = this->root;
      listStruct<T> * p = nullptr;
      if(i->value==val){
        if(i->next==nullptr) root = nullptr;
        else {root = i->next; i->prev = nullptr;}
      }
      else{
        for(listStruct<int> *j = this->root; j!=nullptr; j=j->next){
          if(j->value == val){
            if(j->next!=nullptr)j->next->prev = p;
            p->next = j;
          }
          p = j;
        }
      }
    }
  }

  int count(){
    listStruct<T> * i = root;
    int counter = 0;
    while(i!=nullptr){
      counter++;
      i = i->next;
    }
    return counter;
  }

};

class Node {
 public:
  int value;

  //start//

  list<int> *OutgoingEdges; //list of outgoing edges
  list<int> *IncomingEdges; //list of incoming edges
  list<int> *SimilarNodes; //list of similar nodes
  list<int> * AdjacencyList; //adjacency list for collapse
  list<int> * NewOutGoing; //new graph after collapse
  bool visited;
  Node(){visited = false; OutgoingEdges = new list<int>(); IncomingEdges = new list<int>(); SimilarNodes = new list<int>(); AdjacencyList = new list<int>(); NewOutGoing = new list<int>();}

  bool sourceNode(){
    if(this->IncomingEdges->root==nullptr) return true;
    else return false;
  }

  bool similarNodes(int val){
    for(listStruct<int> *i = this->SimilarNodes->root; i!=nullptr; i=i->next){
      if(i->value == val) return true;
    }
    return false;
  }
  //end//

  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  // int numEdges;
  // fstream graphFile;
  list<int> * maxValues;
  Node *nodes;
  Node *newNodes;
  // Add appropriate fields as necessary for your implementation
  
  list<int> * Stack;
  
  int connectedComponents;
  
  bool newNode;

 public:
  Graph(){

  }
  Graph(int nNodes) {
    
    connectedComponents = 0;
    Stack = new list<int>();
    maxValues = new list<int>();
    // backtrack = false;

    numNodes = nNodes;
    nodes = new Node[nNodes];
    
    for (int i = 0; i < nNodes; i++) {
      nodes[i].value = i+1;
    }

    int n1, n2;
     
    while(true){
      cin >> n1;
      cin >> n2;
      if(n1 == -1) break;

      if(nodes[n1-1].OutgoingEdges->Exists(n2)) continue;
      //   // if(!nodes[n2].adjacencyList->Exists(n1))
      if(nodes[n2-1].OutgoingEdges->Exists(n1)) continue;
      // if(nodes[n2-1].IncomingEdges->Exists(n1)) continue ; --> not required
      nodes[n1-1].OutgoingEdges->push_front(n2);
      nodes[n2-1].IncomingEdges->push_front(n1);
    }

    while(true){
      cin >> n1;
      cin >> n2;
      if(n1==-1) break;
      if(!nodes[n1-1].sourceNode() || !nodes[n2-1].sourceNode()) continue;
      if(nodes[n1-1].SimilarNodes->Exists(n2)) continue;
      // if(nodes[n2-1].SimilarNodes->Exists(n1)) continue; --> not required
      nodes[n1-1].SimilarNodes->push_front(n2);
    }

    //marking the similar nodes.
    for(int i = 0; i < nNodes; i++){
      listStruct<int> * j = nodes[i].IncomingEdges->root;
      if(j!=nullptr && j->next==nullptr){
        nodes[i].SimilarNodes->push_front(j->value);
      }
    }

     for(int i = 0; i < nNodes; i++){
  
       listStruct<int> *j = nodes[i].SimilarNodes->root;
       while(j!=nullptr){
  
         j = j->next;
       }

     }
  }
      
  ~Graph() {

    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  // void modifiedDFS();
  // void myDFS(int i);
  void dfs(int i, int * max);
  void dfs2(int i, int max);
  int findSimilar(int v1, int v2);
  void printResults();
};

#endif


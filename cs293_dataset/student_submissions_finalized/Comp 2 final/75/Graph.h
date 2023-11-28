#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif



#include <time.h>
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

template <typename T> class myList{
  public:
  listOfObjects<T> * journeys;// HEAD of the linked list
  listOfObjects<T> * tail; // TAIL of the linked list
  int size;

  myList(){
    journeys = nullptr; tail = nullptr; size = 0;
  }
  void add(T num){
    listOfObjects<T>* toAdd = new listOfObjects<T>(num);
    if(tail!=nullptr){// non-empty queue
      tail->next = toAdd;
      toAdd->prev = tail;
      tail = tail->next;
    }
    else{// empty queue
      journeys = toAdd;
      tail = toAdd;
    }
    // increase the size of vector by 1
    size++;
  }
  
  bool find(T num){ // do not use find for other than T = int 
    listOfObjects<T> * iterator = journeys;
    bool found = false;
    while(iterator!=nullptr){
      if (iterator->object == num){
        found = true;
        break;
      }
      iterator = iterator->next;
    }

    return found;
  }
  void print(){
    listOfObjects<T> * iterator = journeys;
    int i = 0;
    while(iterator!=nullptr){
      cout<<"Connected Component: "<<(i+1)<<endl;
      iterator->object->printBST("", false);
      cout<<"-------------------------------------------------------------------------"<<endl;
      iterator = iterator->next; 
      i++;
    }
  }
};

struct TreeNode{
  int value;
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root
  
  TreeNode() : value(0), left(nullptr), right(nullptr) {}
  
  TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
  
  TreeNode(int value, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : value(value), left(leftChild), right(rightChild), parent(parent) {}
};

class Node {
 public:
  int value;
  Node* next;
  Node* list;
  myList<int> backtrack;

  Node(int i){
    value = i;
    next = nullptr;
    list = nullptr;
  }
  Node(){
    value = 0;
    next = nullptr;
    list = nullptr;
  }

  // insert other fields and methods as appropriate
};

class Graph {
  public:
  int numNodes;
  int numSource;
  int numEdges;
  fstream graphFile;
  Node *nodes;
  int* inEdges;
  int* outEdges;
  myList<int>* parents;
  bool *visited;
  int index;
  int* maxDistance;
  bool* visitedDFS;
  int numComponents;
  int* compNum;

  
 public:
  Graph(int nNodes); // constructor for the class Graph
  bool insert(int n1, int n2); // to insert new directed edges into the graph from n1 to n2
  bool find(int n1, int n2);
  void printGraph();
  void topologicalSort(int sourceArray[]);
  void recTopological(int v, int stack[]);
  void DFS();
  void recDFS(int v);// v is the index of the vertex on whih DFS is done

  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
  }

};

#endif

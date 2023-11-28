#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template <typename T> class listOfObjects {
  public:
  T object;
  listOfObjects<T> *next;
  listOfObjects(T initValue) {object = initValue; next =nullptr;}
  listOfObjects(){}
  ~listOfObjects() {;}
};

class IntNode{
  public:
  int value;
  IntNode* left;
  IntNode* right;
  IntNode* parent;
  IntNode(int value){
    this->value=value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
};

class BST {
  private:
  IntNode* root;
  public:
  BST(){
    root=nullptr;
  }
  bool insert(int value);
  void printBST(const string& prefix, bool isLeft=false);
};

class dir_node{
  public:
  int value;
  bool direction;
  dir_node(int value, bool direction){
    this->value=value;
    this->direction=direction;
  }
};
class Node {
 public:
  int value;
  listOfObjects<dir_node*>* adj;
  Node(){}
  Node(int value){
    this->value=value;
  }
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node* nodes;
  int connected_components;
  int visited_once;
  int visited_twice;
  int cycle_nodes;
  listOfObjects<BST>* bst_trees;
  int start_vertex;
  // Add appropriate fields as necessary for your implementation
  
  public:
  bool** visited;
  int** visited_values;
  Graph(int nNodes, int nEdges, string gFileName) {
    connected_components=0;
    start_vertex=0;
    bst_trees=nullptr;
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;
    visited=new bool*[numNodes];
    for(int i=0; i<numNodes; i++){
      visited[i]=new bool[2];
      for (int j=0; j<2; j++){
        visited[i][j]=false;
      }
    }
    visited_values=new int*[numNodes];
    for(int i=0; i<numNodes; i++){
      visited_values[i]=new int[2];
      for (int j=0; j<2; j++){
        visited_values[i][j]=-1;
      }
    }
    nodes = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
        do {
            n1 = rand() % numNodes;
            n2 = rand() % numNodes;
        } 
        while (n1 == n2);

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
        int incremented=0;
        for(int i=0; i<numNodes; i++){
          if(nodes[i].value==n1+1){
            int found=0;
            listOfObjects<dir_node*>* a=nodes[i].adj;
            while(a!=nullptr){
              if(a->object->value==n2+1){
                found=1;
              }
              a=a->next;
            }
            if(found==0){
              a=nodes[i].adj;
              if(a==nullptr){
                nodes[i].adj=new listOfObjects<dir_node*>(new dir_node(n2+1,true));
                if(incremented==0){
                  incremented=1;
                  countEdges++;
                  graphFile << n1+1 << " " << n2+1 << endl;
                }
              }
              else{
                while(a->next!=nullptr){
                  a=a->next;
                }
                a->next=new listOfObjects<dir_node*>(new dir_node(n2+1,true));
                if(incremented==0){
                  incremented=1;
                  countEdges++;
                  graphFile << n1+1 << " " << n2+1 << endl;
                }
              }
            }
          }
          if(nodes[i].value==n2+1){
            int found=0;
            listOfObjects<dir_node*>* a=nodes[i].adj;
            while(a!=nullptr){
              if(a->object->value==n1+1){
                found=1;
              }
              a=a->next;
            }
            if(found==0){
              a=nodes[i].adj;
              if(a==nullptr){
                nodes[i].adj=new listOfObjects<dir_node*>(new dir_node(n1+1,true));
                if(incremented==0){
                  incremented=1;
                  countEdges++;
                  graphFile << n1+1 << " " << n2+1 << endl;
                }
              }
              else{
                while(a->next!=nullptr){
                  a=a->next;
                }
                a->next=new listOfObjects<dir_node*>(new dir_node(n1+1,true));
                if(incremented==0){
                  incremented=1;
                  countEdges++;
                  graphFile << n1+1 << " " << n2+1 << endl;
                }
              }
            }
          }
        }
    }
    //Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  void modifiedDFS();
  bool modifiedDFS1(int n,BST& bst_tree,int prev_node);
  void printResults();
};

#endif

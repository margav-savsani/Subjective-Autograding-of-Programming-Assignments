#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif


class Node {
 public:
  int value;
  bool* incoming;
  bool* outgoing;
  bool* userSimilar;
  bool* similar;
  // insert other fields and methods as appropriate
  Node(){}
  Node(int value){
    this->value=value;
  }
  bool isSource(int numNodes);
};

class Graph {
  int numNodes;
  fstream graphFile;
  Node *nodes;
  int* collapsed;
  int* collapsedNodes;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int numNodes) {

    this->numNodes = numNodes;
    
    nodes = new Node[numNodes];
    collapsed=new int[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
      nodes[i].incoming=new bool[numNodes];
      nodes[i].outgoing=new bool[numNodes];
      nodes[i].userSimilar=new bool[numNodes];
      nodes[i].similar=new bool[numNodes];
      for(int j=0; j<numNodes; j++){
        nodes[i].incoming[j]=false;
        nodes[i].outgoing[j]=false;
        nodes[i].userSimilar[j]=false;
        nodes[i].similar[j]=false;
      }
    }
    
    int n1, n2;
    while(cin>>n1){
        cin>>n2;
        if(n1==-1 && n2==-1) break;
        nodes[n1-1].outgoing[n2-1]=true;
        nodes[n2-1].incoming[n1-1]=true;
    }
    while(cin>>n1){
        cin>>n2;
        if(n1==-1 && n2==-1) break;
        nodes[n1-1].userSimilar[n2-1]=true;
    }
    
    // Add appropriate code as necessary for your implementation
  }
      
  ~Graph() {
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation

  bool isSimilar(int n1,int n2);
  bool isConnected(int n1, int n2);
  void printResults();
};

#endif

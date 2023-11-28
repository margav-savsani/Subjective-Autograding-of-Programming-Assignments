#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

class Node {
 public:
  int value;
  int *incoming;
  // constructor
  Node(){
    value = -1;
    incoming = new int[50];
    for (int i = 0; i < 50; i++) {
      incoming[i] = -1;
    }   
  }
};

class Graph {
  int numNodes;
  int *left;
  int *right;
  Node *nodes;
  ofstream graphone;
  
 public:
  //constructor
  Graph(){

    graphone.open("outgraph.txt");
    cin>>numNodes;

    left = new int[30];
    right = new int[30];
    nodes = new Node[numNodes];
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }

    for (int i = 0; i < 30; i++) {
      left[i] = -1;
      right[i] = -1;
    }
    
    while(true){
      int n1;
      cin>>n1;
      int n2;
      cin>>n2;
      if(n2 == -1) break;
      int a = 0;
      while(nodes[n2-1].incoming[a] > -1){
        a++;
      }
      nodes[n2-1].incoming[a] = n1;
    }
  }
      
  ~Graph() {
    /*if (graphFile.is_open()) {
      graphFile.close();
    }*/
    delete[] nodes;
  }

  bool similar(int a , int b);
  void similar_nodes();
  void printResults();
};

#endif
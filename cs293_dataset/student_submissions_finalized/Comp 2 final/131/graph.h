//#ifndef GRAPH_BST_H
//#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <vector>
#endif

class adjacent  {  // for storing the adjacency list of nodes of any form
 public:
  int value; 
  adjacent *next; // next in list 
  adjacent *prev;// not needed in this question though
  
  // Constructor
  adjacent (int initValue) {value = initValue; next = prev = nullptr;}
  adjacent (){value = -2; next = prev = nullptr;}
  // Destructor
  ~adjacent() { ;}
};
class Node {  // these are the nodes of the graph
 public:
  int value;
  adjacent* toadjacencylist; // outgoing edges 
  adjacent* fromadjacencylist;// incoming edges 
  bool  *similarlist = new bool  [100]; // make sure any test case has less than 100 nodes or precisely less than 100 similar nodes 
  Node (){toadjacencylist = nullptr;fromadjacencylist = nullptr;  // otherwise change this value of 100 accordingly
   for (int i=0;i<100; i++){
        similarlist[i]= false;}
  }
};

class Graph {
  int numNodes;
  int numEdges;
  bool* sourceyes;
  Node *nodes; // contains all nodes of the graph
  public: // indexing starts from 1 
  Graph(int nNodes , Node *nodeslist, bool* sourcenode ) {
    numNodes = nNodes; // constructor of graph
    nodes=nodeslist;
    sourceyes = sourcenode ;}
    void findsimilar(); // finding similar set of nodes 
    void  DFS(int vertex,int  * maxcomp, int count , int & maximum); // dfs search to find connected components
    void printResults(); // printing similar nodes  and  collapsed graph 
};
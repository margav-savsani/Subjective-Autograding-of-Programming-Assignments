#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class List{
  public:
  T value; //value of node
  List *next;

  List(T node){
    value = node;
    next = nullptr;
  }
};

class Node
{
public:
  int value;
  List<Node> *toadj; //adjacency list- nodes to which edge from this node exist
  List<Node> *fromadj; //adjacency list- nodes from which edge to this node exist
  int to_degree; //number of elements in toadj list
  int from_degree; //number of elements in fromadj list
  bool source; //whether it is source node or not, i.e. fromadj is nullptr
  List<Node> *similar; //stores similar nodes
  int num_similar;
  int rep; //denotes the representation
};

class Graph
{
public:
  int numNodes;
  fstream graphFile;
  Node *nodes;
  int *visited;
  int t; //stores the number of sources in the collapsed graph
  int *coll_sources; //stores indices of sources in collapsed graph
  // Add appropriate fields as necessary for your implementation

  Graph();

  // Add appropriate method declarations as necessary for your implementation
  void symmetrize();
  void dfs(int v, List<int> *l);
  void rep_updator();
  void coll_source();
  void similar();
  void printResult(string FileName);
};



#endif

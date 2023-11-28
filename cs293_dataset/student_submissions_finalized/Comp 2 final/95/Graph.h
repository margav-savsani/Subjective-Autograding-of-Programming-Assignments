#include<vector>
#include<fstream>

#ifndef STD_HEADERS_H
#include"std_headers.h"
using namespace std;
class Node {
 public:
 vector<int>adjancy_in;
 vector<int> adjancy_out;
 vector<int> similar_nodes;
 vector<int> undir_sim;
 vector<int> adjancy;

 bool source_node;
 bool visited;
  int value;
Node(){
  this->visited=0;
  this->source_node=true;
}

  // insert other fields and methods as appropriate
};

class Graph {
  public:
  int numNodes;
  Node *nodes;
  int numEdges;
  vector<int> coll_gph;
  fstream outgraph;
  int c;
  // Add appropriate fields as necessary for your implementation
  
 public:
  Graph(int nNodes) {
    numNodes = nNodes;
    numEdges=0;
     outgraph.open("outgraph.txt", ios::out);
    nodes = new Node[numNodes];
    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }
    
    // Add appropriate code as necessary for your implementation
  }
  void add_edges(int a,int b);
  void check_similar();
  void collapse_graph();
  int dfs(int r,int& maximum);
  void print_results();
  void print_graph();
  // ~Graph() {
  //   delete[] nodes;
  //   // Add appropriate code as necessary for your implementation
  // }

  // Add appropriate method declarations as necessary for your implementation

 
};

#endif

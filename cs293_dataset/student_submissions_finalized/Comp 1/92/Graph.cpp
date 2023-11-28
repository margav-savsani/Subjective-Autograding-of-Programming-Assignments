#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  int vertex=rand()%numNodes;
  DFS(vertex);
  
}

void Graph::printResults() {
  cout<<"Number of connected components"<<numNodes-count1-count2<<endl;
  cout<<"Number of vertices visited once"<<count1<<endl;
  cout<<"Number of vertices visited twice"<<count2<<endl;
  Tree.printBST("",0);
}

#endif

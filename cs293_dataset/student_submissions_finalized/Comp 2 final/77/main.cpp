#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "graph.cpp"
#endif

int main()
{
  Graph *myGraph;
  
  myGraph = new Graph("outgraph.txt");
  myGraph->print_sources();
  myGraph->similar_node_pairs();
  myGraph->collapsed_graph();
  myGraph->collapsed_edges();
  return 0;
}

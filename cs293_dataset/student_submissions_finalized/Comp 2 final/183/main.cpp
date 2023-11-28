#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "graph.cpp"
#endif

int main(int argc, char **argv)
{ 
  Graph *myGraph;
  myGraph = new Graph();
  if (myGraph == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  myGraph->print();
  myGraph->similar();
  myGraph->collapse();
  return 0;
}
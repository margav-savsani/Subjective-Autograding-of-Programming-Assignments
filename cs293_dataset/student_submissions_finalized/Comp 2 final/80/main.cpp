#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// #ifndef GRAPH_BST_CPP
#include "Graph.cpp"
// #endif

int main(int argc, char **argv){
  Graph *myGraph;


  myGraph = new Graph();

  myGraph->printSources();
  
  myGraph->fix_similar();
  myGraph->printSimilar();
  myGraph->take_closure_and_collapse();
  myGraph->print_collapsed();

  return 0;
}
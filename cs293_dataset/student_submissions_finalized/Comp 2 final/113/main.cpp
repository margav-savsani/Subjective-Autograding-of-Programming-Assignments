#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

int main(int argc, char **argv)
{
  Graph *myGraph;

  myGraph = new Graph();
  if (myGraph == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  myGraph->printSources();
  myGraph->printSimilar();
  //myGraph->print();
  myGraph->printCollapsed();

  return 0;
}

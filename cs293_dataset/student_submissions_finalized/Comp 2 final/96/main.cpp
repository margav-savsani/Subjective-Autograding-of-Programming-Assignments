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

  int numNodes;
  cin>>numNodes;

  myGraph = new Graph(numNodes);
  if (myGraph == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  myGraph->printResults();

  return 0;
}

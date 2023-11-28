#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_CPP
#include "graph.cpp"
#endif

using namespace std;

int main(int argc, char **argv)
{
  Graph *myGraph;

  myGraph = new Graph("outgraph.txt");
  if (myGraph == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  myGraph->DFS();
  myGraph->printResults();

  return 0;
}

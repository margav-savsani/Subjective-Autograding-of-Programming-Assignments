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

//   if (argc != 4) {
//     cerr << "Usage: " << argv[0] << " numNodes numEdges graphFile" << endl;
//   }


  myGraph = new Graph();
  if (myGraph == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  myGraph->similarNodes();
  myGraph->compressGraph();
  myGraph->printResults();
}
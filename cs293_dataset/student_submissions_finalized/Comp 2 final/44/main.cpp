#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

int main(int argc, char **argv)
{

  // if (argc != 4) {
  //   cerr << "Usage: " << argv[0] << " numNodes numEdges graphFile" << endl;
  // }

  // int numNodes = stoi(argv[1]);
  // int numEdges = stoi(argv[2]);

  int numNodes;
  cin >> numNodes;
  Graph *myGraph;
  myGraph = new Graph(numNodes);
  
  Graph *cpdGraph;

  if (myGraph == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  myGraph->printResults();

  return 0;
}

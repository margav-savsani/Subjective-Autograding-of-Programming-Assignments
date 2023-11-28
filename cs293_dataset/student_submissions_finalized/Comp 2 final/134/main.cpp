#ifndef STD_HEADERS_H
#endif
#include "graph.cpp"
#include<iostream>
using namespace std;

#ifndef GRAPH_BST_CPP
#endif

int main(int argc, char **argv)
{
  Graph *myGraph;

//   if (argc != 4) {
//     cerr << "Usage: " << argv[0] << " numNodes numEdges graphFile" << endl;
//   }

  int numNodes;
  cin >> numNodes;
//   int numEdges = stoi(argv[2]);
//   string graphFileName = argv[3];

  myGraph = new Graph(numNodes);
//   if (myGraph == nullptr) {
//     cerr << "Memory allocation failure." << endl;
//     exit(-1);
//   }

//   myGraph->modifiedDFS();
//   myGraph->printResults();

     myGraph->findSources();
     myGraph->updateSimilars();
     myGraph->print();
  return 0;
}

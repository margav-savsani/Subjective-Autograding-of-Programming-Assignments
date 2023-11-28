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

  int n = 0;
  cin >> n;
  myGraph = new Graph(n);

  int n1 = 0, n2 = 0;
  bool source = true;
  while (true) {
    if (source) {
        cin >> n1 >> n2;
        if (n1 == -1 && n2 == -1) {
            source = false;
            continue;
        }
        myGraph->insertEdge(n1, n2);
    } else {
        cin >> n1 >> n2;
        if (n1 == -1 && n2 == -1) {
            break;
        }
        myGraph->insertSimilar(n1, n2);
    }
  }

  // Find source nodes
  myGraph->sourceNodes();

  // Find similar nodes
  myGraph->similarNodes();

  // Rebuild Graph
  Graph* myGraph2 = new Graph(n);
  // Make graph with similar nodes
  myGraph2->rebuildGraph(myGraph);

  // Find collapsed nodes
  myGraph2->collapsedNodes(myGraph);
  
  myGraph->printResults(myGraph2);

  return 0;
}

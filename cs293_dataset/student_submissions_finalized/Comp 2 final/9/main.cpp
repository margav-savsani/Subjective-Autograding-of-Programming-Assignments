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
  // cout << "Number of Nodes: ";
  cin >> numNodes;

  myGraph = new Graph(numNodes);

  int from, to;
  cin >> from >> to;

  while (from != -1 and to != -1)
  {
    myGraph->insertNode(from, to);
    cin >> from >> to;
  }
  // cout << "All edges inserted\n";

  int similar1, similar2;
  cin >> similar1 >> similar2;

  while (similar1 != -1 and similar2 != -1)
  {
    myGraph->insertSimilar(similar1, similar2);
    cin >> similar1 >> similar2;
  }
  // cout << "All similar edges taken\n";

  myGraph->checkSource();
  myGraph->checkSimilar3();
  myGraph->checkSimilar2(numNodes);
  myGraph->collapse();
  myGraph->printResults();
  return 0;
}

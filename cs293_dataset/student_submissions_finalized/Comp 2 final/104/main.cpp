#include "graph.cpp"
using namespace std;

int main()
{
  Graph *myGraph;

  int numNodes;
  int numEdges=0;

  cin >> numNodes;

  myGraph = new Graph(numNodes);
  if (myGraph == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  myGraph->principle();
  myGraph->afterClosureThings();

  return 0;
}
#include "Graph.cpp"

int main(int argc, char **argv)
{
  Graph *myGraph;
  myGraph = new Graph();
  if (myGraph == nullptr)
  {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  myGraph->printResults();

  return 0;
}

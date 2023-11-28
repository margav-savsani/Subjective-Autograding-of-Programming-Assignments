#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
using namespace std;
#include "Graph.cpp"

int main(int argc, char **argv)
{
  Graph *myGraph = new Graph(argv[1]);
  myGraph->printResults(); // prints the results
  return 0;
}


using namespace std;

#ifndef GRAPH_BST_CPP
#include "graph.cpp"
#endif

int main(int argc, char **argv)
{
  
  Graph myGraph ;
 myGraph.check_similar();
 myGraph.print_sources();
 myGraph.print_similar();
 myGraph.collapsed();
  return 0;
}

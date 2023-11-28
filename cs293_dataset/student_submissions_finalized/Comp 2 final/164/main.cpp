#include <iostream>
#include "graph.cpp"
using namespace std;
int main(int argc, char** argv)
{

  graph g;
  g.find_sources();
  g.find_similar();
  g.print_similar();
  g.collapse();
}
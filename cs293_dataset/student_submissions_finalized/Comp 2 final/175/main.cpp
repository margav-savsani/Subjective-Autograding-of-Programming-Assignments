#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.h"
#endif

int main(){
  Graph *myGraph;
  fstream file;
  file.open("outgraph.txt",fstream::out); // output will be present in "outgraph.txt" file
  myGraph = new Graph();
  myGraph->print_src(file);
  file << endl;
  myGraph->print_similar(file);
  file << endl;
  myGraph->print_collapse(file);
  file.close();
}

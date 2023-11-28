#include<iostream>
using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#include <fstream>
#endif
int main(int argc, char **argv)
{ 
  Graph *myGraph;
  int n,n1,n2;
  cin>>n;
  myGraph = new Graph(n);
  cin >> n1 >> n2;
  while(n1!=-1 || n2!=-1){
    myGraph->addEdge(n1,n2);
    cin>>n1>>n2;
  }
  cin>>n1>>n2;
  while(n1!=-1 || n2!=-1){
      myGraph->addSimilar(n1-1,n2-1);
      cin>>n1>>n2;
  }
  myGraph->printSrcNodes();
  cout<<endl;
  myGraph->processSimilar();
  myGraph->printSimilar();
  cout<<endl;
  myGraph->createEquivalence();
  myGraph->collapse();
  myGraph->print_collapsed();

  return 0;
}
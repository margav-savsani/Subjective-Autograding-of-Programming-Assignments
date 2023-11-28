
#include "graph.cpp"

int main(int argc, char **argv)
{
  Graph *myGraph;

  myGraph = new Graph();
  if (myGraph == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }
  cout<<"Source nodes:";
  myGraph->findsrcnodes();
  cout<<endl;
  cout<<"Similar node pairs:";
  myGraph->calcsimilar();
  cout<<endl;
  cout<<"Collapsed graph:"<<endl;
  myGraph->Printcollapsedgraf();
  cout<<endl;
  return 0;
}

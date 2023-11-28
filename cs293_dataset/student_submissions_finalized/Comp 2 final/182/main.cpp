#include "graph.cpp"
using namespace std;

int main(int argc, char **argv)
{
  Graph *myGraph;  
  int numNodes;
  cin>>numNodes;
  myGraph = new Graph(numNodes);
  if (myGraph == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }
  while (true)
  {
    int a,b;
    if(a==-1&&b==-1)break;
    cin>>a>>b;
    myGraph->addedge(a,b);
  }
  while (true)
  {
    int a,b;
    if(a==-1&&b==-1)break;
    cin>>a>>b;
    myGraph->addsimilarpair(a,b);
  }
  myGraph->printResults();
  return 0;
}

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#include "collapsedgraph.cpp"


int numNodes;
int main(int argc, char **argv)
{
  Graph *myGraph;
   int inp1=0;int inp2=0;
   
  int numNodes ;
  cin>>numNodes;
   myGraph = new Graph(numNodes);
  while(true){
    cin>>inp1;
    cin>>inp2;
    if(inp1==-1 && inp2==-1) break;
    myGraph->modify_adj(inp1,inp2);
  }
  
  if (myGraph == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }
    myGraph->sourcenodes();
    while(true){
    cin>>inp1;
    cin>>inp2;
    
    if(inp1==-1 && inp2==-1) break;
    myGraph->check(inp1-1,inp2-1);
  }
  
  myGraph->similarnodes();
 
  myGraph->simil();
   myGraph->print();
  return 0;
}
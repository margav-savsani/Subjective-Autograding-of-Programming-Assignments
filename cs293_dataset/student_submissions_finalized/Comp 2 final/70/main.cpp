#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.h"
#endif

int main(int argc, char **argv)
{
  Graph *myGraph;
  
  int numNodes;
  cin >> numNodes;

  myGraph = new Graph(numNodes);
  
  while(true){
    int n1, n2;
    cin >> n1;
    cin >> n2;
    if(n1 == -1 && n2 == -1){
      break;
    }
    myGraph->insertEdge(n1, n2);
  }

  while(true){
    int edge1, edge2;
    cin >> edge1;
    cin >> edge2;
    if(edge1 == -1 && edge2 == -1){
      break;
    }
    myGraph->updateSimilarity(edge1, edge2);
  }
  myGraph->checkNupdateSimilarity();

  ofstream outfile;
  outfile.open("outgraph.txt");
  outfile<<"Source nodes: "<<myGraph->printSrcNodes()<<endl;
  outfile<<"Similar node pairs: "<<myGraph->printSimilarNodes()<<endl;
  outfile<<"Collapsed graph:\n";
  myGraph->printCollapsedGraph(&outfile);
  
  outfile.close();
  return 0;
}

#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::modifiedDFS() {
  for (auto i : adj){
    if (visited[i.first] ==0 ){
      comp++;
      travel(i.first,-1);
      cout<<endl;
      b.printBST(" ");
    }
  }
  return;
}

void Graph::printResults() {
  int one=0;
  int two=0;
  for(int y=1;y<=numNodes;y++){
    if(visited[y]==1){one++;}
    if(visited[y]==2){two++;}
  }
  cout<<"No. of connected components: "<<comp<<endl;
  cout<<"No. of nodes visited once: "<<one<<endl;
  cout<<"No. of nodes visited twice: "<<two<<endl;
  //cout<<"No. of nodes that are present in a cycle: "<<ncycles<<endl;
  return;
}

#endif

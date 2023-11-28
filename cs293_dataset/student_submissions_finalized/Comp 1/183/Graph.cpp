#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS(){
    for(int i=0;i<numNodes;i++){
      if(nodes[i].visited==0){b.root=NULL;connected_comp++;DFS(&nodes[i],NULL);b.printBST(" ");}
    }
  }


void Graph::printResults(){
  int v2=0;
  int v1=0;
  for (int i = 0; i < numNodes; i++) {
    if(nodes[i].visited==2){v2++;}
    if(nodes[i].visited==1){v1++;}
  }
  int c=0;
  for (int i = 0; i < numNodes; i++){
    if(g[i]==true){c++;}
  }
cout<<"No. of connected components: "<<connected_comp<<endl;
cout<<"No. of nodes visited once: "<<v1<<endl;
cout<<"No. of nodes visited twice: "<<v2<<endl;
cout<<"No. of nodes that are present in a cycle: "<<c<<endl;
}
#endif

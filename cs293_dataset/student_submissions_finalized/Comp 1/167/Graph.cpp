#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::dfs(int k,int p){
  node* n=dfsele.find(nodes[k].value-1);
  if(n!=NULL){
   while(n!=NULL){
    nodes[n->data].incycle=true;
    n=n->next;
   }
  }
  dfsele.insertNode(nodes[k].value-1);
  visited[k]++;
  bool h;
  tree.insert(nodes[k].value);
  node* x=nodes[k].adjacency.head;
  while(x!=NULL){
  if(visited[x->data]<2 && x->data!=p){ 
    dfs(x->data,k);
    }
    x=x->next;
  }
  
}
// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  for(int j=0;j<numNodes;j++){
    if(visited[j]==0){
      connectcomp++;
      dfs(j,-1);
      tree.printBST(" ");
      tree.root=NULL;
    }
  }
  for(int k=0;k<numNodes;k++){
    if(nodes[k].incycle==true) ncycles++;
  }
}

void Graph::printResults() {
  int a=0;
  int b=0;
  for(int f=0;f<numNodes;f++){
    if(visited[f]==1){
      a++;
    }
    if(visited[f]>=2){
      b++;
    }
  }
  cout<<"No. of connected components: "<<connectcomp<<endl;
  cout<<"No. of nodes visited once: "<<a<<endl;
  cout<<"No. of nodes visited twice: "<<b<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<ncycles<<endl;
  return;
}

#endif

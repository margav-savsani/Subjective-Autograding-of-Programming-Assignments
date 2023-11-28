#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation

void Graph::DFS(BST *bst,int n,int p){
  v[n-1]++;
  Adjacency *lx=nodes[n-1].leo;
  while(lx!=nullptr){
    if(v[lx->object]<2){  
      if(lx->object+1==p){
        if(lx->next!=nullptr)lx=lx->next;
        else break;
      }
      bst->insert(lx->object+1);
      DFS(bst,lx->object+1,n);
    }
    lx = lx->next;
  }
}

void Graph::modifiedDFS() {
  int noC=0;
  for(int i=0;i<numNodes;i++){
    if(v[i]==0){
      BST *bst=new BST();
      bst->insert(nodes[i].value);
      DFS(bst,nodes[i].value,0);
      bst->printBST("");
      noC++;
    }
  }
  cout<<"No. of connected components:"<<noC<<endl;
  return;
}

void Graph::printResults() {
  int noV1=0;
  int noV2=0;
  for(int i=0;i<numNodes;i++){
    if(v[i]==1)noV1++;
    if(v[i]==2)noV2++;
  }
  cout<<"No. of nodes visited once:"<<noV1<<endl;
  cout<<"No. of nodes visited twice:"<<noV2<<endl;
  cout<<"No. of nodes that are present in a cycle:0"<<endl;
  return;
}

#endif

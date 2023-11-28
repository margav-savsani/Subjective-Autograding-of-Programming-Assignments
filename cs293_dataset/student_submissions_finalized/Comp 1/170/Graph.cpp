#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

int numCycle = 0;
int jee = 0;
void Graph::DFS(int p, Node n, BST &bst){
  int zip = n.value-1;
  visited[zip]++;
  if(c[zip] == 1){
    int temp = p;
    if(b[temp] == 0){
      b[temp] = 1;
      while(temp != zip){
        if(jee > numNodes)break;
        temp = a[temp];
        b[temp] = 1;
        jee++;
      }
    }
  }
  a[zip] = p;
  c[zip] = 1;

  for(int j=0; n.adjlist[j]>-1; j++){
    if( (n.adjlist[j] != p) && (visited[n.adjlist[j]] < 2) ){
      bst.insert(n.adjlist[j]+1);
      DFS(n.value-1, nodes[n.adjlist[j]], bst);
    }
  }
}

void Graph::modifiedDFS() {
  for(int i=0; i<numNodes ; i++){
    if(visited[i]==0){
      numComp++;
      Comp[numComp-1] = BST (new TreeNode(i+1));
      DFS(-2, nodes[i], Comp[numComp-1]);
    }
  }
}

void Graph::printResults() {
  cout<<"No. of connected components:"<<numComp<<endl;
  int nv1 = 0;
  int nv2 = 0;
  for(int i=0; i<numNodes; i++){
    if(b[i] == 1){
      numCycle++;
    }
    if(visited[i] == 1) nv1++;
    else if(visited[i] == 2) nv2++;
  }
  cout<<"No. of nodes visited once:"<<nv1<<endl;
  cout<<"No. of nodes visited twice:"<<nv2<<endl;
  cout<<"No. of nodes that are present in a cycle:"<<numCycle<<endl;
  for(int i=0; i<numComp; i++){
    cout<<"Component-"<<i+1<<":"<<endl;
    Comp[i].printBST("");
  }
}

#endif
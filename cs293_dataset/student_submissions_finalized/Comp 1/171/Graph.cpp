#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
void Graph::DFS(Node n,BST b,int par){
  int k=0;
  visited[n.value-1]++;
  if(a3[n.value-1]==1){
    int bok=par;
    if(a2[bok]==0){
      a2[bok]=1;
      while(bok!=n.value-1 && k<numNodes){
        bok=a1[bok];
        a2[bok]=1;
        k++;
      }
    }
  }
  a1[n.value-1]=par;
  a3[n.value-1]=1;
  for(int i=0;n.adjacentNodes[i]>-1;i++){
    if(n.adjacentNodes[i]!=par && visited[n.adjacentNodes[i]]<2){
      b.insert(n.adjacentNodes[i]+1);
      DFS(nodes[n.adjacentNodes[i]],b,n.value-1);
    }
  }
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  for(int i=0;i<numNodes;i++){
    if(visited[i]==0){
      conncomp++;
      nodes[i].b = BST(new TreeNode(i+1));
      DFS(nodes[i],nodes[i].b,-2);
    }
  }
  return;
}

void Graph::printResults(){
  
  cout << "No. of connected components:" << conncomp << endl;
  int vison=0,vistw=0,numcyc=0;
  
  for(int i=0;i<numNodes;i++){
    if(a2[i]==1)
      numcyc++;
    if(visited[i]==1)
      vison++;
    if(visited[i]==2){
      vistw++;
      
    }
  }
  
  cout << "No. of nodes visited once:" << vison << endl;
  cout << "No. of nodes visited twice:" << vistw << endl;
  cout << "No. of nodes that are present in a cycle:" << numcyc << endl;
  for(int i=0;i<numNodes;i++){
    if(nodes[i].b.root!=nullptr){
      //cout << "bokkaga" << endl;
      nodes[i].b.printBST("");
    }
  }

  return;
}

#endif
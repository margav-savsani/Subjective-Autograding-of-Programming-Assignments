#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::cycles(int val, int initial,bool &present){
  cyc[val] = cyc[val]+1;
  listOfObjects *curr = nodes[val].adjacent;
  while(curr!=NULL){
    if(cyc[curr->object]!= 2){
      if(parent[val*numNodes+curr->object]==0){  
        parent[(curr->object)*numNodes+val] = 1;  
        cycles(curr->object,initial,present);
      }  
    }
    else{
      if(curr->object == initial){
        present = true;
        return;
      }
    }
    curr = curr->next;
  }  
}
void Graph::DFS(int val){
  Tree->insert(nodes[val].value);
  visited[val] = visited[val]+1;
  listOfObjects *curr = nodes[val].adjacent;
  while(curr!=NULL){
    if(visited[curr->object]!=2){
      if(adj[val*numNodes+curr->object]==0){
        adj[(curr->object)*numNodes+val]=1;
        DFS(curr->object);
      }  
    }
    curr = curr->next;
  }
}
// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  for(int i=0;i<numNodes;i++){
    if(visited[i]==0){
      connected_components++;
      Tree = new BST();
      DFS(i);
      cout<<"BST"<<endl;
      Tree->printBST(" ");
    }
  }
  return;
}

void Graph::printResults() {
  cout<<"No.of connected components "<<connected_components<<endl;
  int once = 0;
  int twice = 0;
  for(int i=0;i<numNodes;i++){
    if(visited[i]==1){
      once++;
    }
    if(visited[i]==2){
      twice++;
    }
  }
  cout<<"No.of nodes visited once "<<once<<endl;
  cout<<"No.of nodes visited twice "<<twice<<endl;
  bool print = false; 
  int l = numNodes; 
  for(int i=0;i<numNodes;i++){
    int j = 0;
    for(int m=0;m<numNodes;m++){
      cyc[m] = 0;
    }
    bool present = false;
    cycles(i,i,present);
    if(present){
      int k = 0;
      print = true;
      for(int n =0;n<numNodes;n++){
        if(cyc[n]!= 0)k++;
      }
      if(k<l)l=k;
    }
  }
  if(!print)cout<<"No cycles are possible"<<endl;
  else cout<<"No of nodes present in cycle are "<<l<<endl;
  return;
}

#endif
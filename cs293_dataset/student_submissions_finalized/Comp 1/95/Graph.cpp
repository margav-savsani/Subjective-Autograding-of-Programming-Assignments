#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::new_dfs(int a,BST *b){
  b->insert(a);
  if(nodes[a].visited==0){
    nodes[a].visited++;
    visited_once++;
  }
  else if(nodes[a].visited==1){
    nodes[a].visited++;
    visited_once--;
    visited_twice++;
  }
  
  for(int i=0;i<nodes[a].adjancy.size();i++){
    if(nodes[nodes[a].adjancy[i]-1].visited==0){
    bool parent=false;
    for(int j=0;j<nodes[a].parent.size();j++){
      if(nodes[a].parent[j]==nodes[a].adjancy[i]){
        parent=true;
      }
    }
    if(nodes[nodes[a].adjancy[i]-1].visited<=1&&!parent){
      nodes[nodes[a].adjancy[i]-1].parent.push_back(nodes[a].value);
      
      new_dfs(nodes[a].adjancy[i]-1,b);
      nodes[a].parent.push_back(nodes[a].adjancy[i]);
    }}
  }
  for(int i=0;i<nodes[a].adjancy.size();i++){
    if(nodes[nodes[a].adjancy[i]-1].visited==1){
    bool parent=false;
    for(int j=0;j<nodes[a].parent.size();j++){
      if(nodes[a].parent[j]==nodes[a].adjancy[i]){
        parent=true;
      }
    }
    if(nodes[nodes[a].adjancy[i]-1].visited<=1&&!parent){
      nodes[nodes[a].adjancy[i]-1].parent.push_back(nodes[a].value);
      
      new_dfs(nodes[a].adjancy[i]-1,b);
      nodes[a].parent.push_back(nodes[a].adjancy[i]);
    }}
  }
}
void Graph::modifiedDFS() {
  int i=0;
  while(i<numNodes){
    if(nodes[i].visited==0){
      BST *a=new BST();
  new_dfs(i,a);
  conn_component++;
  a->printBST("BST",false);}
  i++;}
  return;
}

void Graph::printResults() {
 
  cout<<"connected component : "<<conn_component<<endl;
  cout<<"visited once : "<<visited_once<<endl;
  cout<<"visited twice : "<<visited_twice<<endl;
  cout<<"number of nodes in cycles:"<<visited_twice<<endl;

  return;
}

#endif

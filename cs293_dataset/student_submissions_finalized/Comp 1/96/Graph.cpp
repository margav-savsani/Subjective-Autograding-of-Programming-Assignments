#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::DFS(int value){
  if(nodes[value].visited>=2 || nodes[value].backtracked) return;
  
  nodes[value].visited++;
  Tree[connected].insert(value+1);
  cout<<value+1<<"-";
  for(int i = 0; i < numNodes; i++){
    if(nodes[value].adjacency[i] && nodes[i].visited<=2 && !nodes[value].parent[i]){
      nodes[i].parent[value]=true;
      DFS(i);
    }
    if(i==numNodes-1) nodes[value].backtracked=true;
  }
}
void Graph::modifiedDFS() {
  DFS(rand()%numNodes);
  connected++;
  for(int i = 0; i < numNodes; i++){
    if(nodes[i].visited==0){
      DFS(i);
      connected++;
    }
  }
  return;
}

void Graph::printResults() {
  int visitedOnce=0;
  int visitedTwice=0;

  for(int i = 0; i < numNodes; i++){
    if(nodes[i].visited==1) visitedOnce++;
    else if(nodes[i].visited==2) visitedTwice++;
  }
  cout<<endl;
  cout<<"No. of connected components: "<<connected<<endl;
  cout<<"No. of nodes visited once: "<<visitedOnce<<endl;
  cout<<"No. of nodes visited twice: "<<visitedTwice<<endl<<endl;
  for(int i = 0; i < connected; i++){
    cout<<"Tree "<<i+1<<":"<<endl<<endl;
    Tree[i].print();
    cout<<endl;
  }
  return;
}

#endif

#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  for (int i = 0; i< numNodes; i++){
    if(Visited[i] == 0){
      numberOfConnectedComponents++;
      Visited[i]++;
      root->Insert(root, i);
      myDFS(i);
      root->printBinaryTree(root, "", false);
    }
  }
  return;
}
void Graph::myDFS(int i) {
  Visited[i]++;
  vector<int>::iterator it;
  for (it = Adj[i].begin(); it != Adj[i].end(); ++it){
    if(Visited[*it] < 2){
      root->Insert(root, *it);
      myDFS(*it);
    }
  }
  return;
}
void Graph::VisitCount(){
  for (int i = 0; i< numNodes; i++){
    if(Visited[i] == 1) oneVisitCount++;
    else if(Visited[i] == 2) twoVisitCount++;
  }
  return;
}
void Graph::printResults() {
  VisitCount();
  cout<<"No. of connected components:"<<numberOfConnectedComponents<<"\n";
  cout<<"No. of nodes visited once:"<<oneVisitCount<<"\n";
  cout<<"No. of nodes visited twice:"<<twoVisitCount<<"\n";
  cout<<"No. of nodes that are present in a cycle:"<<twoVisitCount<<"\n";
  return;
}

#endif

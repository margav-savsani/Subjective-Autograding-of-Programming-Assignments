#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
using namespace std;
void Graph::modifiedDFS() {
  BST tre;
  dfs(0,visited,tre);
  tre.printBST(" ");
  Node *temp=nodes;
  for(int i=1;i<numNodes;i++){
    BST a;
    if(visited[i]=0) dfs(i,visited,a);
    tre.printBST(" ");
    i++;
  }
  return;
}

void Graph::printResults() {
  return;
}

#endif
void Graph::dfs(int start, int* visited,BST tree){
  visited[start] = 1;
  listOfObjects<Node*>*temp1=adj[start].adjacent;
  do{
    if(!visited[temp1->object->value]==2){
      dfs(temp1->object->value,visited,tree);
      tree.insert(tree.root,temp1->object->value);
      visited[temp1->object->value]++;
      temp1=temp1->next;
    }
  }while (temp1->next!=nullptr);
}


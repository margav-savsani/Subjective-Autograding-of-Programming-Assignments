#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::connectedComp(){
  int vis[numNodes];
  int connComp=0;
  for (int i = 0; i<numNodes; i++){
    visited[i] = 0;
  }
  for (int i = 0; i<numNodes; i++){
    if(visited[i] == 0){
      DFS(i);
      connComp++;
      if (connComp_num == nullptr){
        connComp_num = new adjList(i);
      }
      else{
        adjList *x = connComp_num, *y = nullptr;
        while( x != nullptr){
          y = x;
          x = x->next;
        }
        y = new adjList(i);
      }
    }
  }
  connComp_number = connComp;
  BSTree = new BST*[connComp_number];
  numNod = new int[connComp_number];
  for (int i = 0; i<connComp_number; i++){
    numNod[i] = 0;
  }
}

void Graph::DFS(int i){
  visited1[i]++;
  a[i] = time1++;
  for (adjList *ad = nodes[i].adjacency; ad != nullptr; ad = ad->next){
    if (visited1[ad->object] != 0){
      DFS(ad->object);
    }
  }
  d[i] = time1++;
}

void Graph::DFS2(int i, int num){
  visited[i]++;
  if (visited[i] == 1){ t1[i] = time2++; }
  if (visited[i] == 2){ t2[i] = time2++; }
  if (visited[i] == 1){numNod[num]++;}
  BSTree[num]->insert(i);
  for( adjList *ad = nodes[i].adjacency; ad != nullptr; ad = ad->next){
    if(visited[ad->object] < 2){
      DFS2(ad->object, num);
    }
  }
  if (visited[i] == 3){ t3[i] = time2++; }
  if (visited[i] == 2){ t2[i] = time2++; }
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  connectedComp();
  int i = 0;
  for (adjList *list = connComp_num; list != nullptr; list = list->next){
    DFS2(list->object, i);
    i++;
  }
  return;
}

void Graph::printResults() {
  int visi1 = 0;
  int visi2 = 0;
  for (int i = 0; i < numNodes; i++){
    if (visited[i] == 1) { visi1++; }
    if (visited[i] == 2) { visi2++; }
  }
  cout << "NUMBER OF CONNECTED COMPONENTS:" << connComp_number << endl;
  cout << "NUMBER OF NODES VISITED ONCE:" << visi1 <<endl;
  cout << "NUMBER OF NODES VISITED TWICE:" << visi2 <<endl;
  for (int i = 0; i<connComp_number; i++){
    cout << "NUMBER OF NODES IN THIS CYCLE" << numNod[i] << endl;
  }
  cout << "printing BST's" << endl;
  int i = 0;
  for (adjList *list = connComp_num; list != nullptr; list = list->next){
    BSTree[i]->print();
    i++;
  }
  return;
}

#endif

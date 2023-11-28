#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

using namespace std;
void Graph::getSourceNodes(){
  file << "Source nodes: ";
  for(int i = 0; i<numNodes; i++){
    if(nodes[i].from_edges==NULL) file << i+1 << ' ';
  }
  file << "\n\n";
}

void Graph::computeSimilarity(){
  for(int i = 0; i<numNodes; i++){
    for(int j = 0; j<numNodes; j++){
      similar[i][j] = recursiveComputeSimilarity(i,j);
    }
  }
}

int Graph::recursiveComputeSimilarity(int i, int j){
  if(similar[i][j]!=-1) return similar[i][j];
  if(nodes[i].from_edges==NULL){
    similar[i][j]=0;
    return 0;
  }
  if(nodes[i].from_edges->head->next==NULL&&nodes[i].from_edges->head->node->value==j){
    similar[i][j]=1;
    return 1;
  }
  if(nodes[j].from_edges==NULL){
    similar[i][j]=0;
    return 0;
  }
  listOfNodes* i_parents = nodes[i].from_edges->head;
  listOfNodes* j_parents = nodes[j].from_edges->head;
  while(i_parents!=NULL){
    j_parents = nodes[j].from_edges->head;
    bool similar_found(false);
    while(j_parents!=NULL){
      if(recursiveComputeSimilarity(i_parents->node->value,j_parents->node->value)==1){
        similar_found = true;
        break;
      }
      j_parents = j_parents->next;
    }
    if(!similar_found){
      similar[i][j]=0;
      return 0;
    }
    i_parents = i_parents->next;
  }
  while(j_parents!=NULL){
    i_parents = nodes[i].from_edges->head;
    bool similar_found(false);
    while(i_parents!=NULL){
      if(recursiveComputeSimilarity(j_parents->node->value,i_parents->node->value)==1){
        similar_found = true;
        break;
      }
      i_parents = i_parents->next;
    }
    if(!similar_found){
      similar[i][j]=0;
      return 0;
    }
    j_parents = j_parents->next;
  }
  similar[i][j]=1;
  similar[j][i]=1;
  return 1;
}

void Graph::printSimilar(){
  file << "Similar node pairs: ";
  for(int i = 0; i<numNodes; i++){
    for(int j = 0; j<numNodes; j++){
      if(similar[i][j]==1) file << "(" << i+1 << ", " << j+1 << ") ";
    }
  }
  file << "\n\n";
}

void Graph::collapse(){
  Node* new_graph = new Node[numNodes];
  for(int i = 0; i<numNodes; i++){
    visited[i] = 0;
  }
  int nodesAfterCollapsing(0);
  for(int i = 0; i<numNodes; i++){
    if(visited[i]) continue;
    nodesAfterCollapsing++;
    int collapseValue = DFS_Similar(i);
    new_graph[collapseValue].value = collapseValue;
    DFS_Collapse(i, collapseValue);
  }
  for(int i = 0; i<numNodes; i++){
    listOfNodes* x = nodes[i].to_edges;
    if(x==NULL) continue;
    x = x->head;
    while(x!=NULL){
      new_graph[nodes[i].collapsed_to].insert_to(&new_graph[x->node->collapsed_to]);
      x = x->next;
    }
  }
  file << "Collapsed graph: \n\n";
  file << nodesAfterCollapsing << ": ";
  for(int i = 0; i<numNodes; i++){
    if(new_graph[i].value==-1) continue;
    file << i+1 << ' ';
  }
  file << '\n';
  for(int i = 0; i<numNodes; i++){
    if(new_graph[i].value==-1) continue;
    if(new_graph[i].to_edges==NULL) continue;
    listOfNodes* x = new_graph[i].to_edges->head;
    while(x!=NULL){
      if(i!=x->node->value) file << i+1 << ' ' << x->node->value+1 << '\n';
      x = x->next;
    }
  }
}

int Graph::DFS_Similar(int x){
  if(visited[x]) return x;
  visited[x] = 1;
  int mx = x;
  for(int i = 0; i<numNodes; i++){
    if(similar[x][i]||similar[i][x]){
      int y = DFS_Similar(i);
      if(y>mx) mx = y;
    }
  }
  return mx;
}

void Graph::DFS_Collapse(int x, int mx){
  if(visited[x]==2) return;
  visited[x]=2;
  nodes[x].collapsed_to = mx;
  for(int i = 0; i<numNodes; i++){
    if(similar[x][i]||similar[i][x]){
      DFS_Collapse(i, mx);
    }
  }
}
#endif

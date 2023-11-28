#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
void deleteparent(listOfObjects<int>* adjlist,int b){
  //used for deleting the cause in the DFS().
  listOfObjects<int>* x = adjlist;
  listOfObjects<int>* y;
  while(x != NULL){
    y = x;
    if(x->object == b){
      if(x->next == NULL && x->prev == NULL){
        x = NULL;
        return;
      }
      if(x->next != NULL && x->prev != NULL){
        x->next->prev = y->prev;
        x->prev->next = y->next;
        return;
      }
      if(x->prev != NULL && x->next == NULL){
        x->prev->next = NULL;
        return;
      }
      if(x->prev == NULL && x->next != NULL){
        x->next->prev = NULL;
        return;
      }
    }
    x = x->next;
  }
  return;
}
void Graph::DFSnaive(Node a){
  //whenever this function is called i will store the elements in the vector so that i will use it for the sake of cycles.
  //and also the nodes in cycle.
  listOfObjects<int>* x = a.adjacentnodes;
  int b = a.value - 1;
  visited1[b] ++;
  cyclics.push_back(b);
  while(x != NULL){
    deleteparent(nodes[x->object].adjacentnodes,b);
    if(visited1[x->object] != 2){
      if(nodes[x->object].value != b+1)
        DFSnaive(nodes[x->object]);
    }
    x = x->next;
  }
}
void Graph::DFS(Node a,BST* tree) {
  tree->insert(a.value);
  listOfObjects<int>* x = a.adjacentnodes;
  int b = a.value - 1;
  visited[b] ++;
  pathpattern[0][b] = count;
  count++;
  while(x != NULL){
    //i have to go in single direction so i have to delete the parent from the neighbouring nodes list
    //but its not showing any impact after the function.
    //inorder to show variation between the nodes visisted once and twice.
    deleteparent(nodes[x->object].adjacentnodes,b);
    if(visited[x->object] != 2){
      if(nodes[x->object].value != b+1)
        DFS(nodes[x->object],tree);
    }
    x = x->next;
  }
  pathpattern[1][b] = count;
  return;
}
void Graph::modifiedDFS(){
 for(int i=0;i<numNodes;i++){
    if(visited[i] == 0){
        connected++;
        BST* tree = new BST();
        DFS(nodes[i],tree);
        DFSnaive(nodes[i]);
        trees.push_back(tree);
      }       
    }
  }
int Graph::Cycles() {
  int c[cyclics.size()];
  for(int i =0;i < cyclics.size();i++){
    c[i] = cyclics[i];
  }
  //when one of the elements of the contributing array repeats then 
  //its said that cycle exits and the gap between them is number of nodes in the cycle. 
  return 0;
}
void Graph::printResults() {
  int visonce = 0;
  int vistwice = 0;
  for(int i = 0; i< numNodes; i++){
    if(visited[i] == 1) visonce++;
    if(visited[i] == 2) vistwice++;
  }
  cout<<"No. of connected components:"<<connected<<endl;
  cout<<"No. of nodes visited once:"<<visonce<<endl;
  cout<<"No. of nodes visited twice:"<<vistwice<<endl;
  cout<<"No. of nodes that are present in a cycle:0"<<endl;
  for (auto tree : trees ){
    tree->printBST(" ");
  }
}
#endif

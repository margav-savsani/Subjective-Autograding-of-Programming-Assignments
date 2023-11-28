#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif
void Graph::DFS(int k,BST *T,Node* pi){

  Node *a=&nodes[k-1];
  T->insert(a->value);
  arr[k-1]=arr[k-1]+1;
  if (a->right==nullptr) return;
  Node *v=a->right;
  while(v!=nullptr){
    if (v->value==pi->value){
      if (v->right!=nullptr){
      v->left->right=v->right;}
      else if(v->right==nullptr){
        v->left->right=nullptr;}
    }
    v=v->right;
  }  //removing pi from a adjacency list 
  Node*b=a->right;
  if(b==nullptr) return;
  while(b!=nullptr){
    if (arr[b->value-1]<2){
      DFS(b->value,T,a);
    }
    b=b->right;
  }
  return;
}

void Graph::modifiedDFS() {
  int index=0;
  int k=0;
  DFS(index+1,&T[k],&nodes[index]);  //calling dfs for 0 index node
  k++;
  while(index!=numNodes){
  
  while(arr[index]!=0){
  index++;}  //finding the index of node which is not visited in the previous dfs call

  if (index>=numNodes){
    nvis1=0;
    for (int x=0;x<numNodes;x++){
      if (arr[x]==1){nvis1++;}
    }
    return;}
  if(index==numNodes-1){
    T[k].insert(index+1);
    k++;
    arr[index]++;
    nvis1=0;
    for (int x=0;x<numNodes;x++){
      if (arr[x]==1){nvis1++;}
    }  //then there is only one element left which is the last element hence instead of calling dfs  i directly inserted it to bst
    return;}
  if (nodes[index].right==nullptr){T[k].insert(index+1);k++;arr[index]++;}
  else{
  DFS(index+1,&T[k],&nodes[index]);
  k++;}
  index=0;  
  }
  nvis1=0;
  for (int x=0;x<numNodes;x++){
      if (arr[x]==1){nvis1++;}
  }
  return;
}

void Graph::DFSCycle(int u, int parentindex, int* visit, int parent[], int* cycle){
  Node* a=&nodes[u-1];
   //the node is visited completely already
   if (visit[u-1] == 2) {
      return;
   }
   //partially visited node found that means there is a cycle
   if (visit[u-1] == 1) {   
        int b = parentindex;
        if (cycle[b-1]==0){cycle[b-1]=1;}
        while (b != u) {
            b = parent[b-1];
            if (cycle[b-1]==0){cycle[b-1]=1;}
        }
      
      return;
   }

   parent[u-1] = parentindex;
   visit[u-1] = 1;
   if (a->right==nullptr) return;
   Node *v=a->right;
   while(v!=nullptr){
      if (v->value != parent[u-1]) {
      DFSCycle(v->value, a->value, visit, parent, cycle);}
      v=v->right;
   }
   
   visit[u-1]=2;
   return;
}
 
void Graph::printResults() {
  int k=0;
  while(T[k].root!=nullptr){
    k++;
  }
  nvis2=numNodes-nvis1;  //nvis1+nvis2=numNodes
  



  nconnected=k;
  cout<<"No. of connected components:"<<nconnected<<endl;
  cout<<"No. of nodes visited once:"<<nvis1<<endl;
  cout<<"No. of nodes visited twice:"<<nvis2<<endl;
  k=0;
  
  for(int j=0;j<numNodes;j++){
    parent[j]=0;   //to store parent from which dfs is called
  }
  for (int j=0;j<numNodes;j++){
    visit[j]=0;   //intially all are not visited visit count 
  }
   for (int j=0;j<numNodes;j++){
    cycle[j]=0;    // an array to store which nodes are in cycles if array value is 1 that means node is in cycle
  } 
  int numofnodescyc=0;
  DFSCycle(1,0,visit,parent,cycle);
  int index=0;

  while(index!=numNodes){  
  while(visit[index]!=0){
  index++;}

  if (index>=numNodes){
    break;}
  if(index==numNodes-1){break;}
  if (nodes[index].right==nullptr){break;}
  else{
  DFSCycle(index+1,0,visit,parent,cycle);}
  index=0;  
  }

  for(int j=0;j<numNodes;j++){
    if (cycle[j]==1){numofnodescyc++;}
  }
  cout<<"No. of nodes that are present in a cycle:"<<numofnodescyc<<endl;
  while(T[k].root!=nullptr){
    T[k].printBST("",false);
    k++;
  }

  
  return;
}

#endif

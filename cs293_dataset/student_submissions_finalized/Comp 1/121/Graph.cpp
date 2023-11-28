#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<cassert>
#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  list<BST*> *bsts = nullptr;
  list<BST*> *tailbsts = nullptr;

  //resetting the visited array
  for (int i=0; i<numNodes; i++){
    visited[i] = 0;
  }
  //calling DFS function for every node if the node is unvisited yet
  for(int i=0; i<numNodes; i++){
    if(visited[i]==0){
      //bst for this dfs
      BST* dfsbst = new BST(-1);
      DFS(i,-1, dfsbst);
      //adding this bst to list of bsts
      if(bsts==nullptr){
        bsts = new list<BST*> (dfsbst);
        tailbsts = bsts;
      }
      else{
        tailbsts->next = new list<BST*> (dfsbst);
        tailbsts->next->prev = tailbsts;
        tailbsts = tailbsts->next;
      }
      //every dfs call means a connected component
      numConComp++;
    }
  }
  //printing bsts
  list<BST*>* curr=bsts;
  while(curr !=nullptr){
    curr->object->printBinaryTree(curr->object->root, "", false, &graphFile);
    curr = curr->next;
  }

  cout<<"Number of Connected Components: "<<numConComp<<endl;
  return;
}

void Graph::DFS(int v, int parent, BST* dfsbst){  //v is index of graph node, parent is index of parent's garph node in tree of dfs (which we haven't constructed in this code)
  //time of arrival 
  t++;
  nodes[v].time = t;
  //visited of this node
  visited[v] ++;
  //if first visit, define parent
  if(visited[v]==1){
    nodes[v].insertParent(&nodes[parent]);
  }
  //for each adjacent node
  list<Node*> *curr = nodes[v].adjacency;
  while(curr!=nullptr){
    //if unvisited and not a parent call dfs
    if((visited[curr->object->value-1] == 0) && (!nodes[v].isParent(nodes[(curr->object->value-1)])) && ((curr->object->value-1)!=parent)){
      DFS(curr->object->value-1, v,dfsbst);
    }
    //if visited 1 and not parent call dfs and update incircle
    if((visited[curr->object->value-1] == 1) && (!nodes[v].isParent(nodes[(curr->object->value-1)])) && ((curr->object->value-1)!=parent)){
      DFS(curr->object->value-1, v,dfsbst);
      if(nodes[v].time > curr->object->time){
        iscircle[v] = true;
        iscircle[curr->object->value-1] = true;
        Node* currprnt = &nodes[nodes[v].parents->object->value-1];
        while(currprnt->value != curr->object->value){
          iscircle[currprnt->value-1] = true;
          if(currprnt->parents == nullptr) break;
          currprnt = currprnt->parents->object;
        }
        iscircle[currprnt->value-1] = true;
      }
      
    }
    // 2 visited and not parent incircle update
    if((visited[curr->object->value-1] == 2) && (!nodes[v].isParent(nodes[(curr->object->value-1)])) && ((curr->object->value-1)!=parent)){
      if(nodes[v].time > curr->object->time){
        iscircle[v] = true;
        iscircle[curr->object->value-1] = true;
        Node* currprnt = &nodes[nodes[v].parents->object->value-1];
        while(currprnt->value != curr->object->value){
          iscircle[currprnt->value-1] = true;
          if(currprnt->parents == nullptr) break;
          currprnt = currprnt->parents->object;
        }
        iscircle[currprnt->value-1] = true;
      }
    }
    curr = curr->next;
  }
  //add it to BST
  if(dfsbst->root->value==-1){
    dfsbst->root->value = v+1;
  }
  //insert v+1 into dfsbst
  else{
    dfsbst->insert(v+1);
  }
  t--;
}

void Graph::printResults() {
  //calculating the number of cyclic components
  int numCyclic=0;
  int numTwice = 0;
  //counting numcyclic and numtwice
  for (int i=0; i<numNodes; i++){
    if(iscircle[i]){
      numCyclic++;
      // cout<<i+1<<" is a cyclic node"<<endl;
    }
    if(visited[i]>1){
      numTwice++;
    }
  }
  //numOnce is total-numTwice
  int numOnce = numNodes-numTwice;
  cout<<"No. of nodes visited once: "<<numOnce<<endl;
  cout<<"No. of nodes visited Twice: "<<numTwice<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<numCyclic<<endl;
  return;
}

#endif

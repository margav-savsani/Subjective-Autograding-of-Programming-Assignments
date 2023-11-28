#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void Graph::modifiedDFS() {
  listOfObjects<BST *> *currBSTNode = all_trees, *prevBSTNode = nullptr;
  int currIndex=0;
  bool visited[numNodes];
  bool visitedEdge[numNodes][numNodes];
  bool inCycle[numNodes];
  int num_visited[numNodes];
  for(int i=0;i<numNodes;i++){
    visited[i]=false;
    inCycle[i]=false;
    num_visited[i]=0;
    for(int j=0;j<numNodes;j++){
      visitedEdge[i][j]=false;
    }
  }
  // loop through each connected component
  while(currIndex<numNodes){
    if(!visited[currIndex]){
      conns++;
      BST *newTree = new BST();
      if(all_trees == nullptr){
        all_trees = new listOfObjects<BST *>(newTree);
        currBSTNode = all_trees;
      }
      else{
        prevBSTNode->next = new listOfObjects<BST *>(newTree);
        currBSTNode = prevBSTNode->next;
      }
      listOfObjects<int> *DFSstack = new listOfObjects<int>(currIndex); // creates a DFS Stack using linked list
      newTree->insert(nodes[currIndex].value);
      while(DFSstack != nullptr){ // main DFS loop
        int head = DFSstack->object;
        if(!visited[head]){
          visited[head]=true;
          num_visited[head]++;
        }
        // newTree->insert(nodes[head].value);
        listOfObjects<Node *> *adj = nodes[head].adjacent;
        // cout<<head<<endl;
        while(adj != nullptr){ // loops through all adjacent vertices
          if(!visited[adj->object->value-1]){ // new vertex, simply added into stack and processed next
            DFSstack->next = new listOfObjects<int>(adj->object->value-1);
            DFSstack->next->prev = DFSstack;
            break;
          }
          else if(num_visited[adj->object->value-1] > 0 && DFSstack->prev != nullptr && DFSstack->prev->object != adj->object->value-1){
            // checks if next vertex is present in DFS Stack
            bool found1=false;
            listOfObjects<int> *prevDFSstack = DFSstack->prev;
            while(prevDFSstack != nullptr){
              if(prevDFSstack->object == adj->object->value-1){
                found1=true;
                break;
              }
              prevDFSstack=prevDFSstack->prev;
            }
            if(found1){
              // checks if current edge is an unvisited edge
              bool found2=false;
              prevDFSstack = DFSstack->prev;
              while(prevDFSstack != nullptr){
                if((prevDFSstack->object == adj->object->value-1 && prevDFSstack->next->object == head) || (prevDFSstack->object == head && prevDFSstack->next->object == adj->object->value-1)){
                  found2=true;
                  break;
                }
                prevDFSstack=prevDFSstack->prev;
              }
              if(!found2){ // cycle detected, all vertices between the two vertices belong to it, and the vertex is added into DFS stack again
                inCycle[adj->object->value-1]=true;
                prevDFSstack = DFSstack;
                while(prevDFSstack->object != adj->object->value-1){
                  inCycle[prevDFSstack->object] = true;
                  prevDFSstack=prevDFSstack->prev;
                }
                if(num_visited[adj->object->value-1] == 1){
                  // cout<<"aay "<<head+1<<" "<<adj->object->value<<endl;
                  num_visited[adj->object->value-1]++;
                  DFSstack->next = new listOfObjects<int>(adj->object->value-1);
                  DFSstack->next->prev = DFSstack;
                  break;
                }
              }
            }
          }
          adj = adj->next;
        }
        if(DFSstack->next != nullptr){
          // cout<<head+1<<endl;
          newTree->insert(nodes[DFSstack->next->object].value);
          DFSstack = DFSstack->next;
        }
        else{
          listOfObjects<int> *temp = DFSstack;
          DFSstack = DFSstack->prev;
          delete temp;
          if(DFSstack != nullptr) DFSstack->next = nullptr;
        }
      }
      prevBSTNode = currBSTNode;
      currBSTNode = currBSTNode->next;
    }
    currIndex++;
  }
  for(int i=0;i<numNodes;i++){ // collecting results
    if(num_visited[i]==1) nodes_once++;
    else if(num_visited[i]==2) nodes_twice++;
    if(inCycle[i]) nodes_cycle++;
  }
  return;
}

void Graph::printResults() {
  cout<<"No. of connected components: "<<conns<<endl;
  cout<<"No. of nodes visited once: "<<nodes_once<<endl;
  cout<<"No. of nodes visited twice: "<<nodes_twice<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<nodes_cycle<<endl;
  // loop through all trees
  listOfObjects<BST *> *currBSTNode = all_trees;
  while(currBSTNode != nullptr){
    cout<<endl;
    currBSTNode->object->printBinaryTree(currBSTNode->object->root,"",1);
    currBSTNode=currBSTNode->next;
  }
  return;
}

#endif

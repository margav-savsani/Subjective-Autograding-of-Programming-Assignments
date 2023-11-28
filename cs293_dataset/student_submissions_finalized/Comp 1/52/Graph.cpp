#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif



void Graph::DFSRecurse(int v, BST* tree){
  visited[v]++;
  tree->insert(v+1);
  listOfObjects<Node*>* curr = nodes[v].adjacencyList;
  while (curr != nullptr){
    if(visited[curr->object->value-1] < 2){
      bool blocked = 0;
      listOfObjects<Node*>* c = nodes[v].blockList;
      while(c!= nullptr){
        if(c->object == curr->object){
          blocked = 1;
          break;
        }
        c = c->next;
      }
      if(!blocked){
        Node* p = &nodes[v];
        nodes[curr->object->value-1].insert_block(p);
        DFSRecurse(curr->object->value-1, tree);
        nodes[v].insert_block(curr->object);
      }
    }
    curr = curr->next;
  }

  
}


void Graph::modifiedDFS() {
  for (int i = 0; i < numNodes; i++){
    visited[i] = 0;
  }

  for (int i = 0; i < numNodes; i++){
    if(visited[i] != 0) continue;

    numConnected++;

    listOfObjects<BST*>* t = new listOfObjects<BST*>(new BST);
    t->next = trees;
    trees = t;
    
    DFSRecurse(i, trees->object);
  }
  
  return;
}

void Graph::printResults() {
  int once = 0;
  int twice = 0;
  for (int i = 0; i < numNodes; i++)
  {
    if(visited[i] == 1) once++;
    else if(visited[i] == 2) twice++;
  }
  
  cout << "No. of connected components: " << numConnected << endl;
  cout << "No. of nodes visited once: " << once << endl;
  cout << "No. of nodes visited twice: " << twice << endl;
  cout << "No. of nodes that are present in a cycle: " << twice << endl;

  listOfObjects<BST*>* curr = trees;
  while(curr!= nullptr){
    cout << endl;
    curr->object->printBinaryTree(curr->object->root, "", 0);
    cout << endl;
    curr = curr->next;
  }
  
  return;
}

#endif

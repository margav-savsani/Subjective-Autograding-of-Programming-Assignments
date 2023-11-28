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
  visited = new int[numNodes];

  for(int i = 0; i < numNodes; i++) visited[i] = 0;
  for(int i = 0; i < numNodes; i++){
    if(visited[i] == 1) continue;

    BST* tree = new BST;
    Node* curr = nodes->adj.get_value_at_index(i);
    NewVector<Node*> Stack;
    Stack.push_back(curr);
    while(Stack.vector_size() != 0){
      int val = Stack.return_max()->value;
      int store = val-1;
      if(nodes->adj.get_value_at_index(store)!=nullptr){
        for(int i = 0; i < nodes->adj.get_value_at_index(store)->adj.vector_size(); i++){
          Node* insert = nodes->adj.get_value_at_index(store)->adj.get_value_at_index(i);
          if(nodes->adj.get_value_at_index(store)->adj.get_value_at_index(i)->value != val){
            if(visited[i]!=2){
              Stack.push_back(insert);
            }
          }
        }
      }
      if(visited[store] == 2){
        Stack.pop();
        continue;
      }
      if(visited[store]==1) visited[store] = 2;
      if(visited[store]!=1) visited[store] = 1;
      tree->insert(val);
    }
    main_tree.push_back(tree);
  }
  return;
}

void Graph::printResults() {

  cout << "No. of connected components:" << endl;

  int once_count = 0, twice_count = 0;
  for(int i = 0; i < numNodes; i++){
    if(visited[i] == 1) once_count++;
    if(visited[i] == 2) twice_count++;
  }
  cout << "No. of nodes visited once:" << once_count << endl;
  cout << "No. of nodes visited twice:" << twice_count << endl;
  cout << "Each BST that has been generated using the printBST function provided" << endl;
  for(int i = 0; i < main_tree.vector_size(); i++){
    main_tree.get_value_at_index(i)->printBST("");
  }
  return;
}
#endif
#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

//*********************GRAPH***************************//
BST* new_BST = new BST();
// created a new BST for printig
void Graph::DFS(int index){

  new_BST->insert(index+1);
  // inserting values in BST
  nodes[index].visit ++;
  // incrementing visit by 1
  for(int i = 0; i < nodes[index].adj_nodes.size(); i++){
    int curr = nodes[index].adj_nodes[i];
    // curr index of the node
    if(nodes[curr].visit != 2 && parent_list[index].parent1 != curr && parent_list[index].parent2 != curr){
      // have to visit if it its parent1 and parent2 not equal to curr
      parent_list[curr].insert(index);
      // inserting parent for curr node
      DFS(curr);
    }
  }
  return;
}

void Graph::modifiedDFS() {
  int no_of_nodes = numNodes; // no_of_nodes
  int no_of_edges = numEdges; // no_of_edges
  for(int i =0; i < numNodes; i++){
    if(nodes[i].visit == 0){
      DFS(i); // recursively calling DFS
      cout << "BST component " << connected+1 << endl;
      new_BST->printBST(" "); //print the BST
      new_BST = new BST(); // now creating new BST() for BST..
      connected ++; 
    }
  }
  
  for(int i = 0; i < numNodes; i++){
    if(nodes[i].visit == 1){
      visited_once ++; // to get the visited_once
    }
    if(nodes[i].visit == 2){
      visited_twice ++; // to get the visited_twice
    }
  }
  cycles(); // calling to get the no. of 
  return;
}

void Graph::cycles(){
  // recursively removing all the nodes which are degree 1
  // in order to end the recursive call 
  int* sum1 = new int[numNodes]; // initialized for sum1 === no. of adjacent nodes which are present after removing
  for(int i =0; i < numNodes; i++){sum1[i] = 0;}  
  for(int i = 0; i < nodes_in_cycle.size(); i++){
    int curr = nodes_in_cycle[i];
    if(nodes_bool[curr]){
    for(int j = 0; j < nodes[curr].adj_nodes.size(); j++){
      for(int k = 0; k < nodes_in_cycle.size(); k++){
        if(nodes_bool[k]){if(nodes[curr].adj_nodes[j] == nodes_in_cycle[k]){sum1[i] ++;}}
      }// incrementing sum1[i] to get no. of adjacency list.
    }
    }
  }
  for(int i = 0; i < numNodes; i++ ){
    if(nodes_bool[i]){
      if(sum1[i] == 1 or sum1[i] == 0){
        nodes_bool[i] = false; // deleting the degree 1 nodes in the total nodes  
      }
    }
  }

  int* sum2 = new int[numNodes]; // initialized for sum1 === no. of adjacent nodes which are present after removing
  for(int i =0; i < numNodes; i++){sum2[i] = 0;}
  for(int i = 0; i < numNodes; i++){
    int curr = nodes_in_cycle[i];
    if(nodes_bool[curr]){
    for(int j = 0; j < nodes[curr].adj_nodes.size(); j++){
      for(int k = 0; k < numNodes; k++){
        if(nodes_bool[k]){if(nodes[curr].adj_nodes[j] == nodes_in_cycle[k]){sum2[i] ++;}}
      }// incrementing sum1[i] to get no. of adjacency list.
    }
    }
  }
  // in order to stop the recursive call checking total1 and total2 
  // if they are equal stop the recursive call and set the no_of_nodes_in_cycle
  int total1 = 0; int total2 = 0; 
  for(int i =0; i < numNodes; i++){
    total1 += sum1[i]; total2 += sum2[i];
  }
  if(total1 != total2){
    cycles(); // recursive calling if both are not equal
  }
  else{
    for(int i =0; i < numNodes; i++){
      if(nodes_bool[i]){no_of_nodes_in_cycle ++;} // setting no_of_nodes_in_cycle
    }
  }
}

void Graph::printResults() {
  cout << "no of nodes in cycles = " << no_of_nodes_in_cycle << endl;
  cout << "no of connected components = " << connected << endl;
  cout << "visited once  = " << visited_once << endl;
  cout << "visited twice = " << visited_twice << endl;
}

#endif

#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

#include <cassert>
#include <cmath>

//print function from tree labs
void printBinaryTree(TreeNode<int> *root, const string& prefix, bool isLeft)
{
  if(root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << root->obj << endl;
    cout << endl;
    auto curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

void Graph::DFS(int node, int* visited, my_stack<int>* stack, BST<int>* tree){    //main DFS function, the other one is used as a wrapper
  if(visited[node] >= 2){  //security check
    assert(visited[node] == 2);
    return;
  }

  visited[node]++;   //node is being visited
  tree->insert(nodes[node].value); //node value is inserted into the tree
  
  if(nodes[node].stacknum != 0){  //the number of times a node is present in the stack at the given point in time
    auto trav1 = stack->tail;        //traverse to get the contiguous segment A.....A from the path stack, which contains the cyclic component
    while(trav1->object != node && trav1 != nullptr){
      nodes[trav1->object].incycle = true;
      trav1 = trav1->prev;
    }
  }
  stack->insert(node);   //insert the node in the artificial stack
  nodes[node].stacknum++;   //node in stack, so its appearances in the stack increases

  auto trav = nodes[node].adj;
  while(trav != nullptr){    //traverse through the adjacency list of the current node
    if(!(nodes[node].isParent(trav->object))){   //check the node only if it not a parent of the current node. 
      if(visited[trav->object] != 2){   //if node hasn't been visited twice, one parent position is still vacant
        assert(visited[trav->object] == 0 || visited[trav->object] == 1);  //security check
        nodes[trav->object].parents->insert(node);  //make parent 
        DFS(trav->object, visited, stack, tree);   //perform DFS on the new node
      }
      else{    //upcoming node has already been visited twice
        if(nodes[trav->object].stacknum != 0){   //if node is already on the stack, calculate the of contiguous segment
          auto trav1 = stack->tail;
          while(trav1->object != trav->object && trav1 != nullptr){
            nodes[trav1->object].incycle = true;   //everything in the contiguous cycle is a part of a cycle
            trav1 = trav1->prev;
          }
        }
      }
    }
    trav = trav->next;
  }
  stack->pop();   //departing from the node
  nodes[node].stacknum--;   //decrease number of appearances in the stack
}


// Add code as appropriate for your implementation
void Graph::modifiedDFS() {   //this acts as a wrapper function to DFS function. Check connected components and runs DFS on nodes that haven t been visited after each DFS
  int* visited = new int[numNodes];
  my_stack<BST<int>*>* trees = new my_stack<BST<int>*>;
  for(int i = 0; i < numNodes; i++){
    visited[i] = 0;
  }
  int curr_comp = 0;   //index related to the current component
  int first_non = 0;    //the first node in the array that has not been visited (will be updated after each DFS)
  
  while(first_non < numNodes){   //1 iteration = 1 DFS = 1 connected component
    
    curr_comp++;
    BST<int>* tree = new BST<int>;  //new tree each time
    my_stack<int>* stack = new my_stack<int>;
    stack->insert(first_non);   //

    DFS(first_non, visited, stack, tree);  //perform DFS on the first non visited node
    
    auto temp123 = first_non;    
    bool all_vis = true;
    for(int i = temp123; i < numNodes; i++){   //update the first non visited node
      if(visited[i] == 0){
        first_non = i;
        all_vis = false;
        break;
      }
    }
    if(all_vis) {first_non = numNodes;}   //if all are visited, time to break out of loop
    delete stack; 
    trees->insert(tree);
  }
  comps = curr_comp;
  vis = visited;
  trees_gr = trees;  
}

void Graph::printResults() {   //prints the required entities
  std::cout << "No. of connected components: " << comps << endl;
  int once = 0;
  int twice = 0;
  for(int i = 0; i < numNodes; i++){
    if(vis[i] == 1){
      once++;
    }
    else if(vis[i] == 2){
      twice++;
    }
  }
  std::cout << "No. of nodes visited once: " << once << endl;
  std::cout << "No. of nodes visited twice: " << twice << endl;
  int cycnodes = 0;
  for(int i = 0; i < numNodes; i++){
    if(nodes[i].incycle == true){
      cycnodes++;
    }
  }
  std::cout << "No. of nodes that are present in a cycle: " << cycnodes << endl;
  auto trav = trees_gr->list;
  while(trav != nullptr){
    printBinaryTree(trav->object->root, "", false);
    trav = trav->next;
  }
}
#endif

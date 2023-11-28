#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void printFlag(int flag_num){
  cout<<"flag"<<flag_num<<endl;
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  memset(this->visited_once, 0, sizeof(bool)*this->numNodes);memset(this->visited_twice, 0, sizeof(bool)*this->numNodes);

  //Initialising the variables used in the recursive algorithms that follows
  LinkedListNode<BST<int>*> *bst_container = this->dfs_bsts->getHead();
  while(bst_container != nullptr){
    bst_container->data->clear();
    delete bst_container->data;
    bst_container->data = nullptr;
    bst_container = bst_container->next;
  }
  this->dfs_bsts->clear();

  // Choosing node with value 1 as the first node to perform DFS on
  Node *next_start = &(this->nodes[0]);
  int visited_itr = 0;
  while(next_start != nullptr){
    BST<int> *this_bst = new BST<int>();
    this->dfs_bsts->insert(this_bst);
    this->modifiedDFS_perComponent(next_start, nullptr, visited_once, visited_twice, this_bst);

    // Find the next unvisited node
    next_start = nullptr;
    for(; visited_itr < this->numNodes; visited_itr++){
      if(!visited_once[visited_itr]){
        next_start = &(this->nodes[visited_itr]);
        break;
      }
    }
  }

  return;
}

void Graph::modifiedDFS_perComponent(Node* cur, Node* prev, bool *visited, bool *revisited, BST<int>* dfs_bst){
  // Reinforcing the condition that a twice-visited node should not be visited the third time
  if(revisited[(cur->value)-1]) return;
  if(visited[(cur->value)-1]) revisited[(cur->value) - 1] = true;
  else visited[(cur->value)-1] = true;

  // Once an edge is chosen and used to travel, fix its direction for the rest of the DFS procedure to avoid the backtrack problem.
  if(prev != nullptr){
    LinkedListNode<Node*> *prev_in_adj = cur->adj->findOne([val = prev->value](LinkedListNode<Node*>* to_check){return to_check->data->value == val;});
    if(prev_in_adj != nullptr) prev_in_adj->consider = false;
  }

  // Record the visit in the BST
  dfs_bst->insert(cur->value, [](int& d1, int& d2) -> bool {return d1<d2;});

  // Traverse the adjacency list
  LinkedListNode<Node*> *adj = cur->adj->getHead(); 
  while(adj != nullptr){
    // Don't consider marked edges, marked by certain conditions
    if(!(adj->consider)){
      adj = adj->next;
      continue;
    }
    
    this->modifiedDFS_perComponent(adj->data, cur, visited, revisited, dfs_bst);
    // If the node just considered has no other nodes to travel to anymore, mark the edge reaching it as one to not be considered again
    // This avoids revisiting of the branches emanating from the branches
    if(adj->data->adj->findOne([](LinkedListNode<Node*> *to_check){
      return to_check->consider;
    }) == nullptr) adj->consider = false;
    adj = adj->next;
  }

  return;
}

void Graph::printResults() {
  // Just print out the results
  LinkedListNode<BST<int>*> *cur = this->dfs_bsts->getHead();
  int count=0;
  while(cur != nullptr){count++;cur=cur->next;}
  cout << "No. of connected components: "<<count<<endl;
  
  count = 0;
  for(int i=0; i<this->numNodes; i++){
    if(this->visited_twice[i]) {
      count++;
    }
  }

  cout << "No. of nodes visited once: "<< (this->numNodes - count) << endl;
  cout << "No. of nodes visited twice: "<< count <<endl;
  cout << "No. of nodes present in a cycle: "<< count <<endl;

  cur = this->dfs_bsts->getHead();
  while(cur != nullptr){
    cur->data->printBST();
    cout<<endl;
    cur = cur->next;
  }
  return;
}

#endif
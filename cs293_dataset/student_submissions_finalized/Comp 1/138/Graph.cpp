#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// function that executes the modified DFS
void Graph::mod_DFS(Node* parent, Node* child,BST* bst){

  // child is not visited in this case
  if(parent!=NULL){
    if(child->count == 2 || parent->p1 == child->value || parent->p2 == child->value ){
      // cout<<"exited"<<endl;
      return;
    }
  }

  // cout<<"aa"<<str<<endl;

  // str = str + to_string(child->value - 1);

  // storing the elements in a list
  node_l* to_be = new node_l(child->value-1);
  //
  if(start==NULL){
    start = to_be;
  }
  else{
    //start is the ending element
    start->next = to_be;
    to_be->prev = start;
    start = start->next;
  }

  // cout<<"bb"<<str<<endl;
  bst->insert(child->value);
  // setting child as connected
  child->connected = 1;

  // if child is visited
  // insert in BST here

  //incrementing number of times visited
  child->count++;

  //setting parent child relationship
  if(parent!=NULL){
    if(child->p1 != 0){
      child->p2 = parent->value;
    }
    else{
      child->p2 = parent->value;
    }
  }
  //setting instack for checking for cycle
  if(child->instack != 2){
    child->instack++;
  }

  // checking if in cycle
  if(child->instack == 2){

    node_l * traversal = start->prev;
    while(traversal->value != child->value - 1){
      nodes[traversal->value].incycle = 1;
      traversal = traversal -> prev;
    }
    nodes[traversal->value].incycle = 1;
  }

  // Node* parent_ptr = child;
  Node* child_ptr = child->next;

  while(child_ptr!=NULL){
    // cout<<child->value<<endl;
    // cout<<child_ptr->ref->value<<endl<<endl;
    // call to the function
    mod_DFS(child, child_ptr->ref,bst);
    // parent_ptr = child_ptr;
    child_ptr = child_ptr->next;
  }
  child->instack--;
  // if(start!=NULL){}
  // popping element out of the stack
  start = start->prev;
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  int i = 0;
  while( i<numNodes ){
    // doing DFS for all the connected components
    if(nodes[i].connected==0){
      // cout<<"uu"<<nodes[i].connected<<endl;
      // initialising BST
      BST *bst = new BST;
      if(arr==NULL){
        arr=bst;
      }

      // traversing the array storing BST
      else{
        BST * traver = arr;
        while(traver->next!=NULL){
          traver = traver->next;
        }
        traver->next = bst;
      }
      //incrementing num_connected
      num_connected++;
      mod_DFS(NULL, &nodes[i],bst);
    }
    i++;
  }
  return;
}

void Graph::printResults() {
  // printing important information
  cout<<"No. of connected components: "<<num_connected<<endl;
  int once = 0, twice = 0, incycle=0;

  for(int i=0;i<numNodes;i++){
    if(nodes[i].count == 1){
      once++;
    }
    if(nodes[i].count == 2){
      twice++;
    }
    if(nodes[i].incycle == 1){
      incycle++;
    }
  }

  cout<<"No. of nodes visited once: "<<once<<endl;

  cout<<"No. of nodes visited twice: "<<twice<<endl;

  cout<<"No. of nodes that are present in a cycle: "<<incycle<<endl;
  // cout<<str<<endl;

  // printing all BST trees
  BST * traverse;
  traverse = arr;
  while(traverse!=NULL){
    traverse->printBST("",false);
    cout<<endl;
    traverse=traverse->next;
  }


  return;
}

#endif

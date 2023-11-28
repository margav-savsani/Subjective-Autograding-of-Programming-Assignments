#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// insert a node with the given value
void BST::insert(int value){
  Node* temp1 = root;
  Node* temp2 = nullptr;
  while(temp1 != nullptr){                                    // find the position where the node should be iserted 
    temp2 = temp1;
    if(value < temp1->value) temp1 = temp1->left;
    else temp1 = temp1->right;
  }
  
  if(temp2 == nullptr){
    root = new Node(value);    
  } else{                                                     // inset the node
    if(value < temp2->value){
      temp2->left = new Node(value);
      temp2->left->parent = temp2;
    } else{
      temp2->right = new Node(value);
      temp2->right->parent = temp2;
    }
  }
}

void printBST(const string& prefix, bool isLeft, Node* r_node) // prints a tree with root as the given node
{
  if( r_node != nullptr )
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__" );

    // print the value of the node
    cout << r_node->value << endl;
    Node *curr = r_node;
    r_node = r_node->left;
    // enter the next tree level - left and right branch
    printBST( prefix + (isLeft ? "│   " : "    "), true,r_node);
    r_node = curr->right;
    printBST( prefix + (isLeft ? "│   " : "    "), false,r_node);
    r_node = curr;
  }
}

// return the arrival time of the deepest back edge
int Graph::DFS(Node* node,BST* tree){
  int node_index = node->value-1;                                    // index of the current node 
  arrv[node_index] = min(counter,arrv[node_index]); counter++;       // updating arrival time of the node
  int dbe = arrv[node_index];                                        // initially, let deepest back edge node be the node it self
  if(visited[node_index] == 0) ones++;                               // if the node is visited for the first time, increase ones
  else if(visited[node_index] == 1){ones--;twice++;}                 // if the node is visited for the second time increase twos and decrease ones
  visited[node_index]++;                                             // increase the visit freq of the node
  list_node* temp = node->adj_list->adj_nodes;                       // list of all adjacent nodes of the node
  while(temp != nullptr){ 
    int vis_val = visited[temp->node->value-1];                      // visited value of the adjacent node
    int vis_node_val = temp->node->value;                            // value of the adjacnet node 
    if(!(parents[node_index][0] == vis_node_val || parents[node_index][1] == vis_node_val)) {      // check whether the adjcaent node is not a parent of the node
      if( vis_val != 2){                                             // if the node is not visited twice
        parents[vis_node_val-1][vis_val] = node->value;              // add the node as a parent to the adjacent node
        tree->insert(vis_node_val);                                  // insert the node value into the tree
        int a_t = DFS(temp->node,tree);                              // find the arrival time of the deepest back edge node from the adjacent node 
        if(a_t == dbe && coun_cycl[node_index] == 0) {n_cycl++; coun_cycl[node_index] =1;} // if the deepest back edge ends upon the the node, then the node is in a cycle           
        dbe = min(a_t,dbe);                                          // update the dbe time 
      } else{
        dbe = min(dbe,arrv[vis_node_val-1]);                         // check with twice visited vertices also
      }
    }
    temp = temp->next;
  }
  if(dbe < arrv[node_index] && coun_cycl[node_index] == 0) {n_cycl++; coun_cycl[node_index] =1;} // if the dbe is less than the arrival time of node, then there is a cylce from the node
  return dbe;                                                        // return dbe
}

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  int nv_ind = 0;                                             // index of the node which is not visited 
  while(nv_ind < numNodes){
    BST* tree = new BST(&nodes[nv_ind]);                      // creates a tree with the the given node as root
    DFS(&nodes[nv_ind],tree);                                 // runs the dfs and insets the values in the tree
    root_list->add(&nodes[nv_ind]);                           // add the node to the root_list
    n_comp++;                                                 // increase the component count
    int i=nv_ind;                                             // find the next unvisited component
    while(i<numNodes){
      if(visited[i] == 0) break;
      i++;
    }
    nv_ind = i;                                               // update the value of nv_ind
  }
  return;
}

void Graph::printResults() {
  cout<<"No. of connected components: "<<n_comp<<endl;
  cout<<"No. of nodes visited once: "<<ones<<endl;
  cout<<"No. of nodes visited twice: "<<twice<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<n_cycl<<endl;
  list_node* temp = root_list->adj_nodes;                     // print all the BSTs
  while(temp != nullptr){
    cout<<endl;
    printBST("",false,temp->node);       
    temp = temp->next;
  }
  return;
}

#endif

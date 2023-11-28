#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation


void Graph::modifiedDFS() {   // iterative function to perform modified DFS

  for (int i = 0; i < numNodes; i++){   // looping through all the elements and checking whether they are visited
    if (parent1[i] != -1){      // if already visited, continue
      continue;
    }
    // else, do modified DFS 
    list<BST> * B = new list<BST>;    // linked list of BST, to store the connected components
    B->next = BSTlist;
    BSTlist = B;
    num_connected++;        // increasing the number of connected components

    parent1[i] = -2;        // parent of a root of BST tree is being set to -2, unvisited => parent = -1 
    Node node = nodes[i];
    list<int> * l = node.L;
    /* inserting to the stack S, S stores both the node and some additional information, such as 
      whether the progress through the adjacency list.
    */
    S->insert(i, l);        
    B->val.insert(i+1);   // inserting into the BST
    int j = i;
    while (!S->isempty()){    // loop till the Stack gets empty
      l = S->next[S->n-1];    // the next adjacent element
      j = S->node[S->n-1];    // number of the current node
      // cout << "0 : " << j+1 << endl;
      if (l == nullptr){      
        S->pop();       // if no more adjacent elements, pop from the Stack, ie, backtrack
      }
      else if (parent1[l->val] == -1){    // if unvisited insert to the Stack
        int k = l->val;
        // cout << "1 : " << k+1 << endl;
        l = l->next;    // updating the 'to be visited' adjacent nodes 
        parent1[k] = j;     // setting the parent of node k to node j
        S->next[S->n-1] = l;
        S->insert(k, nodes[k].L);     // inserting in the Stack
        B->val.insert(k+1);
      }
      else if ((parent2[l->val] == -1) && (parent1[j] != l->val) && (parent2[j] != l->val)){    // second insertion
        if (S->instack(l->val) == 0){   // if not in the Stack
          int k = l->val;
          // cout << "2 : " << k+1 << endl;
          l = l->next;
          parent2[k] = j;
          S->next[S->n-1] = l;
          S->insert(k, nodes[k].L);
          B->val.insert(k+1);
          visit2++;
        }
        else if (S->instack(l->val) == 1){    // if element already in the Stack => cycle
          int k = l->val;
          // cout << "3 : " << k+1 << endl;
          l = l->next;
          parent2[k] = j;
          S->next[S->n-1] = l;
          S->insert(k, nodes[k].L);
          B->val.insert(k+1);
          visit2++;
          for (int c = S->first[k]; c < S->second[k]; c++){   // looping through the Stack to find the nodes present in a cycle
            if (!is_incycle[S->node[c]]){
              is_incycle[S->node[c]] = 1;
              cycles++;     // updating the number of cycles
            }
          }
        }
        else {
          if (S->instack(l->val) >= 1){
            int k = l->val;
            // cout << "4 : " << k+1 << endl;
            l = l->next;
            S->next[S->n-1] = l;
            for (int c = S->first[k]; c < S->n; c++){     // looping through the Stack to find the nodes present in a cycle
              if (!is_incycle[S->node[c]]){
                is_incycle[S->node[c]] = 1;
                cycles++;
              }
            }
          }
          else {
            // cout << "hello1 : " << l->val+1 << endl;
            l = l->next;
            S->next[S->n-1] = l;
          }
        }
      }
      else {
        if ((S->instack(l->val) >= 1) && (parent1[j] != l->val) && (parent2[j] != l->val)){
            int k = l->val;
            // cout << "5 : " << k+1 << endl;
            l = l->next;
            S->next[S->n-1] = l;
            for (int c = S->first[k]; c < S->n; c++){     // looping through the Stack to find the nodes present in a cycle
              if (!is_incycle[S->node[c]]){
                is_incycle[S->node[c]] = 1;
                cycles++;
              }
            }
          }
        else {
          // cout << "hello0 : " << l->val << endl;
          l = l->next;
          S->next[S->n-1] = l;
        }
      }
    }
  }
  return;
}

void Graph::printResults() {    // printing the results in the required format
  modifiedDFS();
  cout << "=========================================" << endl;
  cout << "Number of connected components : " << num_connected << endl;
  cout << "Number of nodes visited once : " << numNodes-visit2 << endl;
  cout << "Number of nodes visited twice : " << visit2 << endl;
  cout << "Number of nodes that are present in a cycle : " << cycles << endl;
  cout << "=========================================" << endl;
  list<BST> * B = BSTlist;
  while(B != nullptr){
    B->val.printBST("");
    B = B->next;
    cout << "-----------------------------------------" << endl;
  }
  // for (int i = 0; i < numNodes; i++){
  //   cout << i+1 << " " << is_incycle[i] << endl;
  // }
  return;
}

void Graph::resetVisits(){
  for (int i = 0; i < numNodes; i++){
    parent1[i] = -1;
    parent2[i] = -1;
  }
}

#endif
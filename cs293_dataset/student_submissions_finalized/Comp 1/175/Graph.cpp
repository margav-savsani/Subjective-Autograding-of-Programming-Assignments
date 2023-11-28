#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

void DFS(int visited[], Node nodes[], int node, BST *tree, int ba_tr[], int pt[]){
  visited[node] ++; // increase the visited count
  tree->insert(nodes[node].value); // insert in the tree
  for (int i = 0; i < nodes[node].index; i++){
    if ((visited[nodes[node].adj_list[i] - 1] == 0 || visited[nodes[node].adj_list[i] - 1] == 1) && nodes[node].adj_list[i] - 1 != pt[node] && ba_tr[nodes[node].adj_list[i] - 1] == 0){ // should not be the parent node, should not be visited more than 2 times, it should be a node from which we haven't backtracked before
      if (pt[nodes[node].adj_list[i] - 1] == -1){ // populating the parent array if not yet done for this node
        pt[nodes[node].adj_list[i] - 1] = node;
      }
      DFS(visited, nodes, nodes[node].adj_list[i] - 1, tree, ba_tr, pt); // calling the DFS function recursively
      ba_tr[nodes[node].adj_list[i] - 1] = 1; // now we have backtracked from this node
    }
  }
  return;
}

void Graph::modifiedDFS() { // the 'main' function
  int index = 0;
  while (index != numNodes){ // traversing the entire array only once to determine the number of connected components and calling the DFS function appropriately
    if (visited[index] != 0) index ++;
    else{
      conn_comp ++;
      BST *tree = new BST();
      list<BST *> *copy = trees, *head = nullptr; // incrementing the BST linked list
      while(copy != nullptr){
        head = copy;
        copy = copy->next;
      }
      head->value = tree;
      head->next = new list<BST *>();
      DFS(visited, nodes, index, tree, ba_tr, pt); // calling a self-created function
    }
  }
  return;
}

void Graph::printResults() { // printing the results
  cout << "No. of connected components: " << conn_comp << endl;
  int one = 0, two = 0; // finding out how many vertices were visited once or twice
  for (int i = 0; i < numNodes; i++){
    if (visited[i] == 1) one ++;
    else if (visited[i] == 2) two ++;
  }
  cout << "No. of nodes visited once: " << one << endl;
  cout << "No. of nodes visited twice: " << two << endl;
  cout << "No. of nodes that are present in a cycle: " << two << endl;
  cout << "The trees formed are as follows: " << endl;
  list<BST *> *copy = trees;
  int id = 1;
  while (copy != nullptr && copy->value != nullptr){ // printing the trees
    cout << "Tree " << id++ << endl;
    copy->value->printBST("");
    cout << "====================" << endl;
    copy = copy->next;
  }
}

#endif

#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

/*
1. Allocate memory whatever needed inside the constructor itself (left = right = null doesn't req but still) 
2. Implement insert
3. Implement printBST() -> take code from previous labs
*/

BST::BST() {

  root = new BSTNode(0);

}

BST::BST(int start) {

  root = new BSTNode(start);

}

bool BST::BSTLessThan(BSTNode* node1, BSTNode* node2) {
  return node1->value < node2->value;
}

void BST::insert(int x) {

  BSTNode* currNode = root; // this assignment preserves pointers.  
  
  while (currNode != nullptr) {
    if (x < currNode->value) {
      if (currNode->left == nullptr) {
        currNode->left = new BSTNode(x);
        return;
      }
      else {
        currNode = currNode->left;
      }
    }

    else {
      if (currNode->right == nullptr) {
        currNode->right = new BSTNode(x);
        return;
      }
      else {
        currNode = currNode->right;
      }
    }

  }

}

void BST::printBST() {

  printBinaryTree(root, "", false); 
  return;

}

// Do not visit the parent : taken care of in add parent and check parent.
void Graph::DFSvisit(int idx) {
  nodes[idx].count++;
  for (int i = 0; i < nodes[idx].curcount; i++) {
    if (!nodes[idx].checkparent(nodes[idx].adjacency[i].value - 1)){
      if (nodes[nodes[idx].adjacency[i].value-1].count < 2) {
        nodes[nodes[idx].adjacency[i].value-1].addparent(idx);
        trees[treecount].insert(nodes[idx].adjacency[i].value); // inserting the value in BST
        DFSvisit(nodes[idx].adjacency[i].value-1);
      }
    }
  }
}

void Graph::modifiedDFS() {
  for (int i = 0; i < numNodes; i++) {
    assert(nodes[i].count <= 2);
    if (nodes[i].count == 0) {

      trees[treecount].root = new BSTNode(nodes[i].value);
      DFSvisit(nodes[i].value-1);
      treecount++;

    }
  }
}

int Graph::computecycles() {
  /*
  1. Remove the leaves of the graph recursively (n^2 time)
  2. Find the number of nodes left with belongs to cycle = true 
  */

  // traversing the entire nodes and setting any degree 1 stuff cyclic = 0
  // doing this numNodes times

  int pass = 0; 
  while (pass != numNodes) {
    for (int i = 0; i < numNodes; i++) {
      // iterate through all adj nodes, add cyclic ones
      int curcount = 0 ;
      for (int j = 0; j < nodes[i].curcount; j++) {
        if (nodes[nodes[i].adjacency[j].value-1].cyclic == 1) curcount++;
      }
      if (curcount == 1 || curcount == 0) {
        nodes[i].cyclic = 0;
      }
    }
    pass++;
  }

  int count = 0;
  for (int i = 0; i < numNodes; i++) {
    if (nodes[i].cyclic){
      count++;
    
    }
  }

  return count;
}

void Graph::printResults() {

  int onecount = 0, twocount = 0;

  for (int i = 0; i < numNodes; i++) {
    if (nodes[i].count == 1)  onecount++;
    else if (nodes[i].count == 2) twocount++;
  }

  // Computing number of cycles. : same as number of nodes which have been visited twice !

  // printing other information
  cout << "No. of connected components: " << treecount << endl;
  cout << "No. of nodes visited once: " << onecount << endl;
  cout << "No. of nodes visited twice: " << twocount << endl;
  cout << "No. of nodes that are present in a cycle: " << computecycles() << endl;

  // printing BST
  for (int i = 0; i < treecount; i++) {
    trees[i].printBST();
  }
}

void BST::printBinaryTree(BSTNode *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    root->printInfo();
    cout << endl;
    BSTNode *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    return;
  }
}

#endif

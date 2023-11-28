#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <cmath>

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  /*
  1. Insert the object to the "empty" slot. 
  2. Shift the object upward until it reaches the root. 
  3. Update size.
  */

  size += 1;
  int num = size; 
  TreeNode* currNode = root;
  // using the binary representation of the size decide where to go. 
  
  int counter = floor(log(num)/log(2));
  num = num / 2; 
  int bit;
  for (int i = counter; i > 0; i--) {
    bit = num/2;
    if (i == 1) {
      if (bit == 0) currNode->left = new TreeNode();
      if (bit == 1) currNode->right = new TreeNode();
      break;
    }
    if (bit == 0 ) {
      currNode = currNode->left;
    }
    else if (bit == 1) {
      currNode = currNode->right;
    }
  }

  if (bit == 0) currNode->left = obj;
  if (bit == 1) currNode->right = obj; 

  obj.parent = currNode;

  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  
  /*
  1. Remove the root -- NEVER change pointers. only swap objects. 
  2. Bring the greater child upwards.
  3. Shift focus to the next node. 
  */
  
  TreeNode* currNode = root;

  if (root->left->object < root->right->object) {
    root->object = root->right->object;
    currNode = currNode->right;
  }

  else {
    root->object = root->left->object;
    currNode = currNode->left;
  }

  // Now, iterating 

  while (currNode != nullptr) {
    if (currNode->left->object < currNode->right->object) {
      if (currNode->right == nullptr) break;
      swap(currNode->object, currNode->right->object);
      currNode = currNode->right;
    }
    else {
      if (currNode->left == nullptr) break;
      swap(currNode->object, currNode->left->object);
      currNode = currNode->left;
    }
  }

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  const string prefix = "";
  cout << root->object << endl;
  printer(prefix, node->left, true);
  printer(prefix, node->right, false);
  return;
}

template<typename T>
void printer(const string& prefix, TreeNode<T>* root, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printer( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printer( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

  

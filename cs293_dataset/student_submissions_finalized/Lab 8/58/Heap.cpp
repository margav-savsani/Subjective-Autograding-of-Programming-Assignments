#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
// Remember I am just placing a new node,need to shift up that node based on the type of template T
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == nullptr){
    root = new TreeNode(obj);
    return;
  }

  TreeNode<T> *currNode1 = root;int i1=0;
  while(currNode1->left != nullptr){
    currNode1 = currNode1->left;
    i1++;
  }

  TreeNode<T> *currNode2 = root;int i2=0;
  while(currNode2->right != nullptr){
    currNode2 = currNode2->right;
    i2++;
  }

  if(currNode1 == root){
    root->left = new TreeNode(obj);
    root->left->parent = root;
    return;
  }

  if(i1 == i2){
    currNode1->left = new TreeNode(obj);
    currNode1->left->parent = currNode1;
    return;
  }
  // This is the partially filled last level.
  else{
    TreeNode *super = currNode->parent;
    if(super->right == nullptr){
      super->right = new TreeNode(obj);
      super->right->parent = super;
      return;
    }

    else{
      
    }
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

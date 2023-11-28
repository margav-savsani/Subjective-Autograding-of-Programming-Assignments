#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

TreeNode * last(TreeNode root){
  for(+)
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root = NULL) root = TreeNode(obj);
  else {
    TreeNode * l = last(root);
      l->parent;
     l = new TreeNode(obj);
    
    if(l->parent->left == nullptr){
      l->parent->left = new TreeNode(obj);
    }
    if(l->parent->right == nullptr){
      l->parent->right = new TreeNode(obj);
    }
  }
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  root = last(root);
  heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

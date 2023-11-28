#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *treeNode = new TreeNode<T>(obj);
  if (root == nullptr) {
    root = treeNode;
  }
  else{
    if (root->object > treeNode->object){
      
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

  
#endif

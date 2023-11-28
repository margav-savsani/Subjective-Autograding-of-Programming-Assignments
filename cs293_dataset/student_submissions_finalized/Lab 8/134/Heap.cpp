#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){
  TreeNode<T> *currNode = node;
  while(currNode!=NULL){
    if(currNode < currNode->left and currNode->left > currNode->right){
      swap(currNode, currNode->left);
      currNode = currNode->left;
    }
    else if(currNode < currNode->right and currNode->right > currNode->left){
      swap(currNode, currNode->right);
      currNode = currNode->right;
    }
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

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

  

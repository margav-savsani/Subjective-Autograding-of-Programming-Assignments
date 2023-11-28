#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *newNode = new TreeNode<T>(obj);  //creating a new node

  //assuming the heap tree to be leftist
  //traversing the heap to find the empty node where newNode is to be inserted
  TreeNode<T> *currNode = nullptr;
  TreeNode<T> *currChild = root;
  while(currChild != nullptr){
    currNode = currChild;
    //have to implement a height variable to store the height data
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

  

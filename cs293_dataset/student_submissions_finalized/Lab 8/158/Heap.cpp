#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <string.h>

template<typename T>
TreeNode<T>* Heap<T>::CreateLevelOrderSuccessor(TreeNode<T>* node) {
  TreeNode<T>* curr = node;int n = numOfNodes
  for(int currLevelSize=1;;currLevelSize++, currLevelSize*=2){
    if(n - currLevelSize<0)break;
    n = n - currLevelSize;
    
  }

  // Now n  contains number of nodes in the incomplete level.
  // 



  return;
}


template<typename T>
void Heap<T>::insert(T obj) {
  

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

  

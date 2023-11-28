#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include<vector>

template<typename T>
void Heap<T>::insert(T obj) {

  // insert your code here
  TreeNode* x;
  x=new TreeNode(obj);
  if(root==NULL){
    root=*x;
    n++;
    return;
  }
  int k=1,;
  while(n>k){
    k=k*2;
  }
  
  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

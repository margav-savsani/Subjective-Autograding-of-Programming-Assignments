#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
if(root == NULL){
  root =new TreeNode<T>(obj);
  root->level = 0;
  root->imbalance =0;
}

  return;
}
template<typename T>
int get_imbalnce(TreeNode<T>* node){
if(left == NULL && right == NULL){
  return 0;
}
if(left != NULL && right == NULL){
  return 1;
}
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

  

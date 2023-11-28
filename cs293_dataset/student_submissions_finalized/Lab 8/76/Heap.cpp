#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode *t1=obj;
  TreeNode *t2;
  TreeNode *t3;
  if((t1->left!=nullptr)&&(t1->right!=nullptr)){
      t2=t2->left;
      t3=t3->right;
  while(t2->left!=nullptr){
    t2=t2->left
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
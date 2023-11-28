#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert1(T root ,T obj) {
  // insert your code here
  if (root == NULL){
    root->object = obj:
  }
  if (root->left == NULL && root->right == NULL){
    root->left->object = obj;
  }
  if (root->left != NULL && root->right == NULL ){
    root->right->object = obj ;
  }

  return;
}

template<typename T>
void Heap<T>::insert(T obj) {



  // insert your code here
 
  return;
}

/*
template<typename T>
TreeNode Heap<T>::getMin(){
  TreeNode<T> *x;
  TreeNode<T> *y;

}*/

template<typename T>
void Heap<T>::swap(TreeNode<T> *x,TreeNode<T> *y){
  int temp;
  temp = x->object;
  x->object = y->object;
  y->object = temp;
  return ; 

}

template<typename T>
void Heap<T>::delMax() {
 TreeNode<T> *x ; 
 TreeNode<T> *y = root;
 x = getmin();
 y->object = x->object;
 x = nullptr;
  
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

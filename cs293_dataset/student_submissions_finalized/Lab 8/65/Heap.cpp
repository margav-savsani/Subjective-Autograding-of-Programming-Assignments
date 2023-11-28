#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>

TreeNode<T>* Heap<T>::getpos(TreeNode<T> *nodel,TreeNode<T> *noder){
  
  TreeNode<T> *A = nodel;
  if(A->left==nullptr || A->right==nullptr){
    return A;
  }
  return getpos(A->left,A->right);

  else{
    return getpos(A->left);
  }
}
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T>* B = root; 
  TreeNode<T>* A = new TreeNode(obj);
  if(root==nullptr){
    root=A;
  }
  else{

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
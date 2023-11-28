#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template<typename T>
void Heap<T>::Heapify(TreeNode<T>* root) {

}

template<typename T>
TreeNode<T>* nextElement(TreeNode<T>* curr) { 
    if ( curr->parent == nullptr ) return nullptr ;  
    if ( curr == curr->parent->left ) return curr->right ; 
    else return nextElement(curr->parent)->left ; 
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  //change last parent 
  TreeNode<T>* curr = new TreeNode<T>(obj) ; 
  if (root == nullptr)  { root = curr; lastParent = root ;  return ;  }
  
  curr->parent = lastParent ; 
  if ( lastParent->left == nullptr ) lastParent->left = curr ; 
  else lastParent->right == curr ; 
  
  TreeNode<T>* temp = lastParent ; 
  while ( temp->object < curr ) swap(curr->obj,temp->obj) ; 

  while ( lastParent->right != nullptr ) { //both child filed , change lastParent
         TreeNode<T>*  nextElement(last);
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

  

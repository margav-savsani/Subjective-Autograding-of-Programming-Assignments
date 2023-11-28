#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

TreeNode<T>* Heap<T>::findlastNode(){
  
}

void Heap<T>::heapify(TreeNode<T> *root){
  if(root->left == nullptr) return;//base case where only root, no children.
  if(root->left != nullptr && root->right != nullptr){
  if(!(root->object < root->left->object) && !(root->object < root->right->object)){//no need to heapify, already a heap
    return;
  }
  else{
    if(root->left->object < root->right->object){
      T p = root->object;
      root->object=root->right->object;
      root->right->object=p;
      heapify(root->right);
    }
    else{
      T p = root->object;
      root->object=root->left->object;
      root->left->object=p;
      heapify(root->left);
    }
  }
  }
  if(root->right==nullptr){//base case where only root and left node
    if(root->right->object < root->object) return;
    else{
      T p = root->object;
      root->object=root->right->object;
      root->right->object=p;
    }
  }
}

template<typename T>
void Heap<T>::insert(T obj){
  // insert your code here
  T *p=root;
  while(p != nullptr){
    
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

  

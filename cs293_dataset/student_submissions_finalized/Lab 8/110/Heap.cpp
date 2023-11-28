#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode* node=root;
  if(root==nullptr){
    root->object=obj;
    return;
  }
  while (1)
  {
    node=node->left;
    if(node==nullptr){
      node=obj;
      return;
    }
    node=node->parent->right;
    if(node==nullptr){
      node=obj;
      return;
    }
    node=node->parent->left;
  }
  Heapify(node);
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  TreeNode* node = root;
  while (1)
  {
    node=node->left;
    if(node==nullptr){
      root->object=node->parent->object;
      node->parent=nullptr;
      Heapify(node);
      return;
    }
    node=node->parent->right;
    if(node==nullptr){
      root->object=node->parent->left->object;
      node->parent->left=nullptr;
      Heapify(node);
      return;
    }
    node=node->parent->left;
  }
  return;
}
template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  
  return;
}
template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node) {

  // insert your code here
  
  return;
}
  

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> new_node = new TreeNode<T>(obj);
  if(root == NULL) {root = new_node; last_node = root;}
  else if(last_node->parent->right == NULL) {
    last_node->parent->right = new_node;
    new_node->parent = last_node;
    TreeNode<T> temp = last_node->parent;
    while(temp != NULL){
      if(temp->object > new_node->object) break;
      temp = temp->parent;
    }
    last_node = new_node;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  // insert your code here
  TreeNode<T> temp = root;
  //delete root;
  root->object = last_node->object;
  //Heapify(root);  
  return; 
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

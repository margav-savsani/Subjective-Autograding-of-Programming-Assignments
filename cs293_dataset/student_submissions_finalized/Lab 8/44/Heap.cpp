#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


template<typename T>
void heapify(TreeNode<T>* node){
  TreeNode<T>* iterator = node;
  while(iterator!=nullptr && iterator->object > iterator->parent->object){ //swap and terminate when either iterator becomes null while going up, or the iterator object becomes less than the parent object
    TreeNode<T> * temp = iterator;
    iterator->object = iterator->parent->object;
    iterator->parent->object = temp->object;
    iterator = iterator->parent;
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> * currNode = &root;
  TreeNode<T> * trailing_pointer = nullptr;
  while(currNode!=nullptr){
// 
    trailing_pointer = currNode;
    if(currNode->left!=nullptr && currNode->right!=nullptr)
  }
  TreeNode<T> * newNode = new TreeNode<T>(obj);
  currNode = newNode;
  currNode->parent=trailing_pointer;
  if(obj <= trailing_pointer->object) trailing_pointer->left = currNode;
  else trailing_pointer->right = currNode;
  Heapify(currNode);
}

template<typename T>
void Heap<T>::delMax() {
  TreeNode<T> * max_element = & root;
  
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

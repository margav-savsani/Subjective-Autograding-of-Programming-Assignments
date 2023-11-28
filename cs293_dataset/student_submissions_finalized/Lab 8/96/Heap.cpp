#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void setTail(TreeNode<T> *node){
  if(node->parent == nullptr){
    tail = node;
    while(tail->left != nullptr){
      tail = tail->left;
    }
  }
  else if(node->parent->left == node){
    tail = node->parent->right;
    while(tail->left != nullptr){
      tail = tail->left;
    }
  }
  else if(node->parent->right == node){
    setTail(node->parent);
  }
}

template<typename T>
void swap(TreeNode<T> *node1,TreeNode<T> *node2){
  T temp = node1->object;
  node1->object = node2->object;
  node2->object = temp;
}

template<typename T>
void heapify(TreeNode<T> *node){
  if(node->parent != nullptr){
    if(node->parent->object < obj){
      swap(node, node->parent);
      heapify(node->parent);
    }
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == nullptr){
    root = new TreeNode(obj);
    tail = root;
  } 
  else if(tail->left == nullptr){
    tail->left = new TreeNode(obj);
    tail->left->parent = tail;
    heapify(tail->left);
  }
  else{
    tail->right = new TreeNode(obj);
    tail->right->parent = tail;
    heapify(tail->right);
    setTail(tail);
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

  

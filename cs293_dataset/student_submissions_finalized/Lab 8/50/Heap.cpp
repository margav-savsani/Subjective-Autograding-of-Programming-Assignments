#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void swap(TreeNode<T> *a, TreeNode<T> *b){
  T temp = a->object;
  a->object = b->object;
  b->object = temp;
  return;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode *ins;
  ins = new TreeNode(obj);
  if(root == nullptr){
    root = ins;
    last = ins;
    return;
  }
  TreeNode *curr = root;
  while(curr != nullptr){
    if(curr == last){
      curr = root;
      while(curr->left == null){
        curr = curr->left;
      }
      curr->left = ins;
      curr->left->parent = curr;
      last = curr->left;
      curr = last;
      while(curr->object > curr->parent->object){
        swap(curr, curr->parent);
        curr = curr->parent;
        if(curr == root) break;
      }
      return;
    }
    curr = curr->right;
  }
  curr = last;
  if(curr->parent->left == curr){
    curr->parent->right = ins;
    curr->parent->right->parent = curr->parent;
    last = curr->parent->right;
    curr = last;
    while(curr->object > curr->parent->object){
      swap(curr, curr->parent);
      curr = curr->parent;
      if(curr == root) break;
    }
    return;
  }
  while(curr->parent->right == curr){
    curr = curr->parent;
  }
  curr = curr->parent->right;
  while(curr->left != nullptr){
    curr = curr->left;
  }
  curr->left = ins;
  curr->left->parent = curr;
  last = curr->left;
  curr = last;
  while(curr->object > curr->parent->object){
    swap(curr, curr->parent);
    curr = curr->parent;
    if(curr == root) break;
  }
  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  swap(root, last);
  

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

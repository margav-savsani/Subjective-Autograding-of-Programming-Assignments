#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  if(root==nullptr){
    root = new TreeNode<T> (obj);
    last = new TreeNode<T> (obj);
    last = root;
  }
  class TreeNode <T> *iterator = new class TreeNode <T> (obj);
  iterator = last;
  
  //Code to find the next empty place and put the element in it
  while(1){
    if ( iterator->parent == nullptr ){
      while(iterator->left != nullptr ){
        iterator = iterator->left;
      }
      iterator->left = new TreeNode<T> (obj);
      last = iterator->left;
      last->parent = iterator;
      break;
    }
    if ( iterator->parent->right != iterator ){
      iterator=iterator->parent;
      if ( iterator->right == nullptr ){
        iterator->right =  new TreeNode<T> (obj);
        last = iterator->right;
        last->parent = iterator;
      }
      else{
        iterator = iterator->right;
        while(iterator->left!=nullptr){
          iterator = iterator->left;
        }
        iterator->left = new TreeNode<T> (obj);
        last = iterator->left;
        last->parent = iterator;
        break;
      }
    }
    iterator = iterator->parent;
  }

  //Now let's balance the heap
  iterator = last;
  while(iterator->parent!=nullptr && iterator->parent->object < iterator->object ){
    T temp;
    temp = iterator->parent->object;
    iterator->parent->object = iterator->object;
    iterator->object = temp;
    iterator = iterator->parent;
  }

  return;
}

template<typename T>
void Heap<T>::delMax() {
  //If root is nullptr
  if(root == nullptr ){
    return;
  }
  //Only one node in heap
  if ( root->left == nullptr && root->right == nullptr ){
    TreeNode<T> temp = *root;
    root = nullptr;
    return ;
  }
  //Only 2 nodes in heap case
  if ( root ->right == nullptr ){
    TreeNode<T> temp = *root;
    root = root->left;
    root->parent = nullptr;
    return;
  }
  
  //General heap with 3 or more nodes
  TreeNode<T> *iterator = root;
  
  //Starting from switch, its value with the child with greater value, until node of height 0 or 1 is reached
  while(iterator->left!=nullptr && iterator->right!=nullptr){
    T left = iterator->left->object;
    T right = iterator->right->object;
    if ( left < right ){
      T temp = right;
      iterator->right->object = iterator->object;
      iterator->object = temp;
      iterator = iterator->right;
    }
    else {
      T temp = left;
      iterator->left->object = iterator->object;
      iterator->object = temp;
      iterator = iterator->left;
    }
  }

  //Node of height 1
  if ( iterator->left != nullptr ){
    iterator->object = iterator->left->object;
    delete iterator->left;
    iterator->left = nullptr;
  }
  //Node of height 0
  else{
    if ( iterator->parent->left = iterator ){
      iterator = iterator->parent;
      iterator->left = nullptr;
    }
    if ( iterator->parent->right = iterator){
      iterator = iterator->parent;
      iterator->right = nullptr;
    }
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  if (node==nullptr){
    return;
  }
  
  cout << node->object << endl;
  printHeap(node->left);
  printHeap(node->right);
  // insert your code here

  return;
}
#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <bits/stdc++.h>


template<typename T>
int Heap<T>::level_filled_completely(TreeNode<T> *node) {
  if (node==nullptr) {
    return 0;
  }
  return 1+level_filled_completely(node->left)+level_filled_completely(node->right);
}

template<typename T>
void Heap<T>::climb(TreeNode<T> *node) {
  while (node->parent->object<node->object) {
    T temp=node->parent->object;
    node->parent->object=node->object;
    node->object=temp;
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if (root==nullptr) {
    root = new TreeNode(obj);
    return;
  }
  TreeNode<T> *temp=root;
  while (temp!=nullptr){
    if (temp->left==nullptr && temp->right==nullptr) {
      temp->left= new TreeNode(obj);
      climb(temp->left);
      return;
    }
    if (temp->left!=nullptr && temp->right==nullptr) {
      temp->right= new TreeNode(obj);
      climb(temp->right);
      return;
    }
    int l=level_filled_completely(temp->left),r=level_filled_completely(temp->right);
    l=int(log2(l+1));
    r=int(log2(r+1));

    if (l==r) {
      temp=temp->left;
      continue;
    }
    else {
      temp=temp->right;
      continue; 
    }
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

  

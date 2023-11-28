#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T> *root=root;

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::delMax() {
  TreeNode<T> *root=root;
  while(1){
      if(min(root->left->object,root->right->object)==root->left->object){
      root->object=min(root->left->object,root->right->object);
      if(root->left)root=root->left;
    }
    else{
      root->object=min(root->left->object,root->right->object);
      if(root->right)root=root->right;
    }
    while(root!=null){
      root=root->left;
    }
    while(1){root=root->parent;
    if(root->right)continue;}
  }
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  TreeNode<T> *root=root;
  while(root!=null){
    cout<<root->object;
    if(root->left)root=root->left;
    if(root->right) root=root->right;

  }
  // insert your code here

  return;
}

  

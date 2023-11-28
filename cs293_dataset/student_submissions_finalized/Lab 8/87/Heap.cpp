#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T> currNode = root;
  if ( root == nullptr ){
    root = new TreeNode<T>(obj);
  return;
  }
  else {
    if ( currNode->left == nullptr ){
      currNode->left = new TreeNode<T>(obj);
    }
    else if ( currNode->right == nullptr ){
      currNode->right = new TreeNode<T>(obj);
    }
    else ()
  }



  // insert your code here

  return;
}

template<typename T>
void Heap<T>::delMax() {
  TreeNode<T> currNode = root;
  if( root != nullptr ){
    while(currNode != nullptr){
      if ((currNode->left)->object >= (currNode->right)->object){
        TreeNode<T> rgt = currNode->right;
        TreeNode<T> lft = currNode->left;
        currNode = currNode->left;

      }
      else { currNode = currNode->right; }
    }
  } 
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

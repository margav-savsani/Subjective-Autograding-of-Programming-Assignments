#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  TreeNode *curr = root;
  while(true){
    if(curr->right != nullptr){
      curr = curr->right;
    }
    else if(curr->right= nullptr && curr->left!=nullptr){
      curr = curr->left;
    }
    else if(curr->right= nullptr && curr->left=nullptr){
       if(curr->parent->left->right!=nullptr){
        curr = curr->parent->left->right;
       }
       else if(curr->parent->left->right=nullptr && curr->parent->left->left!=nullptr){
          curr = curr->parent->left->left;
       }
    }
  }

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

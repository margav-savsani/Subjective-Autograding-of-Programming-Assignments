#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>

void Heap<T>::heapify(TreeNode<T> node){
    
}

void Heap<T>::insert(T obj) {
  // insert your code here
    
    if(root != nullptr){
        TreeNode<T> node = root;
        while(node != nullptr){
            if(node->left == nullptr){
                node->left = new TreeNode<T>(obj);
                return;
                //node = node->right;
            }
            else if(node->right == nullptr){
                node->right = new TreeNode<T>(obj);
                return;
                //node = node->parent->left->
            }
//            if(node->left == nullptr && node->right == nullptr){
//                node = node->left;
//            }
//            else if(node->left != nullptr && node->right == nullptr){
//                node = node->right;
//            }
//            else if(node->left != nullptr && node->right != nullptr){
//
//            }
        }
    }
    else if(root == nullptr){
        root = new TreeNode<T>(obj);
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

  

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

void swap_elem(TreeNode<T> *elem_1, TreeNode<T> *elem_2){
  TreeNode<T> *store = elem_1;
  elem_1 = elem_2;
  elem_2 = store;
}
template<typename T>
void Heap<T>::insert(T* obj) {
  // insert your code here
  int height_root = -1;
  int total_elements = 0;
  if(root == nullptr){
    root = obj;
    height_root++;
    total_elements++;
  }
  else if(total_elements < pow(2,height_root+1) - 1){
    TreeNode<T> *to_left_child_insert = root;
    while(to_left_child_insert->left != nullptr){
      to_left_child_insert = to_left_child_insert ->left;
    }
    while(to_left_child_insert->parent != nullptr){
      if(to_left_child_insert->parent->right == nullptr){
        to_left_child_insert->parent->right = obj;
        total_elements++;
      }
      else{
        to_left_child_insert = to_left_child_insert->parent;
      }
    }
    while(to_left_child_insert != nullptr){
      if(to_left_child_insert->right == nullptr){
        to_left_child_insert->right = obj;
        total_elements++;
      }
      else{

      }
    }
  }
  else{
    TreeNode<T> *to_left_child = root;
    while(to_left_child->left != nullptr){
      to_left_child = to_left_child ->left;
    }

    to_left_child->left = obj;
    total_elements++;
    height_root++;
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

  

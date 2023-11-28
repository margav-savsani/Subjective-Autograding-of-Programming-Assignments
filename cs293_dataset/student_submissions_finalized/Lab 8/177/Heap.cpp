#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


void Heap<T>::insert(T obj)
{
  if(root == nullptr){
    root = node;
    height++;
    current = node;
    return;
  }
  
  TreeNode<T> *curr = current;
  bool left_present = false;

  while((curr -> parent != nullptr) && (curr -> parent -> left == curr)) curr = curr -> parent;

  if(curr -> parent -> left == curr){
    curr = curr -> parent;
    left_present = true;
  }

  if(left_present){
    TreeNode<T> *temp_par = curr;
    curr = curr -> right;
    if(curr == nullptr){
      temp_par -> right = node;
      node -> parent = temp_par; 
      current = node;
    }

    else{
      temp_par = curr;
      curr = curr -> left;
      while(curr != nullptr) { temp_par = curr; curr = curr->left;}
      if(curr == nullptr){
          temp_par -> left = node;
          node -> parent = temp_par;
        }
    }
  }

  else{
    TreeNode<T> *temp_par = curr;
    curr = curr->left;
    while(curr != nullptr) {temp_par = curr; curr = curr c-> left}
    if(curr == nullptr){
      temp_par -> left = node;
      node -> parent = temp_par; 
      current = node;
      height++;
    }
  }
  
  TreeNode<T> *upward_moving = node;
  while((upward_moving -> object) > (upward_moving -> parent -> object) || upward_moving -> parent == nullptr)
  {
    swap_elements(upward_moving, upward_moving -> parent);
    node = node -> parent;
    if(node -> parent == nullptr) root = node;
  }
  return;

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

  

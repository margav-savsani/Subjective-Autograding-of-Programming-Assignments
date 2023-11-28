#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::relocate_cur_node() {

  if(check_power_of_two(size)) {
    cur_node=root;
    while(cur_node->left!==nullptr) {
      cur_node=cur_node->left;
    }
  }
  else {
    //go up and look to the right, using size
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T>* child_node = new TreeNode(obj);
  TreeNode<T>* parent_node = cur_node;
  T temp_obj;
  size+=1;

  if(root==nullptr) {
    root=child_node;
    cur_node=child_node;
    return;
  }

  else {
    if(parent_node->left==nullptr) {
      parent_node->left=child_node;
      child_node->parent=parent_node;
    }
    else if(parent_node->right==nullptr) {
      parent_node->right=child_node;
      child_node->parent=parent_node;
      relocate_cur_node();
    }

    while(parent_node!=nullptr && parent_node->object < child_node->object) {
      temp_obj=parent_node->object;
      parent_node->object=child_node->object;
      child_node->object=temp_obj;
      child_node=parent_node;
      parent_node=parent_node->parent;
    }
  }

  // insert your code here

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

  

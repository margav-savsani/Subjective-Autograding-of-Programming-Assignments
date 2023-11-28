#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if (root == NULL){
    root = new TreeNode<T>(obj);
    end = root;
    return;
  }
  else{
    TreeNode<T> *temp = end;
    TreeNode<T> *temp_parent = temp->parent;
    int count=0;
    while (temp_parent != nullptr && temp_parent->right == temp){
      temp = temp_parent;
      temp_parent = temp_parent->parent;
      count++;
    }
    if (temp_parent == nullptr){
      while (temp->left){
        temp = temp->left;
      }
    }
    else {
      temp = temp_parent->right;
      while(count-1){
        temp = temp->left;
        count--;
      }
      temp->left = new TreeNode<T>(obj);
      end = temp->left;
      end->parent = temp;
    }
    temp = end;
    while (temp->parent != NULL && temp->parent->object < temp->object){
      T t = temp->parent->object;
      temp->parent->object = temp->object;
      temp->object = t;
      temp = temp->parent;
      temp->parent = temp->parent->parent;
    }
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  // insert your code here
  if (root != NULL){
    if (root-> right == nullptr && root->left == nullptr){
      delete root;
      root = nullptr;
      end = nullptr;
      return;
    }
    T t = root->object;
    root->object = end->object;
    end->object = t;
    TreeNode<T> *temp = end;
    TreeNode<T> *temp_parent = temp->parent;
    int count=0;
    while (temp_parent != nullptr && temp_parent->left == temp){
      temp = temp_parent;
      temp_parent = temp_parent->parent;
      count++;
    }
    if (temp_parent == nullptr){
      while (temp->right){
        temp = temp->right;
      }
    }
    else {
      temp = temp_parent->left;
      while(count){
        temp = temp->right;
        count --;
      }
    }
    delete end;
    end = temp;
    Heapify();
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::Heapify() {

  TreeNode<T> *temp=root;
  while (temp->left != nullptr && temp->right != nullptr){
    if (temp->object < temp->left->object){
      if (temp->right->object < temp->left->object || (!(temp->right->object < temp->left->object) && !(temp->left->object < temp->right->object))){
        T t = temp->object;
        temp->object = temp->left->object;
        temp->left->object = t;
      }
    }
    else if (temp->object < temp->right->object){
      if (temp->left->object < temp->right->object || (!(temp->left->object < temp->right->object) && !(temp->right->object < temp->left->object))){
        T t = temp->object;
        temp->object = temp->right->object;
        temp->right->object = t;
      }
    }
    else{
      break;
    }
  }
  // insert your code here

  return;
}

  

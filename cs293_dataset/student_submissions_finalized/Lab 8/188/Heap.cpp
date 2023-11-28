#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template<typename T>
TreeNode<T>* Heap<T>::prevSibling(TreeNode<T>* node){
  if(node == root){
    return nullptr;
  }
  if(node->parent->right == node){
    return node->parent->left;
  }
  else{
    TreeNode<T>* ptr = node->parent;
    if(prevSibling(ptr) == nullptr){
      return nullptr;
    }
    return prevSibling(ptr)->right;
  }
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *element = new TreeNode<T>(obj);
  if(root = nullptr){
    root = element;
    return;
  }
  TreeNode<T> *node = root;
  TreeNode<T> *parent = nullptr;
  while(node->right != nullptr){
    parent = node;
    node = node->right;
  }
  while(true){
    if(node->left != nullptr){
      node->right = element;
      element->parent = node;
      break;
    }
    else{
    TreeNode<T> *adj = prevSibling(node);
    if(adj == nullptr){
      adj->left = element;
      element->parent = adj;
      break;
    }
    if(adj->right!= nullptr && adj->left!= nullptr){
      node->left = element;
      element->parent = node;
      break;
    }
    else {node= adj;}
    }
  }
  node = element;
  while(node->object > node->parent->object){
    T temp = node->parent->object;
    node->parent->object = node->object;
    node->object = temp;
    node = node->parent;
    if(node->parent == nullptr) break; 
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  // insert your code here
  root->object = -1;
  Heapify(root);
  return;
}
template<typename T>
TreeNode<T>* Heap<T>::Heapify(TreeNode<T>* node) {
  // insert your code here
  TreeNode<T>* maxi;
  if(node->left == nullptr && node->right == nullptr){
    return node;
  }
  else{ 
    maxi = node->left;
    if(node->right != nullptr){
      if(node->right->object > node->left->object){
        maxi = node ->right;
      }
    }
    
  }
  if(node->object < maxi->object){
    T temp = node->object;
    node->object = maxi->object;
    maxi->object = temp;
    Heapify(maxi);  
  }
  return node;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

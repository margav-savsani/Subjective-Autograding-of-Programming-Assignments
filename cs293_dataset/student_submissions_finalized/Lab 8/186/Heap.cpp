#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
int height(TreeNode<T> *node){
  int h = 0;
  TreeNode<T> *x = node;
  if(node == nullptr) return -1;
  while(x->left != nullptr){
    h++;
    x = x->left;
  }
  return h;
}

template<typename T>
TreeNode<T> *insertNode(TreeNode<T> *node){
  if(height(node) == 1){
    if((node->left == nullptr && node->right == nullptr) || (node->left == nullptr && node->right != nullptr)) return node;
  }
  insertNode(node->left);
  insertNode(node->right);
  return nullptr;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *newNode = new TreeNode<T>(obj);
  if(root == nullptr){
    root = newNode;
    return;
  }
  TreeNode<T> *x = insertNode(root);
  x = newNode;

  return;
}

template<typename T>
bool isComplete(TreeNode<T> *node){
  if(node->left == nullptr && node->right == nullptr) return true;
  else if((node->left == nullptr && node->right != nullptr) || (node->left != nullptr && node->right == nullptr)) return false; 
  static bool complete;
  complete = isComplete(node->left);
  complete = isComplete(node->right);
  return complete;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  if(node == nullptr) return;
  else{
    printHeap(node->left);
    cout << node->object << endl;
    printHeap(node->right);
  }

  return;
}

  

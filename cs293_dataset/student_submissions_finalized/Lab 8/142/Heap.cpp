#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

TreeNode* Heap<T>::getlastNode(TreeNode* node)
{
  
} 

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  getlastNode()

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
  cout << node->object << " ";
  if(node->left != nullptr)
  {
    printHeap(node->left);
  }
  if(node->right != nullptr)
  {
    printHeap(node->right);
  }
  
  return;
}
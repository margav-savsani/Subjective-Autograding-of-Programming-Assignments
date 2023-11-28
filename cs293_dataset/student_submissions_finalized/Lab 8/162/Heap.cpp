#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void mantainHeap(TreeNode<T>* node)
{ 
  TreeNode<T>* ptr = node;
  while(ptr->parent->object > ptr->object)
  {
    T obj = ptr->parent->object;
    ptr->parent->object = ptr->object;
    ptr->object = obj;
    ptr = ptr->parent;
  }
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == nullptr)
  {
    root = new TreeNode<T>(obj);
    helperQueue.push(root);
    return;
  }

  TreeNode<T>* last = helperQueue.front();
  if(last->left != nullptr)
  {
    last->left = new TreeNode<T>(obj);
    helperQueue.push(last->left);
    mantainHeap(last->left);
    return;
  }
  if(last->right != nullptr)
  {
    last->right = new TreeNode<T>(obj);
    helperQueue.push(last->right);
    mantainHeap(last->right);
    helperQueue.pop();
    return;
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

  

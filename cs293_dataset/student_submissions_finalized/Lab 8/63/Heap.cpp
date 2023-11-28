#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if (h == 0){
    root = new TreeNode(obj);
    h++;
    N++;
  }
  int n = N+1;
  int k = 0;
  bool * a = new bool[h];
  for (int i = h-1; i >=0 ; i--){
    if (n%2 == 0){
      a[i] = 0;
    }
    else {
      k++;
      a[i] = 1;
    }
    n /= 2;
  }
  TreeNode * A = root;
  
  for (int i = 0; i < h-1; i++){
    if (!a[i]){
      A = A->left;
    }
    else {
      A = A->right;
    }
  }
  if (!a[h-1]){
    A->left = new TreeNode(obj);
    A->left->parent = A;
    A = A->left;
  }
  else {
    A->right = new TreeNode(obj);
    A->right->parent = A;
    A = A->right;
  }
  if (k == h){
    h++;
  }
  N++;
  T obj1;
  while (true){
    if (A->parent == nullptr){
      return;
    }
    if (A->parent->object > A->object){
      return;
    }
    obj1 = A->parent->object;
    A->parent->object = A->object;
    A->object = obj1;
    A = A->parent;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if (h == 0){
    return;
  }
  int n = N;
  int k = 0;
  bool * a = new bool[h];
  for (int i = h-1; i >=0 ; i--){
    if (n%2 == 0){
      k++;
      a[i] = 0;
    }
    else {
      a[i] = 1;
    }
    n /= 2;
  }
  if (k == h){
    h--;
  }
  N--;
  TreeNode * A = root;
  for (int i = 0; i < h; i++){
    if (!a[i]){
      A = A->left;
    }
    else {
      A = A->right;
    }
  }
  root->object = A->object;
  delete A;
  

  return;
}
template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){
  if (node->left == nullptr){
    return;
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

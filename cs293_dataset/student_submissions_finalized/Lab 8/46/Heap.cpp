#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
int Heap<T>::height(TreeNode<T> *tree) {
  TreeNode<T> *ptr = tree;
  int h=0;
  while(ptr!=nullptr) {
    h++;
    ptr=ptr->left;
  }
  return h;
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  cnt++;
  if(root==nullptr) {
    root->object = obj;
    return;
  }
  int k = cnt,sz = height(root);
  int arr[sz];
  int i = 0;
  while(k>1) {
    arr[sz-1] =  k;
    sz--;
    k = k/2;
  }

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

  

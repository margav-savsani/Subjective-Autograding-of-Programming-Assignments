#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include<cmath>

template<typename F>
void n_ins(TreeNode<F> *curr, int n, F obj){
  int hf=int(log2(n+1) -1 );
  if(hf==0){
    if(curr->left==nullptr) curr->left= new TreeNode(obj);
    return;
  }
  if(n>3*pow(2,hf)+1){
    n_ins(curr->right, n-pow(2,hf)-1, obj);
  }
  else{
    n_ins(curr->left, n-pow(2,hf-1)-1, obj);
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  n_ins(root,node+1,obj);

  node++;
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

  

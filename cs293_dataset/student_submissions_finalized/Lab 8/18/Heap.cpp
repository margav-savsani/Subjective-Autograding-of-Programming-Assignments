#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include<cmath>

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
bool Heap<T>::goleft(){
  int n = nodes - (pow(2,(level-1))) + 1; //gives number of nodes in the last level
  if(n<pow(2,(level-2))){ //go to left subtree
    return true;
  } 
  else{
    return false;
  }
}

template<typename T>
T Heap<T>::put(T obj) {
  // insert your code here
  TreeNode<T> *t = new TreeNode<T>(obj);
  if(root == nullptr) {
    root = t;
    nodes=1;
    level=1;
    return nullptr;
  }
  //root!=nullptr

  if(goleft){
    Heap<T> new_heap = new Heap();
    new_heap.root = root->left;
    new_heap.root->parent = root;
    new_heap.put(obj);
    root->left = new_heap;
  }
  else{
    Heap<T> new_heap = new Heap();
    new_heap.root = root->right;
    new_heap.root->parent = root;
    new_heap.put(obj);
    root->right = new_heap;
  }
  nodes++;
  if(nodes== pow(2,level)){
    level++;
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  put(obj);
  //now rearrange

}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

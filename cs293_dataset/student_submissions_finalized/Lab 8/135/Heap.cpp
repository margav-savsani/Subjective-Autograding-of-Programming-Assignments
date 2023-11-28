#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T>* toadd = new TreeNode<T>(obj);
  if(root == nullptr) root = toadd;
  else if(root->left == nullptr) root->left = toadd;
  else if(root->right == nullptr) root->right = toadd;
  else{
    int a=0,b=0,c=0,d=0;
    TreeNode<T>* curr = root;
    while(curr!=nullptr){
      curr = curr->left;
      a++;
    }
    TreeNode<T>* curr = root;
    curr = curr->left;
    b++;
    while(curr!=nullptr){
      curr = curr->right;
      b++;
    }
    TreeNode<T>* curr = root;
    curr = curr->right;
    c++;
    while(curr!=nullptr){
      curr = curr->left;
      c++;
    }
    TreeNode<T>* curr = root;
    while(curr!=nullptr){
      curr = curr->right;
      d++;
    }

    if(a!=b) Heap(curr->left).insert();
    else if(c!=d) Heap(curr->right).insert();
    else Heap(curr->left).insert();
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

  

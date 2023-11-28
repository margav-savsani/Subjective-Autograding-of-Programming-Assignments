#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode * r = new TreeNode(obj);
  if(root == nullptr){
    root = r;
    k++;
  }
  else if(k == 2){
    root->left = r;
    r->parent = root;
    k++;
    
  }
  else if(k == 3){
    root->right = r;
    r->parent = root;
    k++;
    return;
  }
  else{
    int p = k/2;
    TreeNode *last = root;

    while( p != 1 ){
      if(p%2 == 0){
        n = n->left;
        p = p/2;
      }
      else{
        n = n->right;
        p = p/2;
      }
    }

    if(k%2 == 0 ){
      n->left = r;
      r->parent = n;
      k++;
    }
    else{
      n->right = r;
      r->parent = n;
      k++;
    }
  }

  while(r->parent != nullptr){
    if(r->obj < r->parent->obj){
      break;
    }
    else{
      T exc = r->obj;
      r->obj = r->parent->obj;
      r->parent->obj = exc;
      r = r->parent;
    }
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  if(k == 2){
    root = nullptr;
  }
  else{
    int p = k-1;
    TreeNode *last = root;
    while( p != 1){
      if(p%2 == 0){
        last = last->left;
        p = p/2;
      }
      else{
        last = last->right;
        p = p/2;
      }
    }
    T lastobj = last->object;
    root->obj = lastobj;
    if(last->parent->left == last){
      last->parent->left = nullptr;
      k--;
    }
    else{
      last->parent->right = nullptr;
      k--;
    }





    
  }
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

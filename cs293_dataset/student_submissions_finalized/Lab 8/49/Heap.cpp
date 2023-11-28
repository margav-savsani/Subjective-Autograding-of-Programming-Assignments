#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template <typename T> int Heap<T> :: maxheight(TreeNode<T> *x){
  if(TreeNode<T> *x == NULL)return -1;
  return 1 + maxheight(x->left);
}
template <typename T> int Heap<T> :: maxheight(TreeNode<T> *x){
  if(TreeNode<T> *x == NULL)return -1;
  return 1 + minheight(x->right);
}
template<typename T> void Heap<T>::insertNode(TreeNode<T> *x, T obj){
  if((x->left!=NULL)&&(x->right!=NULL)){
    if((maxheight(x->left)==minheight(x->left))){
      if(maxheight(x->left)==(maxheight(x->right))){
        if(maxheight(x->right)==(minheight(x->right))){
          insertNode(x->left,obj);
        }
        else{
          insertNode(x->right,obj);
        }
      }
      else insertNode(x->right,obj);
    }
    else insertNode(x->left,obj);
  }
  else if((x->left)==NULL)x->left = new TreeNode<T>(obj);
  else x->right = new TreeNode<T>(obj);
}
template<typename T> void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == nullptr){
    root = new TreeNode<T>(obj);
  }
  insertNode(root,T obj);
  return;
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

  

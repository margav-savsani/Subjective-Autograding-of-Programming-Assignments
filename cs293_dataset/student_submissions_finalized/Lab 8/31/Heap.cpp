#include <bits/stdc++.h>

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
TreeNode<T>* Heap<T>::checkempty(TreeNode<T> *node, bool &lft){
  static int recursionlevel = -1;
  recursionlevel++;
  if((log2(no_of_elem)%1==0 && recursionlevel>=log2(no_of_elem)+1) || recursionlevel>=int(log2(no_of_elem))){
    return NULL;
  }
  if(node->left==NULL){
    lft = true;
    return node;
  }
  else if(node->right==NULL){
    lft = false;
    return node;
  }
  TreeNode<T>* r = checkempty(node->left,lft);
  if(r!=NULL)
    return r;
  else 
  return checkempty(node->right,lft);
  recursionlevel--;
}

template<typename T>
void Heap<T>::swap(TreeNode<T> *par, TreeNode<T> *child){
  TreeNode<T> obj = par->object;
  par->object = child->object;
  child->object = obj;
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T>* node){
  while(node!=NULL){
    if(node->left!=NULL)
      if((node->left)->object>node->object){
        swap(node,node->left);
      }
    else if(node->right!=NULL)
      if((node->right)->object>node->object){
        swap(node,node->right);
      }
    else return;
    node = node->parent;
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> t = new TreeNode<T>(obj);
  bool lft=false;
  TreeNode<T> *found = checkempty(root,lft);
  if(lft)
    found->left = &t;
  else
    found->right = &t;
  Heapify(found);
  lastelem = &t;
  no_of_elem++;
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  swap(lastelem, root);
  if((lastelem->parent)->right == lastelem)
    (lastelem->parent)->right = NULL;
  else (lastelem->parent)->left = NULL;
  Heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

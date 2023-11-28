#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T> 
void custswap(TreeNode<T> *x, TreeNode<T> *y){
  T temp = x->object;
  x->object = y->object;
  y->object = temp;
}

template <typename T>
TreeNode<T> *pred(TreeNode<T> *t){
  if(t->parent == NULL) return NULL;
  while(t->parent!=NULL && t->parent->left==t){
    t = t->parent;
  }
  if(t->parent ==NULL){
    while(t->right != NULL){
      t = t->right;
    }
    return t;
  }
  else{
    t= t->parent->left ;
    while(t->right != NULL){
      t = t->right;
    }
    return t;
  }
}

template <typename T>
TreeNode<T> *succ(TreeNode<T> *t, T obj){
  if(t->parent == NULL){
    if(t->left != NULL){
      __throw_bad_function_call; 
    }
    t->left = new TreeNode<T>(obj) ;
    return t->left;  
  }
  else{
    while(t->parent!= NULL && t->parent->right == t ){
      t = t->parent;
    }
    if(t->parent == NULL){
      while(t->left != NULL && t->right!=NULL ) t= t->left;
      if(t->left == NULL){
        t->left = new TreeNode<T>(obj);
        return t->left;
      }
      else{
        t->right  = new TreeNode<T>(obj);
        return t->right;
      }
    }
    else{
      t = t->parent->right;
      while(t->left != NULL) t= t->left;
    }
  }
}


template<typename T>
void Heap<T>::insert(T obj) {
  if(root==NULL){
    root = new TreeNode<T>(obj);
    last  = root;
  }
  else if(root == last){
    root->left = new TreeNode<T>(obj);
    last = root->left;
    if(root->object < obj){
      custswap(root, root->left);
    }
  }
  else{
    TreeNode<T> insertionNode = succ(last,obj);
    last = insertionNode;
    while(insertionNode->parent!=NULL && insertionNode->object > insertionNode->parent->object){
      custswap(insertionNode , insertionNode->parent);
      insertionNode = insertionNode->parent;
    } 
  }

  return;
}

template<typename T>
void Heap<T>::delMax() {
  if(root==NULL) return;
  
  if(root== last) {
    root = NULL;
    last = NULL:
    return;
  }

  custswap(root,last);

  TreeNode<T> *pre = pred(last);
  if(last = last->parent->right) last->parent->right = NULL;
  else if(last = last->parent->left) last->parent->left = NULL;
  last = pre;

  //Now apply heapify 
  TreeNode<T> *currNode = root;
  while(true){
    if(currNode->left ==NULL) break;
    if(currNode->right == NULL){
      if(currNode->object < currNode->left->object ) custswap(currNode, currNode->left);
      break;
    }
    if(currNode->left->object <= currNode->object && currNode->right->object <= currNode->object) break;

    if(currNode->left->object > currNode->object){
      custswap(currNode->left,currNode);
      currNode = currNode->left;
    }
    else if(currNode->right->object > currNode->object ){
      custswap(currNode,currNode->right);
      currNode = currNode->right;
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

  

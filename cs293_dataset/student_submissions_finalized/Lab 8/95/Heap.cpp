#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::heapify(TreeNode<T>*a){
  if(a->parent->right==NULL){
      a=a->parent;
    }
  while(a->parent!=NULL){
    if(a->parent->object>a->object){
      return;
    }
    else{
     T r=a->object;
     a->object=a->parent->object;
     a->parent->object=r;
    
    }
  }
  return;
}
void Heap<T>::insert(T obj) {
  // insert your code here
TreeNode*a=new TreeNode<T>(obj);
TreeNode*b=root;
static TreeNode *parent_node;
if(this.root==NULL){
  this.root=a;
  parent_node=a;
  return ;
}
else if(parent_node->left==NULL&&parent_node->right==NULL){
  parent_node->left=a;
  a->parent=parent_node;
heapify(a);
return ;
}
else if(parent_node->left!=NULL&&parent_node->right==NULL){
  parent_node->right=a;
  a->parent=parent_node;
  heapify(a);
  parent_node=parent_node->parent->right;
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

  

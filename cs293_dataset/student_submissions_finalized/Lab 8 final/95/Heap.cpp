#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>

void Heap<T>::make_heap(TreeNode<T>*a){
  if(a->parent->right==NULL){
    if(a->parent->object<a->object){
      T tmp=a->object;
      a->object=a->parent->object;
      a->parent->object=tmp;
    }
    else{return;}
      a=a->parent;
    }
  while(a->parent!=NULL){
   
    if((a->object)<(a->parent->object)){
      return;
    }
    else{
     T r=a->object;
     a->object=a->parent->object;
     a->parent->object=r;
    a=a->parent;
    }
  }
  return;
}
template<typename T>
void Heap<T>::heapify(TreeNode<T>*a){
  if(a->left==NULL&&a->right==NULL){
    return ;
  }
  else if(a->right==NULL){
    if(a->object<a->right->object){
    T tmp=a->object;
    a->object=a->right->object;
    a->right->object=tmp;}
    return ;
  }
  else if(a->left->object<(a->object)&&a->right->object<(a->object)){
   return;
  }
  else if(a->right->object<a->left->object){
    return heapify(a->left);
  }
  else {
    return heapify(a->right);
  }

}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
TreeNode<T>*a=new TreeNode<T>(obj);


if(this->root==NULL){
  this->root=a;
 this->parent_node=a;
  return ;
}


if(parent_node->left==NULL&&parent_node->right==NULL){
  parent_node->left=a;
  a->parent=parent_node;
make_heap(a);
return ;
}


if(parent_node->left!=NULL&&parent_node->right==NULL){
  parent_node->right=a;
  a->parent=parent_node;
  make_heap(a);
  int special=0;
  if(parent_node==root){
    parent_node=parent_node->left;
    return;
  }
  while (parent_node->parent->right==parent_node)
  { if(parent_node->parent==root){
    special++;
    break;
  }
    parent_node=parent_node->parent;
  }
  
  parent_node=parent_node->parent;
  if(special==0){
  parent_node=parent_node->right;}
  while(parent_node->left!=NULL){
    parent_node=parent_node->left;
  }
  return;
}

  return;
}


template<typename T>
void Heap<T>::delMax() {
  if(parent_node->left==NULL){
    int special=0;
    while (parent_node->parent->left==parent_node)
    {if(parent_node->parent==root){
      special++;
      break;
    }
      parent_node=parent_node->parent;
    }
    
    parent_node=parent_node->parent;
    if(special==0){
    parent_node=parent_node->left;}
    while(parent_node->right!=NULL){
      parent_node=parent_node->right;
    }
    parent_node=parent_node->parent;
     root->object=parent_node->right->object;
    parent_node->right=NULL;
    heapify(root);
    return ;
   
  }
  else if(parent_node->left!=NULL){
    root->object=parent_node->left->object;
    heapify(root);
    return;
  }
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

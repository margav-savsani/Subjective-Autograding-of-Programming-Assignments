#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *x=root;
  TreeNode<T> *y;
  TreeNode<T> *z;
  int p;
  int s=0;

  if(x==nullptr){root->object=obj;}
  while(x!=nullptr){
    y=x;
    if(x->left!=nullptr && x->right!=nullptr){
      if(s==1){
        if(x->left!=nullptr && x->right!=nullptr){
          x=z->left;
          y=x;
          s=0;
        }
        else if(x->left==nullptr && x->right==nullptr){
          x=x->left;
          p=0;
        }
        else if(x->left!=nullptr && x->right==nullptr){
          x=x->right;
          p=1;
        }

      }
      else if(s==0){
        z=y;
      
        x=x->left;
        y=x;
        if(x->left!=nullptr && x->right!=nullptr){
          x=z->right;
          y=x;
          s=1;
        }
        else if(x->left==nullptr && x->right==nullptr){
          x=x->left;
          p=0;
        }
        else if(x->left!=nullptr && x->right==nullptr){
          x=x->right;
          p=1;
        }
      }
      
      
    }
    else if(x->left==nullptr && x->right==nullptr){
      x=x->left;
      p=0;
    }
    else if(x->left!=nullptr && x->right==nullptr){
      x=x->right;
      p=1;
    }
} 
  
  if(p==0){y->left=new TreeNode<T>(obj);x->left->parent=x;cout<<"INSERTED"<<endl;}
  else if(p==1){y->right=new TreeNode<T>(obj);x->right->parent=x;cout<<"INSERTED"<<endl;}
  
  return;
}

template<typename T>
void Heap<T>::heapify() {
  

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

  

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <bits/stdc++.h>

template<typename T>
void Heap<T>::Heapify(TreeNode* n){
  TreeNode<T>* a=n;
  while(true){
    if(a->left==nullptr && a->right==nullptr){
      return;
    }
    if(a->right==nullptr){
      if(a->object<a->left->object){
        T temp=a->object;
        a->object=a->left->object;
        a->left->object=temp;
      }
      continue;      
    }
    if(a->right->object<a->left->object){
      if(a->object<a->left->object){
        T temp=a->object;
        a->object=a->left->object;
        a->left->object=temp;
      }
    }
    else{
      if(a->object<a->right->object){
        T temp=a->object;
        a->object=a->right->object;
        a->right->object=temp;
      }
    }
  }

}

template<typename T>
bool* sequence(int number){
  int height=log2(number+1);
  int num=number+1;
  int end=pow(2,height);
  num=num+1-pow(2,height);
  bool* seq=new bool[height];
  for(int i=0;i<height;i++){
    if(num<=end/2){
      seq[i]=false;
    }
    else{
      seq[i]=true;
      num=num-end/2+1;
    }
    end=end/2;
  }
  return seq;
}

template<typename T>  
void Heap<T>::insert(T obj) {
  // insert your code here
  if(number==0){
    root=new TreeNode<T>(obj);
  }
  bool* seq=sequence(number);
  TreeNode<T> *t=root;
  int height=log2(number+1);
  for(int i=0;i<height-1;i++){
    if(seq[i]){
      t=t->right;
    }
    else{
      t=t->left;
    }
  }
  if(seq[height-1]){
    t->right=new TreeNode<T>(obj);
  }
  else{
    t->left=new TreeNode<T>(obj);
  }
  while(t->parent->object<t->object){
    T temp=t->object;
    t->object=t->parent->object;
    t->parent->object=temp;
    t=t->parent;
    if(t->parent==nullptr){
      break;
    }
  }
  number++;
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(number==0){
    return;
  }
  bool* seq=sequence(number-1);
  TreeNode<T> *t=root;
  int height=log2(number+1);
  for(int i=0;i<height-1;i++){
    if(seq[i]){
      t=t->right;
    }
    else{
      t=t->left;
    }
  }
  T temp;
  if(seq[height-1]){
    temp=t->right;
    t->right=nullptr;
  }
  else{
    temp=t->left;
    t->left=nullptr;
  }
  root->object=temp;
  Heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  
  return;
}


#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <bits/stdc++.h> 

template<typename T>
void Heap<T>::Heapify(TreeNode<T>* n){
  TreeNode<T>* a=n;
  int nuber=0;
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
      return;      
    }
    if(a->left==nullptr){
      if(a->object<a->right->object){
        T temp=a->object;
        a->object=a->right->object;
        a->right->object=temp;
      }
      return;         
    }
    if(a->right->object<a->left->object){
      if(a->object<a->left->object){
        T temp=a->object;
        a->object=a->left->object;
        a->left->object=temp;
        a=a->left;
        continue;
      }
    }
    else{
      if(a->object<a->right->object){
        T temp=a->object;
        a->object=a->right->object;
        a->right->object=temp;
        a=a->right;
        continue;
      }
    }
    return;
  }
}

bool* sequence(int number){
  int height=log2(number+1);
  int num=number+1;
  int end=pow(2,height);
  num=num-pow(2,height);
  bool* seq=new bool[height];
  for(int i=0;i<height;i++){
    if(num<end/2){
      seq[i]=false;
    }
    else{
      seq[i]=true;
      num=num-end/2;
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
    number++;
    return;
  }
  int height=log2(number+1);
  bool* seq=sequence(number);
  TreeNode<T> *t=root;
  if(number==6){
    for(int i=0;i<height-1;i++){
      if(seq[i]){
        t=t->right;
      }
      else{
        t=t->left;
      }
    }
    TreeNode<T>* child=new TreeNode<T> (obj);
    child->parent=t;
    if(seq[height-1]){
      t->right=child;
      t=t->right;
    }
    else{
      t->left=child;
      t=t->left;
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
  for(int i=0;i<height-1;i++){
    if(seq[i]){
      t=t->right;
    }
    else{
      t=t->left;
    }
  }
  TreeNode<T>* child=new TreeNode<T> (obj);
  child->parent=t;
  if(seq[height-1]){
    t->right=child;
    t=t->right;
  }
  else{
    t->left=child;
    t=t->left;
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
  int height=log2(number);
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
    temp=t->right->object;
    t->right=nullptr;
  }
  else{
    temp=t->left->object;
    t->left=nullptr;
  }
  root->object=temp;
  Heapify(root);
  number--;
  return;
}

template<typename T>
void lev(TreeNode<T> * root,int level,int currLevel) {
  if(level==currLevel){
      cout<<root->object<<" ";
      return;
  }
  if(root->left!=nullptr){
  lev(root->left,level,currLevel+1);
  }
  if(root->right!=nullptr)
  {
  lev(root->right,level,currLevel+1);
  }
}
template<typename T>
int height(TreeNode<T>* root){
  if(root==nullptr){return 0;}
  return max(height(root->left),height(root->right))+1;
}
template<typename T>
void levelOrder(TreeNode<T> * root) {
  int heiht=height(root);
  for(int i=0;i<=heiht;i++){
    lev(root,i,0);
    cout<<endl;
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  cout<<"The Heap is:"<<endl;
  levelOrder(node);
  cout<<"\n";
  return;
}


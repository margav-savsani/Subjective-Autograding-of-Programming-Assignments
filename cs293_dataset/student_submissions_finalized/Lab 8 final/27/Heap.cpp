#ifndef STD_HEADERS_H
#include "std_headers.h"
#include <cmath>
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root==NULL){
    root=new TreeNode<T>(obj);
    elem++;
    return;
  }
  TreeNode<T>*curr=root;
  int h=log2(elem+1);
  int p=(elem+1)/2;
  int x=1;
  while(x!=p){
    if((2*x+1)*pow(2,h-2)>p){
      x=2*x;
      h--;
      curr=curr->left;
    }
    else{
      x=2*x+1;
      h--;
      curr=curr->right;
    }
  }
  if(curr->left==NULL){
    curr->left=new TreeNode<T>(obj,curr);
    curr=curr->left;
  }
  else{
    curr->right=new TreeNode<T>(obj,curr);
    curr=curr->right;
  }
  while(true){
    if(curr->parent==NULL)break;
    {
      if(curr->parent->object<curr->object){
      T temp=curr->parent->object;
      curr->parent->object=curr->object;
      curr->object=temp;
      curr=curr->parent;
      }
      else break;
    }
  }
  elem++;
  return;
}

template<typename T>
void Heap<T>::delMax() {
  if(elem==0)return;
  if(elem==1){
    delete root;
    root=nullptr;
    elem--;
    return;
  }
  TreeNode<T>*curr=root;
  int h=log2(elem);
  int p=(elem)/2;
  int x=1;
  while(x!=p){
    if((2*x+1)*pow(2,h-2)>p){
      x=2*x;
      h--;
      curr=curr->left;
    }
    else{
      x=2*x+1;
      h--;
      curr=curr->right;
    }
  }
  TreeNode<T>*de;
  if(curr->right!=NULL){
    de=curr->right;
    curr->right=NULL;
  }
  else {
    de= curr->left;
    curr->left=NULL;
  }
  root->object=de->object;
  delete de;
  elem--;
  curr=root;
  while(true){
    TreeNode<T>*child=NULL;
    if(curr->left!=NULL)child=curr->left;
    {
      if(child==NULL)child=curr->right;
      else{
        if(curr->right!=NULL){
          if(curr->left->object<curr->right->object)child=curr->right;
        }
      }
    }
    if(child==NULL)break;
    else{
      if(curr->object<child->object){
        T temp=curr->object;
        curr->object=child->object;
        child->object=temp;
      }
      else break;
    }
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *root) {

    print(root,"",true);

  return;
}
template<typename T>
void Heap<T>::print(TreeNode<T> *root, const string& prefix, bool isLeft){
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout<<root->object;
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    print(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    print(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else {
    cout << "NULL tree" << endl;
  }
}


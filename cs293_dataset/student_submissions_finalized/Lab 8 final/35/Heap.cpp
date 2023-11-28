#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <cmath>

template<typename T>
void Heap<T>::swap(TreeNode<T> *A,TreeNode<T> *B){
  T temp = A->object;
  A->object = B->object;
  B->object = temp;
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node ){
  if(node->left == nullptr) return;
  if(node->right == nullptr){
    if(node->object < node->left->object){
      swap(node,node->left);
      return;
      }
    }
  else{
    TreeNode<T> *GreaterNode;
    if(node->right->object < node->left->object) GreaterNode = node->left;
    else GreaterNode = node->right;
    if(node->object < GreaterNode->object){
      swap(node,GreaterNode);
      return Heapify(GreaterNode);
    }
    else return;
  }
}

template<typename T>
int Heap<T>::level(int n){
  int lvl = log2(n);
  return lvl;
}

template<typename T>
void Heap<T>::binary(int n,int l,int* Arr){
  while(l!=0){
    Arr[l-1] = n%2;
    n = n/2;
    l--;
  }
  return;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *New = new TreeNode<T>(obj);
  if(root == nullptr){
    root = New;
    TotalNodes++;
  }
  else{
    TreeNode<T> *temp = root;
    TotalNodes++;
    int lvl = level(TotalNodes);
    int k = pow(2,lvl);
    int* Arr=new int[lvl];
    binary(TotalNodes%k,lvl,Arr);
    for(int i=0;i<lvl-1;i++){
      if(Arr[i]==0){temp = temp->left;}
      else temp = temp->right;
    }
    New->parent = temp;
    if(Arr[lvl-1]==0) {temp->left = New;temp=temp->left;}
    else {temp->right = New;temp=temp->right;}
    while(temp != nullptr && temp->parent != nullptr){
      if(temp->parent->object < temp->object){
        swap(temp,temp->parent);
        temp = temp->parent;
      }
      else break;
    }
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  // insert your code here
  if(root->left == nullptr){
    root = nullptr;
    TotalNodes--;
    return;
  }
  TreeNode<T> *temp = root;
  int lvl = level(TotalNodes);
  int k = pow(2,lvl);
  int* Arr=new int[lvl];
  binary(TotalNodes%k,lvl,Arr);
  for(int i=0;i<lvl;i++){
      if(Arr[i]==0){temp = temp->left;}
      else temp = temp->right;
    }
  swap(root,temp);
  if(Arr[lvl-1]==0) temp->parent->left = nullptr;
  else temp->parent->right = nullptr;
  TotalNodes--;
  Heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  // insert your code here
  printBST(" ");
  return;
}

  

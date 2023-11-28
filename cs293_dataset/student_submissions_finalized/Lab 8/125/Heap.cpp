#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <vector>
using namespace std;

template<typename T>
void Heap<T>::insert(T obj) {
  int n = this->size + 1;
  vector<int> v;
  while(n!=0){
    v.push_back(n);
    n /= 2;
  }
  TreeNode* curr = root;
  while(true){
    v.pop_back();
    if(v.size()==1){
      if(v[0]%2==0) curr->left = new TreeNode<T>(obj);
      else curr->right = new TreeNode<T>(obj);
      break;
    }
    if(v.back()%2==0) curr = curr->left;
    else curr = curr->right;
  }
  this->size++;
  return;
}

template<typename T>
T Heap<T>::delMax() {
  T return_val = root->object;
  if(root->left==NULL){
    root = NULL;
    return return_val; 
  }
  int n = this->size;
  vector<int> v;
  while(n!=0){
    v.push_back(n);
    n /= 2;
  }
  TreeNode* curr = root;
  bool l_child;
  while(true){
    v.pop_back();
    if(v.size()==0) break;
    if(v.back()%2==0){
      curr = curr->left;
      l_child = true;
    }
    else{
      curr = curr->right;
      l_child = false;
    }
  }
  root->object = curr->object;
  if(l_child) curr->parent->left = NULL;
  else curr->parent->right = NULL;
  curr = root;
  while(curr->left!=NULL){
    if(curr->right = NULL){
      if(curr->object<curr->left->object){
        T temp = curr->object;
        curr->object = curr->left->object;
        curr->left->object = temp;
      }
      return return_val;
    }
    if(curr->object>=curr->left->object&&curr->object>=curr->right->object) break;
    if(curr->left->object<curr->right->object){
      T temp = curr->object;
      curr->object = curr->right->object;
      curr->right->object = temp;
      curr = curr->right;
    }
    else{
      T temp = curr->object;
      curr->object = curr->left->object;
      curr->left->object = temp;
      curr = curr->left;
    }
  }
  return return_val;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  cout << node->object;
  return;
}

  

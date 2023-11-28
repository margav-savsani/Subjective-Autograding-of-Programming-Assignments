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
  if(this->size==0){
    root = new TreeNode<T>(obj);
    this->size = 1;
    return;
  }
  int n = this->size + 1;
  vector<int> v;
  while(n!=0){
    v.push_back(n);
    n /= 2;
  }
  TreeNode<T>* curr = root;
  while(true){
    v.pop_back();
    if(v.size()==1){
      if(v[0]%2==0){
        curr->left = new TreeNode<T>(obj);
        curr->left->parent = curr;
        curr = curr->left;
      }
      else{
        curr->right = new TreeNode<T>(obj);
        curr->right->parent = curr;
        curr = curr->right;
      }
      break;
    }
    if(v.back()%2==0) curr = curr->left;
    else curr = curr->right;
  }
  this->size++;
  while(curr->parent!=NULL){
    if(curr->parent->object<curr->object){
      T temp = curr->object;
      curr->object = curr->parent->object;
      curr->parent->object = temp;
      curr = curr->parent;
    }
    else break;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {
  if(root==NULL) return;
  T return_val = root->object;
  int n = this->size;
  this->size--;
  if(root->left==NULL){
    root = NULL;
    return; 
  }
  vector<int> v;
  while(n!=0){
    v.push_back(n);
    n /= 2;
  }
  TreeNode<T> * curr = root;
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
    if(curr->right == NULL){
      if(curr->object<curr->left->object){
        T temp = curr->object;
        curr->object = curr->left->object;
        curr->left->object = temp;
      }
      return;
    }
    if(!(curr->object<curr->left->object)&&!(curr->object<curr->right->object)) break;
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
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  printBinaryTree(node, "", false);
  return;
}

template<typename T>
void Heap<T>::printBinaryTree(TreeNode<T> *root, const string& prefix, bool isLeft)
{
  if( root != nullptr )   {
    cout << prefix;
    
    cout << (isLeft ? "|--" : "|__" );
    
    // print the value of the node
    cout << root->object;
    cout << endl;
    TreeNode<T> * curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

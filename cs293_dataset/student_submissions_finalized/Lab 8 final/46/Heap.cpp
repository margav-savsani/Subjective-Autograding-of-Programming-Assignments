#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
int Heap<T>::height(TreeNode<T> *tree) {
  TreeNode<T> *ptr = tree;
  int h=0;
  while(ptr!=nullptr) { // traversing down the tree
    h++;
    ptr=ptr->left; // because it is left-sided
  }
  return h;
 }
 template<typename T>
 void Heap<T>::insert(T obj) {
  cnt++;
  if(root==nullptr) { // insertion of first node
    root = new TreeNode<T> (obj);
    return;
  }
  int k = cnt,h = height(root),sz;
  sz = h;
  int arr[sz]; // converting the tree into binary tree array 
  while(k>1) {
    arr[sz-1] =  k%2; // 0 ->left, 1 ->right
    sz--;
    k = k/2;
  }

  TreeNode<T> *tmp = root,*prev = nullptr;
  bool isleft = 0;
  for(int j=0;j<h;j++) {
    if(arr[j]==0) { // position of the last element 
      prev = tmp;
      tmp = tmp->left;
      isleft = 1;
    }
    else if(arr[j]==1) { // position of the last element 
      prev = tmp;
      tmp = tmp->right;
      isleft = 0;
    }
  }
  tmp = new TreeNode<T> (obj);
  if(h-1>=0){if(arr[h-1] == 0) {prev->left = tmp;} // this condition will never fail
  else prev->right = tmp;}
  tmp->parent = prev;
  
  while(tmp->parent!=nullptr) {
    if((tmp->parent->object) < tmp->object) { //swaping the parent and child
      T st = tmp->parent->object;
      tmp->parent->object = tmp->object;
      tmp->object = st;
    }
    else break; // heapification is completed
    tmp = tmp->parent;
  }
}

template<typename T>
void Heap<T>::delMax() {
  if(root==nullptr) { // no node to delete
    return;
  }
  int k = cnt,h = height(root),sz;
  sz = h;
  int arr[sz];

  while(k>1) {
    arr[sz-1] =  k%2;
    sz--;
    k = k/2;
  }
  TreeNode<T> *tmp = root,*prev = nullptr;
  for(int j=0;j<h;j++) { // heap to binary tree with 0,1 s
    if(arr[j]==0) {
      prev = tmp;
      tmp = tmp->left;
    }
    else if(arr[j]==1) {
      prev = tmp;
      tmp = tmp->right;
    }
  }

// --------------------------------------------------------
  TreeNode<T>* last = tmp;
  if(tmp == nullptr) { //base case
    return;
    }
    
  root->object = tmp->object; // swaping the last with the root node

  if(arr[h-1]==0) (tmp->parent)->left = nullptr;
  else (tmp->parent)->right = nullptr;

  tmp = root;
  while(tmp!=nullptr) { 
    if(tmp->left == nullptr && tmp->right == nullptr) {break;} // base case;

    else if(tmp->left!=nullptr && tmp->right ==nullptr){
      if(tmp->object < tmp->left->object) {  // swaping to satisfy heap properties
      T st = tmp->object;
      tmp->object = tmp->left->object;
      tmp->left->object = st;
      tmp = tmp->left;  
    }
    else break; // process is completed
    }
    else if(tmp->left!=nullptr && tmp->right !=nullptr){
     if(tmp->left->object < tmp->right->object) { // swaping to satisfy heap properties
      if(tmp->object < tmp->right->object) {
      T st = tmp->object;
      tmp->object = tmp->right->object;
      tmp->right->object = st;
      tmp = tmp->right;
      }
      else break; // process is completed
    }
    else {
      if(tmp->object < tmp->left->object) { // swaping to satisfy heap properties
      T st = tmp->object;
      tmp->object = tmp->left->object;
      tmp->left->object = st;
      tmp = tmp->left;     
    }
    else break; // process is completed
    }
  }
  }
  cnt--; // reducing the count of nodes
  return;
   
}
template<typename T>
void Heap<T>::printHeap(const string& prefix, bool isLeft) {
      if( root != nullptr )
    {
         cout << prefix;

         cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
         cout << root->object << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printHeap( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printHeap( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
  return;
}
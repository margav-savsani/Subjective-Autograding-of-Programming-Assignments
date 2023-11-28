#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(count == 0){
    root = new TreeNode<T>(obj);
    count++;
    return;
  }
  count++;
  int h = 0;
  int a = count;
  while(a != 1){
    a = a/2;
    h++;
  }
  a = count;
  int *arr = new int[h];
  for(int i = h-1; i >= 0; i--){
    if( a%2 == 1)arr[i]=1;
    else arr[i]=0;
    a = a/2;
  }
  TreeNode<T> *currnode = root;
  for(int i = 0; i < h-1; i++){
    if(arr[i] == 0)currnode = currnode->left;
    else currnode = currnode->right;
  }
  TreeNode<T> *newNode = new TreeNode<T>(obj);
  if(arr[h-1] == 0)currnode->left = newNode;
  else currnode->right = newNode;
  newNode->parent = currnode;
  currnode = newNode;
  while(currnode->parent != nullptr){
    if(currnode->object < currnode->parent->object)break;
    T objec = currnode->object;
    currnode->object = currnode->parent->object;
    currnode->parent->object = objec;
    currnode = currnode->parent;
  }
  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  if(count == 1){
    T obj = root->object;
    //------------------check this-----------------
    delete root->object;
    root = nullptr;
    count--;
    return obj;
  }
  T retobj = root->object;
  int k = count;
  int h = 0;
  int a = count;
  while(a != 1){
    a = a/2;
    h++;
  }
  a = count;
  int *arr = new int[h];
  for(int i = h-1; i >= 0; i--){
    if( a%2 == 1)arr[i]=1;
    else arr[i]=0;
    a = a/2;
  }
  TreeNode<T> *currnode = root;
  for(int i = 0; i < h; i++){
    if(arr[i] == 0)currnode = currnode->left;
    else currnode = currnode->right;
  }
  root->object = currnode->object;
  TreeNode<T> *par = currnode->parent;
  if(arr[h-1] == 0)par->left = nullptr;
  else par->right = nullptr;
  delete currnode;
  count--;
  return retobj;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

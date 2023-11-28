#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include<cmath>

template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){
  if (node->left == nullptr && node->right == nullptr) return;
  if (node->left != nullptr && node->right == nullptr ){
    if ((node->object < node->left->object )) {swap(node->left->object,node->object); return;}
    else return;
  }
  if (node->left != nullptr && node->right != nullptr){
    if (node->left->object < node->object && node->right->object < node->object) return;
    else if (node->left->object < node->object && node->object < node->right->object) {swap(node->right->object,node->object); heapify(node->right); return ;}
    else if (node->right->object < node->object && node->object < node->left->object) {swap(node->left->object,node->object); heapify(node->left); return ;}
    else {
      if (node->left->object < node->right->object) {swap(node->right->object,node->object); heapify(node->right); return ;}
      if (node->right->object < node->left->object) {swap(node->left->object,node->object); heapify(node->left); return ;}
      else return;
    }
  }
}

template<typename T>
TreeNode<T>* Heap<T>::findelewithindex(int index){

  //finding element with given index
  int newindex = index +1;
  int length = (int)log2(newindex);
  int arr[length+1];
  //storing the binary representation of index + 1
  for(int i=0; i<length+1; i++){
    arr[i] = newindex%2;
    newindex/=2;
  }
  TreeNode<T>* temp = root;
  
  for (int i=0 ; i<length ; i++){
    if (arr[length-i-1] == 1) {temp=temp->right; }
    if (arr[length-i-1] == 0) {temp= temp->left; }
  }
  return temp;
}

template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T>* newnode = new TreeNode<T>(obj);
  if (root == nullptr) {root = newnode; N=0; return;}
  else{
    TreeNode<T>* lastparent = findelewithindex(N/2); // the parent node to which the child is to be inserted
    if(lastparent->left == nullptr) {lastparent->left = newnode; newnode->parent = lastparent;}
    else {lastparent->right = newnode; newnode->parent = lastparent;}
    while (newnode != root && newnode->parent->object < newnode->object  ){swap(newnode->object,newnode->parent->object); newnode = newnode->parent;}
    N+=1;
    return;
  }
}

template<typename T>
T Heap<T>::delMax() {
  // insert your code here
  T maxvalue = root->object;
  TreeNode<T>* lastnode = findelewithindex(N); // the last node which is deleted after replacing it with max element
  if (lastnode == root){delete root; root = nullptr; N=-1; return maxvalue;}
  else{
    swap(root->object,lastnode->object);
    if(lastnode->parent->left == lastnode) lastnode->parent->left = nullptr;
    else if(lastnode->parent->right == lastnode) lastnode->parent->right = nullptr;
    delete lastnode;
    N = N-1;
    heapify(root); //heapifying root since it only it is the misplaced element
  }
  return maxvalue;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

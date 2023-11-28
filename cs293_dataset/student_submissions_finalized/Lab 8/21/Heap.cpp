#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){
  if (node->left == nullptr && node->right == nullptr) return;
  if (node->left != nullptr && node->right == nullptr ){
    if ((node->left->object > node->object)) {swap(node->left->object,node->object); return;}
    else return;
  }
  if (node->left != nullptr && node->right != nullptr){
    if (node->left->object <= node->object && node->right->object <= node->object) return;
    else {
      if (node->right->object >= node->left->object) {swap(node->right->object,node->object); heapify(node->right); return ;}
      if (node->right->object < node->left->object) {swap(node->left->object,node->object); heapify(node->left); return ;}
    }
  }
}

template<typename T>
TreeNode<T>* Heap<T>::findelewithindex(int index){
  TreeNode<T>* temp = root;
  while(index != 0){
    if (index%2 == 0) {temp=temp->right; index = index/2;}
    if (index%2 == 1) {temp= temp->left; index =index/2;}
  }
  return temp;
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T>* newnode = new TreeNode<T>(obj);
  if (root == nullptr) {root = newnode; N=0; return;}
  TreeNode<T>* lastparent = findelewithindex(N/2);
  if(lastparent->left == nullptr) {lastparent->left = newnode; newnode->parent = lastparent;}
  else {lastparent->right = newnode; newnode->parent = lastparent}
  while (newnode < newnode->parent || newnode == root){swap(newnode->object,newnode->parent->object); newnode = newnode->parent;}
  N+=1;
  return;
}

template<typename T>
T Heap<T>::delMax() {
  // insert your code here
  TreeNode<T>* lastnode = findelewithindex(N);
  if (last == root){delete root; root = nullptr; N=-1; return;}
  else{
    swap(root->object,last->object);
    if(lastnode-parent->left = lastnode) lastnode->parent->left = nullptr;
    else if(lastnode-parent->right = lastnode) lastnode->parent->rigth = nullptr;
    delete lastnode;
    heapify(root);
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T> *new_node = new TreeNode<T>(obj);
  TreeNode<T>* parent;
  TreeNode<T>* currNode =root;
  if(root==nullptr){root = new_node;level=1;free_node=0;return;}
  int arr[level];
  int i=level-1;
  int position = free_node;
  while(i!=-1){
    arr[i] = position%2;
    position = position/2;
    i--;
  }
  while(i!=level-2){
    i++;
    if(arr[i]==0) currNode = currNode->left;
    else currNode = currNode->right;
  }
  if(arr[i+1]==0) currNode->left = new_node;
  else currNode->right = new_node;
  new_node->parent = currNode;
  Heapifyup(new_node);
  free_node++;
  if(free_node == pow(2,level)){level++; free_node=0;}
  return;
}

template<typename T>
void Heap<T>::delMax() {
TreeNode<T>* currNode =root;
if(free_node == 0){level--; free_node = pow(2,level)-1;}
else free_node--;
if(level==0&&free_node==0) {root=nullptr; return;}
int arr[level];
  int i=level-1;
  int position = free_node;
  while(i!=-1){
    arr[i] = position%2;
    position = position/2;
    i--;
  }
  while(i!=level-1){
    i++;
    if(arr[i]==0) currNode = currNode->left;
    else currNode = currNode->right;
  }
  root->object = currNode->object;
  if(currNode->parent->left==currNode) currNode->parent->left=nullptr;
  else currNode->parent->right=nullptr;
  
  Heapifydown(root);
  return;
}
template<typename T>
void Heap<T>::Heapifydown(TreeNode<T> *node) {

  if(node->left == nullptr && node->right == nullptr) return;
  TreeNode<T>* left = node->left;
  TreeNode<T>* right = node->right;
  TreeNode<T>* max;
  if(right == nullptr){
    if(node->object < left->object){
      T obj;
      obj=node->object;
      node->object=left->object;
      left->object=obj;
      }
      Heapifydown(left);
    }
    
  else {
    if(right->object < left->object) max=left;
    else max=right;
    if(node->object < max->object){
      T obj;
      obj=node->object;
      node->object=max->object;
      max->object=obj;
    }
    Heapifydown(max);
  }
  
}
template<typename T>
void Heap<T>::Heapifyup(TreeNode<T> *node) {
  if(node==nullptr) return;
  if(node->left == nullptr && node->right == nullptr) {Heapifyup(node->parent); return;}
  TreeNode<T>* left = node->left;
  TreeNode<T>* right = node->right;
  TreeNode<T>* max;
  if(right == nullptr){
    if(node->object < left->object){
      T obj;
      obj=node->object;
      node->object=left->object;
      left->object=obj;
      }
      Heapifyup(node->parent);
      return;
    }
    
  else {
    if(right->object < left->object) max=left;
    else max=right;
    if(node->object < max->object){
      T obj;
      obj=node->object;
      node->object=max->object;
      max->object=obj;
    }
    Heapifyup(node->parent);
  }
  
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
 printBST(" ");
}

  

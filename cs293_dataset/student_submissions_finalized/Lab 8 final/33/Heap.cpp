#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include<cmath>
using namespace std ;

template<typename T>
void Heap<T>::swap(TreeNode<T> *a,TreeNode<T> *b){
  T c ;
  c = a->object ;
  a->object = b->object ;
  b->object = c ;
  return ;
}

template<typename T>
int Heap<T>::getheight(TreeNode<T> *currnode){
  if(currnode == nullptr){
     return -1 ;
   }
   else if((currnode->left==nullptr)&&(currnode->right==nullptr)){
    currnode->height = 0 ;
    return 0 ;
   }
   int left_height = getheight(currnode->left);
   int right_height = getheight(currnode->right); ;

   if(currnode->left != nullptr){
    (currnode->left)->height = left_height ;
   }
   if(currnode->right != nullptr){
    (currnode->right)->height = right_height ;
   }
  return (1+max(left_height,right_height));
}

template<typename T>
void Heap<T>::Heapify_down(TreeNode<T> *currNode) {
  if(currNode == nullptr){
    return ;
  }
  else if(currNode->left == nullptr && currNode->right == nullptr){
    return ;
  }
  else{
    int left_rating ;
    int right_rating;
    int node_rating = (currNode->object).rating;
    if(currNode->right == nullptr){
      left_rating = (currNode->left->object).rating ;
      //right_rating = (currNode->right->object).rating ;
      TreeNode<T> *node ;
      if(node_rating < left_rating){
        swap(currNode,currNode->left);
      }
      Heapify_down(currNode->left);
    }
    else{
      TreeNode<T> *node ;
      left_rating = (currNode->left->object).rating ;
      right_rating = (currNode->right->object).rating ;
      if(right_rating > left_rating){
        node = currNode->right;
      }
      else {
        node = currNode->left ;
      }
      int newnode_rating = (node->object).rating ;
      if(node_rating < newnode_rating){
        swap(currNode,node);
      }
      Heapify_down(node);
    }
  }

}

template<typename T>
void Heap<T>::Heapify_up(TreeNode<T> *currNode){
  if(currNode == nullptr)return ;
  else if(currNode->left == nullptr && currNode->right == nullptr){
    Heapify_up(currNode->parent);
    return ;
  }
  else{
    int left_rating ;
    int right_rating ;
    int node_rating = (currNode->object).rating;
    if(currNode->right == nullptr){
      left_rating = (currNode->left->object).rating ;
      if(node_rating < left_rating){
        swap(currNode,currNode->left);
      }
      Heapify_up(currNode->parent);
      return ;
    }
    else {
      left_rating = (currNode->left->object).rating ;
      right_rating = (currNode->right->object).rating ;
      TreeNode<T> *node ;
      if(left_rating < right_rating){
        node = currNode->right ;
      }
      else{
        node = currNode->left ;
      }
      int newnode_rating = (node->object).rating ;
      if(newnode_rating > node_rating){
        swap(currNode,node);
      }
      Heapify_up(currNode->parent);
      return ;
    }

  }
}

template<typename T>
TreeNode<T>* Heap<T>::findlast_insert(){
  if(root == nullptr){
    return nullptr ;
  }
  else{
    TreeNode<T> *d = new TreeNode<T>();
    d = root ;
    while(d!=nullptr){
      int k = d->right->height ;
      int l = d->left->height ;
      if(k < l){
        d = d->right ;
      }
      else if(k==l){
        d = d->left ;
      }
    }
    return d ;
  }
}

template<typename T>
void Heap<T>::insert(T obj) {
  if(root == nullptr){ 
    TreeNode<T> *node = new TreeNode<T>(obj);
    free_index = 0 ;
    num_levels = 1 ;
    root = node ;
    root->height = getheight(root);
    return ;
  }
  else{
    TreeNode<T> *currNode ;
    currNode = root ;
    TreeNode<T> *node = new TreeNode<T>(obj);
    TreeNode<T> *parent;
    int N ;
    N = num_levels ;
    int array[N];
    int k ;
    int index = free_index;
    for( k = N-1 ; k >= 0 ; k-- ){
      array[k] = index%2;
      index = index/2;
    }
    while(k != N-2){
      k++;
      if(array[k] != 0) {
        currNode = currNode->right ;
      }
      else {
        currNode = currNode->left ;
      }
    }
    if(array[k+1] != 0){ 
      currNode->right = node; 
    }
    else {
      currNode->left = node;
    }
    node->parent = currNode;
    root->height = getheight(root);
    Heapify_up(node);
    free_index++;
    int i = 1;
    int j = 0;
    for(j=0 ; j<num_levels ; j++){
      i = i*2 ;
    }
    if(free_index == i){
      free_index = 0;
      num_levels++; 
    }
    return;
  }
  // insert your code here
  
}

template<typename T>
void Heap<T>::delMax(){
  TreeNode<T>* currNode = root;
  if(free_index != 0){
    free_index--;
  }
  else {
    num_levels--; 
    int i = 1;
    int j = 0;
    for(j=0 ; j<num_levels ; j++){
      i = i*2 ;
    }
    free_index = i-1;
  }
  int N = num_levels ;
  int array[N];
  int k = N-1;
  int index = free_index;
  for( k = N-1 ; k>=0 ; k-- ){
    array[k] = index%2;
    index = index/2;
  }
  while(k != num_levels-1){
    k++;
    if(array[k] != 0) {
      currNode = currNode->right;
    }
    else {
      currNode = currNode->left;
    }
  }
  root->object = currNode->object;
  if(currNode == root){
    root = nullptr ;
    return ;
  }
  else{
    if(currNode->parent->left != currNode) {
    currNode->parent->right = nullptr;
    root->height = getheight(root);
    }
    else {
      currNode->parent->left = nullptr;
      root->height = getheight(root);
    }  
    Heapify_down(root);
    return;
  }
    
  // insert your code here
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node){
  print_heap(" ");
}

  

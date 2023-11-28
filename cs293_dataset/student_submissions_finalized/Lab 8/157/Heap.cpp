#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root==nullptr){
    root= new TreeNode<T>(obj);
    tail= new TreeNode<T>(obj);
  }
  else if(tail->left==nullptr){
    tail->left= new TreeNode<T>(obj);
    tail->left->parent=tail;
    maxHeapify(tail->left);
  }
  else{
    tail->right=new TreeNode<T>(obj);
    tail->right->parent=tail;
    maxHeapify(tail->right);
    TreeNode<T> * prevtail=tail;
    setTail(tail);
    tail->prevT=prevtail;
  }
  size++;
  return;
}
template<typename T>
void Heap<T>::setTail(TreeNode<T>* node){
  if(node->parent==nullptr){
    tail=node;
    while(tail->left!=nullptr){
      tail=tail->left;
    }
  }
  else if(node->parent->left==node){
    tail=node->parent->right;
    while(tail->left!=nullptr){
      tail=tail->left;
    }
  }
  else if(node->parent->right==node){
    setTail(node->parent);
  }
}
//heapify for insertion
template<typename T>
void Heap<T>::maxHeapify(TreeNode<T>* node){
  if(node->parent!=nullptr){
    if(node->parent->object<node->object){//COMPARISON
    //If parent node is less than current node, swap them
      swap(node->parent->object,node->object);
      maxHeapify(node->parent);
      //Perform maxHeapify recursively on parent node and keep on swapping
      //it with current node if it is less till root is reached or greater than
      //condition is encountered
    }
  }
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  if(root==nullptr){ return NULL;}
  if(tail==root){
    T res=root->object;
    tail=nullptr;
    root=nullptr;
    return res;
  }
  else{
    T res=root->object;
    if(tail->right!=nullptr){
      swap(tail->right->object,root->object);
      tail->right=nullptr;
      ogmaxheapify(root);
    }
    else if(tail->left!=nullptr){
      swap(tail->left->object,root->object);
      tail->left=nullptr;
      ogmaxheapify(root);
    }
    else{
      tail=tail->prevT;
      delMax();
      size++;
    }

  }
  size--;
  return res;
}
//Usual Heapify function
template<typename T>
void Heap<T>::ogmaxheapify(TreeNode<T> * node){
  if(node==nullptr||node->left==nullptr){return;}
  TreeNode<T> * maxnode=node->left;
  if(node->right!=nullptr && maxnode->object<node->right->object){//COMPARISON
    maxnode=node->right;
  }
  if(node->object<maxnode->object){//COMPARISON 
    swap(node->object,maxnode->object);//swap nodes
    ogmaxheapify(maxnode); //Recursively call heapify on swapped node
  }
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

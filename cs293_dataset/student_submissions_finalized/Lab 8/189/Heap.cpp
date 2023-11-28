#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template<typename T>
void heapify(TreeNode<T> * Node){
  if(Node==nullptr){
    return;
  }
  else if(Node->left==nullptr&&Node->right==nullptr){
    return;
  }
  else if(Node->left!=nullptr&&Node->right==nullptr){
    if(Node->object<Node->left->object){
      TreeNode<T> * tempNode=Node;
      TreeNode<T> * tempNodeLeft=Node->left;
      Node->object=tempNodeLeft->object;
      Node->left=tempNodeLeft->left;
      Node->right=tempNodeLeft->right;
      Node->parent=tempNode;
      tempNode->left=Node;
      heapify(Node);
      
    } 
  }
  else if(Node->left!=nullptr&&Node->right!=nullptr){
    if(Node->object<Node->left->object||Node->object<Node->right->object){
      if(Node->left->object<Node->right->object){
        TreeNode<T> * tempNode=Node;
        TreeNode<T> * tempNodeLeft=Node->left;
        Node->object=tempNodeLeft->object;
        Node->left=tempNodeLeft->left;
        Node->right=tempNodeLeft->right;
        Node->parent=tempNode;
        tempNode->left=Node;
        heapify(Node);
      }
      else{
        TreeNode<T> * tempNode=Node;
        TreeNode<T> * tempNodeRight=Node->right;
        Node->object=tempNodeRight->object;
        Node->left=tempNodeRight->left;
        Node->right=tempNodeRight->right;
        Node->parent=tempNode;
        tempNode->right=Node;
        heapify(Node);
      }
    }
  }
}
template<typename T>
void Heap<T>::Insert(T obj,TreeNode<T> *Node){
  if(Node==nullptr){
    Node->object=obj;
    Node->left=nullptr;
    Node->right=nullptr;
    Node->parent=nullptr;
  }
  else if(Node->left==nullptr&&Node->right==nullptr){
    Node->left->object=obj;
    Node->left->left=nullptr;
    Node->left->right=nullptr;
    Node->left->parent=Node;
  }
  else if(Node->left!=nullptr&&Node->right=nullptr){
    Node->right->object=obj;
    Node->right->left=nullptr;
    Node->right->right=nullptr;
    Node->right->parent=Node;
  }
  else if(Node->left!=nullptr&&Node->right!=nullptr){

  }

}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root==nullptr){
    root->object=obj;
    root->left=nullptr;
    root->right=nullptr;
    root->parent=nullptr;
  }

  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <cmath>

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root==nullptr){
    root = new TreeNode<T>(obj);
    nodes++;
    return;
  }
  //adding at the position of (nodes+1), so find (nodes+1) in base 2
  int num = 0; //stores number of digits in the required binary number
  int m = nodes+1;
  while(m!=0){
    m/=2;
    num++;
  }
  int q = nodes+1;
  int arr[num]; //stores digits of "bin"
  int i = 0;
  while(q!=0){
    arr[i] = q%2;
    q/=2;
    i++;
  }
  TreeNode<T> *currNode = root;
  TreeNode<T> *parent = nullptr;
  int t;
  for(int i=0; i<num-1; i++){
    parent=currNode;
    int b = arr[num-2-i];
    if(b==0){
      if(i==num-2) t=0;
      currNode=currNode->left;
    }
    else{
      if(i==num-2) t=1;
      currNode=currNode->right;
    }
  } //going to the first empty node
  currNode = new TreeNode<T>(obj); //initiate this node and its parent, and parent's child becomes this node
  currNode->parent = parent;
  if(t==0){
    parent->left = currNode;
  }
  else{
    parent->right = currNode;
  }
  while(currNode->parent!=nullptr){ //now we satisfy the heap property
    if(currNode->object < currNode->parent->object) break;
    T temp = currNode->object;
    currNode->object = currNode->parent->object;
    currNode->parent->object = temp;
    currNode = currNode->parent;
  }
  nodes++; //number of nodes increase by 1
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(nodes==0) return;
  if(nodes==1){
    root=nullptr;
    return;
  }
  //deleting the position of nodes, so find nodes in base 2
  int num = 0; //stores number of digits in the required binary number
  int m = nodes;
  while(m!=0){
    m/=2;
    num++;
  }
  int q = nodes;
  int arr[num]; //stores digits of "bin"
  int i = 0;
  while(q!=0){
    arr[i] = q%2;
    q/=2;
    i++;
  }
  TreeNode<T> *currNode = root;
  int t;
  for(int i=0; i<num-1; i++){
    int b = arr[num-2-i];
    if(b==0){
      if(i==num-2) t=0;
      currNode=currNode->left;
    }
    else{
      if(i==num-2) t=1;
      currNode=currNode->right;
    }
  } //going to the last node
  root->object = currNode->object; //root is max, so it is removed and root gets value of last node
  //last node becomes null
  if(t==0){
    currNode->parent->left=nullptr;
  }
  else{
    currNode->parent->right=nullptr;
  }
  currNode=nullptr;
  //now we have to satisfy the heap property
  TreeNode<T> *curr = root;
  while(curr!=nullptr){
    if(curr->left==nullptr && curr->right==nullptr){
      break;
    }
    if(curr->left!=nullptr && curr->right==nullptr){
      T left = curr->left->object;
      T current = curr->object;
      if(left < current) break;
      T temp = left;
      curr->left->object = current;
      curr->object = temp;
      curr = curr->left;
    }

    //if left child is nullptr, right will be nullptr due to heap property
    
    if(curr->left!=nullptr && curr->right!=nullptr){
      T left = curr->left->object;
      T right = curr->right->object;
      T current = curr->object;
      if(left < current && right < current) break;
      if(left < right){
        T temp = right;
        curr->right->object = current;
        curr->object = temp;
        curr = curr->right;
      }
      else{
        T temp = left;
        curr->left->object = current;
        curr->object = temp;
        curr = curr->left;
      }
    }
  }
  nodes--;
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  // insert your code here
  printBST("", false, node);
  return;
}

template<typename T>
void Heap<T>::printBST(const string& prefix, bool isLeft, TreeNode<T> *node){
    if( node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << node->object << endl;
        TreeNode<T> *curr = node;
        node = node->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true, node);
        node = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false, node);
        node = curr;
    }
}


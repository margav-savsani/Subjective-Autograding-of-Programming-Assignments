#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
template<typename T>
TreeNode<T>* last;
template<typename T>
void swap(TreeNode<T>* node1,TreeNode<T>* node2){
  T temp=node1->object;
  node1->object=node2->object;
  node2->object=temp;
  return;
}
template<typename T>
void heapify(TreeNode<T>* root){
  TreeNode<T>* largest=root;
  if(root == nullptr) return;
  if(root->left == nullptr && root->right==nullptr){
    return;
  }
  if(root->left != nullptr && root->right == nullptr){
    if(root->object < root->left->object){
      swap(root,root->left);
    }
  }
  if(root->left != nullptr && root->right != nullptr){
    T temp1=root->object;
    T temp2=root->left->object;
    T temp3=root->right->object;
    if(temp2>temp1){
      largest=root->left;
    }
    if(temp3>temp1){
      largest=root->right;
    }
    if(largest!=root){
      swap(root->left,largest)
      heapify(largest);
    }
  }
}
template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  
  return;
}

template<typename T>
T Heap<T>::delMax() {

  // insert your code here
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

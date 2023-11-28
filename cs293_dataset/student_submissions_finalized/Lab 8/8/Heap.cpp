#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){

}

template<typename T>
void join(TreeNode<T> *parent, TreeNode<T> *child, bool isLeft = true){

}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if (root == nullptr)
  {
    TreeNode<T> *tempNode = new TreeNode<T>(obj);
    root = tempNode; 
    rightMostNode_parent = tempNode;
    return;
  }

  // else if (root->left == nullptr && root->right == nullptr)
  // {
  //   if (root -> object > T ) //modify
  //   {
  //     root ->  
  //   }
    
  // }
  TreeNode<T> *tempNode = new TreeNode<T>(obj);

    

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


  
//
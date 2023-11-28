#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T>* lastElem = getLastElem(root); 


  return;
}

template<typename T>
void Heap<T>::delMax() {
    // Get the last element
    TreeNode<T>* lastElem = getLastElem(root); 
    // Replace root with last element
    swap(root, LastElem);
    lastElem->parent = NULL;
    heapify(root);
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  cout<<node->object<<" ";
  if (node->left != NULL){
    printHeap(node->left);
  }
  if (node->right != NULL){
    printHeap(node->right);
  }
  return;
}
// To swap the data of two nodes
template<typename T>
void Heap<T>::swap(TreeNode<T> *first, TreeNode<T> *second){
  T temp = first->object;
  first->object = second->object;
  second->object = temp;
}
// to compare two objects
template<typename T>
bool Heap<T>:: isGreater(T first, T second){
  return  (first->object > second->object);
}

//To heapify two heaps
template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){
  if (node==NULL){
    return;
  }
  TreeNode<T> * largest = node;
  TreeNode<T> * left = node->left;
  TreeNode<T> * right = node->right;

  if (left != NULL && left->object > largest->object){
    largest = left;
  }

  if (right != NULL && right->object > largest->object){
    largest = right;
  }

  if (largest!=node){
    swap(largest, node);
  }
}
template<typename T>
TreeNode<T> * Heap<T>::getLastElem(TreeNode<T>* node){
  return;
}

//MAINTAIN LAST ELEMENT POINTER WHILE INSERTING !!!
  

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif


template<typename T>
void Heap<T>::setTail(TreeNode<T> *node){

    if(node->parent == nullptr){
        tail = node;
        while(tail->left != nullptr){
            tail = tail->left;
        }
    }

    else if(node->parent->left == node){
        tail = node->parent->right;
        while(tail->left != nullptr){
            tail = tail->left;
        }
    }
    else if(node->parent->right == node){
        setTail(node->parent);
    }
}

template<typename T>
void Heap<T>::swapNodeData(TreeNode<T>* a, TreeNode<T>* b){
    int temp = a->object;
    a->object = b->object;
    b->object = temp;
}

template<typename T>
void Heap<T>::maxHeapify(TreeNode<T>* node){
    if(node->parent != nullptr){
        if(node->parent->object < node->object){
            swapNodeData(node->parent, node);
            maxHeapify(node->parent);
        }
    }
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
    if(root == nullptr){
        root = new TreeNode<T>(obj);
        tail = root;
    }
    else if(tail->left == nullptr){
        tail->left = new TreeNode<T>(obj);
        tail->left->parent = tail;
        maxHeapify(tail->left);
    }else {
        tail->right = new TreeNode<T>(obj);
        tail->right->parent = tail;
        maxHeapify(tail->right);
        TreeNode<T> *prevTail = tail;
        setTail(tail);
        tail->prevTail = prevTail;
    }
    size++;
  return;
}

template<typename T>
void Heap<T>::revMaxHeapify(TreeNode<T>* node){
    if(node == nullptr || node->left == nullptr)
      return;
    TreeNode<T>* min = node->left;
    if(node->right != nullptr && min->object < node->right->object){
        min = node->right;
    }
    if(min->object > node->object){
        swapNodeData(node, min);
        revMaxHeapify(min);
    }
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(root == nullptr) {
      return;
  }
  if(tail == root){
      tail = nullptr;
      root = nullptr;
      return;
  }
  else {
      if (tail->right != nullptr){
          swapNodeData(tail->right, root);
          tail->right = nullptr;
          revMaxHeapify(root);
      }
      else if(tail->left != nullptr) {
          swapNodeData(tail->left, root);
          tail->left = nullptr;
          revMaxHeapify(root);
      }
      else {
          tail = tail->prevTail;
          delMax();
          size++;
      }
  }
  size--;

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  // insert your code here
  return;
}

  

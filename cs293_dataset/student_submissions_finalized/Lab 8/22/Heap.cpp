#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"


template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == nullptr)
  {
    root = new TreeNode<T>(obj);
    lastNode = root;
    return;
  }
  else
  {
    TreeNode<T>* tmp = lastNode->parent;

    while(tmp->parent !=nullptr)
    {
      if(tmp->right == nullptr)
      {
        TreeNode<T>* newNode = new TreeNode<T>(obj);
        tmp->right = newNode;
        newNode->parent = tmp;
        lastNode = newNode;
      }
      else tmp = tmp->parent;
    }
    tmp = tmp->right;
    while(tmp->left!= nullptr)
    {
      tmp = tmp->left;
    }
    TreeNode<T>* newNode = new TreeNode<T>(obj);
    tmp->left = newNode;
    newNode->parent = tmp;
    lastNode = newNode;

    tmp = lastNode;
    while(tmp!=nullptr)
    {
      if(tmp->object > tmp->parent->object)
      {
        T t = tmp->object;
        tmp->object = tmp->parent->object;
        tmp->parent->object = t;
        tmp = tmp->parent;
      }
      else break;
    }
  }

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

template<typename T>
TreeNode<T> Heap<T>::getLast()
{
  return this.lastNode;
}

#endif 

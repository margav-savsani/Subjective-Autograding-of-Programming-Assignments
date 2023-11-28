#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here
  TreeNode<T> newnode(obj);
  TreeNode<T> *arr;
  
  this->H[this->n] = val;
  int i = this->n;
  this->n += 1;
  while (i != 0 && this->H[this->parent(i)] > this->H[i])
  {
    this->H[i],
    this->H[this->parent(i)] = this->H[this->parent(i)], this->H[i];
    i = this->parent(i);
  }
  return;
}

template <typename T>
T Heap<T>::delMax()
{
  TreeNode<T> last;
  root->object = last->object;
  // insert your code here
  Heapify(root);
  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

  // insert your code here

  return;
}
template <typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{
  return;
}

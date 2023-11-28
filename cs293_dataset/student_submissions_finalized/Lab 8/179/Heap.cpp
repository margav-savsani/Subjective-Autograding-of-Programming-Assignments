#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  

  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::heapify(T obj) {
  int largest = obj->object;
  int left = 2 * (obj->object) + 1;
  int right = 2 * (obj->object) + 2;
  if (left < n && arr[left] > arr[largest])
    largest = left;

  if (right < n && arr[right] > arr[largest])
    largest = right;

  if (largest != i) {
      swap(&arr[i], &arr[largest]);
      obj->object = largest
      heapify(T obj);
  }     
  return;
}

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

  int lastElement = arr[n - 1];
 
    // Replace root with last element
    arr[0] = lastElement;
 
    // Decrease size of heap by 1
    n = n - 1;
 
    // heapify the root node
    heapify(arr, n, 0);

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";

  return;
}

  

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
	if (node == nullptr) return;
	else {
		printHeap(node->left);
		cout << node->object << endl;
		printHeap(node->right);
	}
	// insert your code here

	return;
}

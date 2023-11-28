#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>

void Heap<T>::Heapify(TreeNode<T> *node){
  if(node==NULL)
    return;
  if((node->object<node->left->object) || (node->object < node->right->object)){
    TreeNode<T> *x = node;
    if(node->left->object>node->right->object){
      node->object=node->left->object;
      node->left->object=x->object;
      Heapify(T->left);
    }
    else{
      node->object=node->right->object;
      node->right->object=x->object;
      Heapify(T->right);
    }
  }
  else
    return;
}

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

  if(node==NULL)
    return;
  cout << node->object << " " << endl;
  printHeap(node->left);
  printHeap(node->right);

}

  

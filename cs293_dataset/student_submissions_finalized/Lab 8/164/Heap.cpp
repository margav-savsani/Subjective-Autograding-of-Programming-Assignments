#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  TreeNode<T> *r=root;
  if (r==nullptr)
  {
    r= new TreeNode(obj);
    return;
  }
  while (obj<=r->object)
  {
    if (r->left!=nullptr && r->right!=nullptr)
    {
      r=r->right;
      continue;
    }
    if(r->left==nullptr)
    {r->left= new TreeNode(obj);
    return;}
    if (r->right==nullptr)
    {
      r->right= new TreeNode(obj);
      return;
    }
  }
  while (r==nullptr)
  {
    
  }
  


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

  

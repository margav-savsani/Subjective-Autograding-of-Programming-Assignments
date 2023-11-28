#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
   TreeNode<T> *newnode(obj);
  //  if (last == nullptr){ root = newnode ;
  //     last = root;}

   getlast();
   TreeNode<T>  *x = newnode ;

   while (x->parent->object < x->object){
      TreeNode<T> * temp = x;
      x->object= x->parent->object;
      x->parent->object= temp->object
      x= x->parent ;

   }
  
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::delMax() {
  //  static  TreeNode<T> *  last;

  TreeNode<T> * max = root;
   TreeNode<T> *  last =get last();
   root ->object = last->object;
    TreeNode<T> * x =root;
  if (x->object < max ( x->left->object , x->right->object)){
     TreeNode<T> * change;
     if (x->left->object> x->right->object)
        change = x->left;
    else change = x->right;
    TreeNode<T> * temp = x;
      x->object= change->object;
      change->object= temp->object
      x= change  ;
      
  }

  
  // insert your code here

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

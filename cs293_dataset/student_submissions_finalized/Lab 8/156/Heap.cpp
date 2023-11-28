#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"


template<typename T>
void Heap<T>::swapdata(TreeNode<T> *A,TreeNode<T> *B){
  T temp = A->object;
  A->object = B->object;
  B->object = temp; 
}

template<typename T>
void Heap<T>::Heapify(TreeNode<T> *node){
  if(node->parent!=nullptr){
    if(node->parent->object < node->object){
      swapdata(node,node->parent);
      Heapify(node->parent);
    }
  }
} 

template<typename T>
void Heap<T>::taleoftail(TreeNode<T> *node){
  //if(node)
}

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here

  if(root==nullptr){
    root = new TreeNode<T>(obj);
    tail = root;
  }

  else if(tail->left==null){
    tail->left = new TreeNode<T>(obj);
    tail->left->parent = tail;
    Heapify(tail->left);
  }
  else{
    tail->right = new TreeNode<T>(object);
    tail->right->parent = tail;
    //Heapify has to be called after inerting a node so that it continues
    //to follow the heap properties.
    Heapify(tail->right);
    //In this case we would also need the update the tail pointer and the 
    //prevTail value of the new tail to the previous tail to facilitate in the
    //delete max function
    //let us do this by making a function
    TreeNode<T> *temp = tail;
    //this function updates the value of the tail
    taleoftail(tail);
    //set prevTail for the new value of the tail node
    tail->prevTail = temp;
  }

  size++;
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

#endif

/*size++;
    int i=-1,size_curr;
    while(size_curr!=0){
      size_curr = size_curr/2;
      i++;
    }
    //Now the variable i has the level number of the new node to be entered
    int pres_at = pow(2,l)-((pow(2,i+1)-1)-size);
    double x = pres_at/pow(2,i);
    int parent_at = ceil(x*round(pow(2,i-1)));*/
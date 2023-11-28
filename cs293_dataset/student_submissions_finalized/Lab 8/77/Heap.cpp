#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include <cmath>
template <typename T>
void Heap<T>::insert(T obj)
{
  
  // insert your code here
  if (root == NULL)
  {
    root = new TreeNode<T>( obj);

  }
  else if (root->left == NULL)
  {
    Heap *leftpart = new Heap();
    leftpart->insert(obj);
    leftpart->root->parent=root;
    
  }
  else if (root->right == NULL)
  {
    Heap *rightpart = new Heap();
    rightpart->insert(obj);
    rightpart->root->parent=root;
  }
  else
  {
    int x= floor(log(root->count)/log(2));
    int max_inleft= pow(2,x-1);
    if((max_inleft + pow(2,x)) >= (root->count +1)){
      Heap *rightpart = new Heap();
      rightpart->root=root->right;
      rightpart->insert(obj);
    }
    else {
      Heap *leftpart = new Heap();
      leftpart->root=root->right;
      leftpart->insert(obj);
    }
  }
  root->count++;
  
  return;
}

template <typename T>
void Heap<T>::Heapify(){
  /*
  bool leftAndRoot = false;
  if(root->left->object < root->object){
    leftAndRoot=true;
  }
  bool rightAndRoot =false;
  if(root->right->object < root->object){
    rightAndRoot=true;
  }
  bool leftAndRight=false;
  if(root->right->object > root->left->object){
    leftAndRight=true;
  }
  if(leftAndRoot && rightAndRoot){
    left.Heapify();
  }*/

}

template <typename T>
void Heap<T>::delMax()
{
    Heapify();
  // insert your code here

  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

  // insert your code here

  return;
}

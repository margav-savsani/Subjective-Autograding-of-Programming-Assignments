#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  if(root == NULL){
    root = new Treenode(T obj);
  }
  if( root != NULL){
    if(root->object < obj->object){
     obj->left = root;
     obj->right = root->left;
     (obj->left)->left = root->left;
     root = obj;
  }    

  return;
}

template<typename T>
void Heap<T>::delMax() {
  if(root != NULL){
    
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

template<typename T>
void Heap<T>::max_heapify (int Arr[ ], int i, int N){
    int largest;
    int left = 2*i  ;                 //left child
    int right = 2*i +1  ;         //right child
    if(left<= N and Arr[left] > Arr[i] )
          largest = left;
    else
         largest = i;
    if(right <= N and Arr[right] > Arr[largest] )
        largest = right;
    if(largest != i )
    {
        swap (Ar[i] , Arr[largest]);
        max_heapify (Arr, largest,N);
    } 
 }

template<typename T>
void build_maxheap (int arr[])
{
    for(int i = N/2 ; i >= 1 ; i-- )
    {
        max_heapify (arr, i) ;
    }
}

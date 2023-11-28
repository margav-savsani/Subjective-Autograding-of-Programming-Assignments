#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

//declaring some global variables
int size = 0; //size of the heap till now
//declared global variables

template<typename T>
void shift_down(TreeNode<T>* p, int i)
{
  int maxindex_i = i;
  TreeNode<T>* maxindex_p;
  maxindex_p = p;

  //left child
  int left_i = 2*i;
  TreeNode<T>* left_p;
  left_p = p->left;

  if(left_i <= size && p->object > )
}

template<typename T>
void swap_objects(TreeNode<T>* a, TreeNode<T>* b)
{
  T temp;
  temp = a->object;
  a->object = b->object;
  b->object = temp;
}

template<typename T>
void Heap<T>::insert(T obj) 
{
  // insert your code here
  size++;
  //this is the new size and also the index of the new node to be inserted first

  //convert to binary from elements 0 to bin_idx-1
  int bin_arr[arr_size]; //assuming the size of binary number doesn't exceed this
  int bin_idx = 0;   //counter for binary array
  int dum_size = size; //dummy size

  while(dum_size > 0)
  {
    bin_arr[bin_idx] = size%2;
    size = size%2;
    bin_idx++;
  }
  //converted to binary to understand left and right

  TreeNode<T>* new_node = new TreeNode<T>(obj);
  TreeNode<T>* curr;
  curr = root;
  
  if(root == NULL) root = new_node;
  else
  {
    for(int j = bin_idx-2; j > 0; j--)
    {
      if(bin_arr[j] == 0) curr = curr->left;
      else curr = curr->right;
      if(j == 1)
      {
        if(bin_arr[0] == 0) curr->left = new_node;
        else curr->right = new_node;
      } 
    }
  }
  return;
}

template<typename T>
void Heap<T>::delMax() 
{
  // insert your code here
  //first we have to find the last node to swap with root

  //convert to binary from elements 0 to bin_idx-1
  int bin_arr[arr_size]; //assuming the size of binary number doesn't exceed this
  int bin_idx = 0;   //counter for binary array
  int dum_size = size; //dummy size

  while(dum_size > 0)
  {
    bin_arr[bin_idx] = size%2;
    size = size%2;
    bin_idx++;
  }
  //converted to binary to understand left and right

  TreeNode<T>* last_node;
  last_node = root;

  for(int j = bin_idx-2; j > 0; j--)
  {
    if(bin_arr[j] == 0) last_node = last_node->left;
    else last_node = last_node->right;
  }

  swap_objects(root, last_node);

  size--;

  shift_down(root, 1);

  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) 
{
  // insert your code here

  return;
}

  

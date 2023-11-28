#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {   //This is the code to insert in the heap
  // insert your code here
  // we insert the element at just after the bottom right node if it is not a complete binary tree
  // else we insert it at the bottom left position and increase height by 1
  // This is followed by heapify
  int height = 0;
  int heapsize;
  //complete binary tree has pow(2,h+1) - 1 nodes
  int difference = heapsize - pow(2,height) + 1;
  // this is the number of nodes on the bottom row of the tree
  int diffmax = pow(2,height); //max possible difference
  TreeNode** arr;
  arr = new TreeNode*[heapsize+1];  //array of pointers
  arr[0] = root;
  arr[1] = root->left;
  arr[1]->parent = root;
  arr[2] = root->right;
  arr[2]->parent = root;

  //through this loop we initialize our array of pointers of the nodes of heap
  for (int i = 3; i < heapsize; i++)   
  {
    if(i%2 == 0) {
      int paront = (i-2)/2; //this is the index of the parent
      TreeNode* p = arr[paront];
      arr[i] = p->right;
      arr[i]->parent = p;
    }
    else {
      int paront = (i-1)/2; //index of the parent
      TreeNode* p = arr[paront];
      arr[i] = p->left;
      arr[i]->parent = p;
    }
  }

  if(root == nullptr){
    root->object = obj;
  }
  TreeNode* x = root;
  while(x->left != nullptr){    //this loop gives us the height
    height++;
    x = x->left;
  }
  
  arr[heapsize]->object = obj; //inserting the object at last position
  //Now we heapify

  TreeNode* alpha;
  if(heapsize%2 == 0) alpha = arr[(heapsize-2)/2];
  else alpha = arr[(heapsize-1)/2];

  while (obj > alpha->object && alpha != root) {             //swapping 
    T temp = arr[alpha]->object;
    arr[alpha]->object = arr[heapsize]->object;
    arr[heapsize]->object = temp;
    alpha = alpha->parent;
  }

  return;
}

template<typename T>
void Heap<T>::delMax() {    
  //We have implemented the priority queue as a max heap 
  //Thus the max element is at the root of the tree (property of max heap)
  //We just have to delete the root
  //and heapify the remaining tree so that max heap property is satisfied
       
  //We replace the bottom right element with the root and delete it
  //Then we heapify the rest of the heap/tree
  int height = 0;
  int heapsize;   //stores the size of the heap
  TreeNode* x = root;
  while(x->left != nullptr){
    height++;
    x = x->left;
  }
  //now we have the height of the tree
  
  TreeNode** arr;
  arr = new TreeNode*[heapsize];  //array of pointers
  arr[0] = root;
  arr[1] = root->left;
  arr[1]->parent = root;
  arr[2] = root->right;
  arr[2]->parent = root;

  //through this loop we initialize our array of pointers of the nodes of heap
  for (int i = 3; i < heapsize; i++)   
  {
    if(i%2 == 0) {
      int paront = (i-2)/2; //this is the index of the parent
      TreeNode* p = arr[paront];
      arr[i] = p->right;
      arr[i]->parent = p;
    }
    else {
      int paront = (i-1)/2; //index of the parent
      TreeNode* p = arr[paront];
      arr[i] = p->left;
      arr[i]->parent = p;
    }
  }
  //replacing root with object of bottom right node and then deleting it

  T beta = arr[heapsize-1]->object;
  arr[0]->object = beta;
  arr[heapsize-1] = nullptr;

  //now we heapify




  
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

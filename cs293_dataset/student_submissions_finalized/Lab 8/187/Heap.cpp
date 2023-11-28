#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#include<vector>
#endif
template<typename T>
// void Heapify(TreeNode<T> *x){
//       if(x == nullptr){
//         return;
//       }
//       else{
//       <T> a = max(x->left->object, x->right->object);
//       if(x->object < a){
//         if(a == x->right->object){
//           <T> b;
//           b = x->right->object;
//           x->right->object = x->object;
//           x->object = b;
//           Heapify(x->right);
//         }
//         else if(a == x->left->object){
//           b = x->left->object;
//           x->left->object = x->object;
//           x->object = b;
//           Heapify(x->left);
//         }
//       }
//     }

int count = 0;
template<typename T>
void Heap<T>::insert(T obj) {
  TreeNode<T> *x;
  TreeNode<T> *x1;
  TreeNode<T> *z;
  vector<int> arr;
  int i = 0;
  int y = count;
  arr = new int();
  x1 = new TreeNode<T>(obj);
  x = root;
  if(root == nullptr){
    root = x1;
    count++;
  }
  while(y != 1){
    y = y/2;
    arr.push_back(y%2);
    i++;
  }
  arr = arr.reverse(0,i-1);
  int j=0;
  for(int i=0;i<arr.size();i++){
    z = x;
    if(arr[j] == 0){
      x = x->left;
    }
    else{
      x = x->right;
    }
  }
  if(z->left == nullptr){
    z->left = x1;
    x1->parent = z;
    count++;
  }
  else{
    z->right = x1;
    x1->parent = z;
    count++;
  }
  for(int i=0;i<arr.size();i++){
    if(x1->object > x1->parent->object){
      <T> c;
      c = x->object;
      x->object = x->parent->object;
      x->parent->object = c;
    }
  }
  return;
  }

template<typename T>
T Heap<T>::delMax() {
  
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here

  return;
}

  

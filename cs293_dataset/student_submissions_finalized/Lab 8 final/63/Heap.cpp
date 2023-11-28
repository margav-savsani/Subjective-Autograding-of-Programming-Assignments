#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {     
  if (h == 0){
    root = new TreeNode<T>(obj);      
    h++;
    N++;
    flag = 1;
    return;
  }
  if (flag){
    h++;
    flag = 0;
  }
 
  int n = N+1;
  int k = 0;
  bool * a = new bool[h-1];
  for (int i = h-2; i >=0 ; i--){     // finding the path to the last element
    if (n%2 == 0){
      a[i] = 0;
    }
    else {
      k++;
      a[i] = 1;
    }
    n /= 2;
  }
 
  if (k == h-1){
    flag = 1;
  }
  TreeNode<T> * A = root;
  for (int i = 0; i < h-2; i++){    // going to the parent of element to be inserted
    if (!a[i]){
      A = A->left;
    }
    else {
      A = A->right;
    }
  }
  if (!a[h-2]){             // insert the elements
    A->left = new TreeNode<T>(obj);
    A->left->parent = A;
    A = A->left;
  }
  else {
    A->right = new TreeNode<T>(obj);      
    A->right->parent = A;
    A = A->right;
  }
  N++;
  T obj1;
  while (true){         // restore the heap condition
    if (A->parent == nullptr){
      return;
    }
    if (A->object < A->parent->object){
      return;
    }
    obj1 = A->parent->object;
    A->parent->object = A->object;
    A->object = obj1;
    A = A->parent;
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {    // deletes the first element of the heap
  if (h == 0){
    N--;
    return;
  }
  if (flag){
    flag = 0;
  }

  int n = N;
  int k = 0;
  bool * a = new bool[h-1];
  for (int i = h-2; i >=0 ; i--){     // finding the path to the last element
    if (n%2 == 0){
      k++;
      a[i] = 0;
    }
    else {
      a[i] = 1;
    }
    n /= 2;
  }
  int H = h;
  if (k == h-1){
    flag = 1;
    h--;
  }

  N--;
  TreeNode<T> * A = root;
  for (int i = 0; i < H-1; i++){        // going to the last element
    if (!a[i]){
      A = A->left;
    }
    else {
      A = A->right;
    }
  }
  root->object = A->object;       // switch the objects 
  if (a[H-2] == 1){
    A->parent->right = nullptr;
  }
  if (a[H-2] == 0){
    A->parent->left = nullptr;
  }
  delete A;
  heapify(root);              // heapify the heap
  return;
}




template<typename T>
void Heap<T>::heapify(TreeNode<T> *node){       // Heapify function
  if (node->left == nullptr){           // base case
    return;
  }
  else if (node->right == nullptr){     // base case
    if (node->object < node->left->object){
      T obj = node->object;
      node->object = node->left->object;
      node->left->object = obj;
    }
    return;
  }
  T objp = node->object;
  T objl = node->left->object;
  T objr = node->right->object;

  if (objp < objr){           
    if (objl < objr){
      node->object = objr;
      node->right->object = objp;
      heapify(node->right);         // recursive step
    }
    else {
      node->object = objl;
      node->left->object = objp;
      heapify(node->left);          // recursive step
    }
  }
  else if (objp < objl){
    if (objr < objl){
      node->object = objl;
      node->left->object = objp;
      heapify(node->left);          // recursive step
    }
    else {
      node->object = objr;
      node->right->object = objp;
      heapify(node->right);         // recursive step
    }
  }
  return;

}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *root) {
  static bool isLeft = 0;           // 
  static string prefix = "";
  if( root != nullptr )
    { 
      cout << prefix;
      string s = prefix;
      cout << (isLeft ? "|--" : "|__" );
      bool l = isLeft;
      // print the value of the node
      cout << root->object << endl;
      TreeNode<T> *curr = root;
      root = root->left;
      // enter the next tree level - left and right branch
      prefix += (l ? "│   " : "    "); 
      isLeft = 1;
      printHeap(root);
      root = curr->right;
      isLeft = 0;
      prefix = s + (l ? "│   " : "    "); 
      printHeap(root);
      prefix = s;
      root = curr;
    }

  return;
}



#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class TreeNode {
 public:
  T object;
  TreeNode<T> *left;
  TreeNode<T> *right;
  TreeNode<T> *parent;

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
  }
  // void print_object(){
  //   cout << object;
  // }
  
  ~TreeNode() {;}
};

template <typename T> class Heap {
  
  int total_elements;
 public:
  TreeNode<T>* root;
  Heap() {root = nullptr; total_elements = 0;}
  ~Heap() {total_elements = 0;}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};

#endif


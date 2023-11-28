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
  ~TreeNode() {;}
};

template <typename T> class Heap {
  

 public:
  TreeNode<T> *root;
  TreeNode<T> *last;
  Heap() {
    root = nullptr;
    last = nullptr;
  }
  ~Heap() {
    recursive_delete(root);
  }

  void insert(T obj);
  void recursive_delete(TreeNode<T> * node);
  void delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
 #endif


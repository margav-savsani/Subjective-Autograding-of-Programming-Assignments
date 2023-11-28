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
  TreeNode<T> *root;
  // Variable to keep track of number of nodes in the heap
  int count;
  void recursiveDelete(TreeNode<T> *node);

 public:
  Heap() {
    root = nullptr;
    count = 0;}
  ~Heap() {// to free up the space
    recursiveDelete(root);}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif


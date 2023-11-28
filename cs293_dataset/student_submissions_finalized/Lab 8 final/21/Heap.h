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
  int N = -1; // index of last node
 public:
  Heap() {root = nullptr;}
  ~Heap() {;}

  void insert(T obj);
  void heapify(TreeNode<T> *node);
  
  T delMax();
  T getMax() {return root->object;}
  TreeNode<T>* findelewithindex(int index);
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif


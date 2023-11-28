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
  int nodeIndex;
 public:
  Heap() {root = nullptr; nodeIndex = -1;}
  ~Heap() {delete root;}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  void heapify(TreeNode<T> *node);
  void myPrintHeap(TreeNode<T> *root, const string& prefix, bool isLeft);
  void swap(TreeNode<T> *first, TreeNode<T> *second);
  //  void displayAboveThresh(int thresh);
};

#endif


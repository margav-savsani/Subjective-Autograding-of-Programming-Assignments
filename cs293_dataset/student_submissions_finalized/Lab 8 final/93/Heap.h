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
  int size = 0;
 public:
  Heap() {root = nullptr;}
  ~Heap() {;}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node, string prefix = "", bool isLeft = true);
  void heapify(TreeNode<T>*);
  //  void displayAboveThresh(int thresh);
};

#endif


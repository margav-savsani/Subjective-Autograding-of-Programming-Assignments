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
  TreeNode
  ~TreeNode() {;}
};
template <typename T> class Heap {
  TreeNode<T>* root;

 public:
  Heap() {root = nullptr;}
  ~Heap() {;}

  void insert(T obj);
  void Heapify(TreeNode<T> *node);
  T delMax();
  T getMax() {return root->object;}
  void printHeap(const string& prefix, bool isLeft=false);
  //  void displayAboveThresh(int thresh);
};
#endif


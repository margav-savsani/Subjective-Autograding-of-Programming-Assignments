#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

// Node for a Binary Tree.
template <typename T> class TreeNode {
 public:
  T object;
  TreeNode<T> *left = nullptr;
  TreeNode<T> *right = nullptr;
  TreeNode<T> *parent = nullptr;

  TreeNode(const T &initObj): object(initObj) {}
  ~TreeNode(){} // the class using the Node will free up space. No heap memory is used in the node constructor itself.
};

template <typename T> class Heap {
  TreeNode<T> *root;

 public:
  Heap(): root(nullptr){}
  ~Heap(){}

  void insert(const T &obj);
  void delMax();
  T getMax() const{return root->object;} // insert your own code here if needed
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif


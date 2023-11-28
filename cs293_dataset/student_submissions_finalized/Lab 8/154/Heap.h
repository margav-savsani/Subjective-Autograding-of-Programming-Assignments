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
  TreeNode(T initObj, TreeNode<T> *parent, TreeNode<T> *left, TreeNode<T> *right) {
    object = initObj;
    this->parent = parent;
    this->left = left;
    this->right = right;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T> root;
  TreeNode<T> end;
  int count;

 public:
  Heap() {root = nullptr; end = nullptr; count =0;}
  ~Heap() {;}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  TreeNode<T>* getparent(int n);
  void Heapify(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif


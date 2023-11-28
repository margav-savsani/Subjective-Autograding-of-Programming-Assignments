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
  TreeNode<T> *lastelem;
  int no_of_elem;
 public:
  Heap() {root = nullptr; no_of_elem=0; lastelem = nullptr;}
  ~Heap() {;}

  void insert(T obj);
  T delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
  TreeNode<T> *checkempty(TreeNode<T> *node, bool &lft);
  void swap(TreeNode<T> *par, TreeNode<T> *child);
  void Heapify(TreeNode<T>* node);
};

#endif


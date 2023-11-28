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
  TreeNode<T> *parent_node;
 public:

  Heap() {root = nullptr;
  parent_node=nullptr;}
  ~Heap() {;}

  void insert(T obj);
  void make_heap(TreeNode<T> *a);
  void heapify(TreeNode<T> *a);
  void delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif



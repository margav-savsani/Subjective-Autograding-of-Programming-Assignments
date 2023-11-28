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
  public:
  int total_nodes = 0;

 public:
  Heap() {root = nullptr; total_nodes = 0;}
  ~Heap() {;}

  TreeNode<T>* getnode(int n);
  bool exchange(TreeNode<T> *node1,TreeNode<T> *node2);
  void heapfy(TreeNode<T> *node);
  void printall(){printHeap(root);}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  // void displayAboveThresh(int thresh);
};

#endif
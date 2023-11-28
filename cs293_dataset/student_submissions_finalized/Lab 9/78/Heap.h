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
  TreeNode<T> *lastnode;
  int totalnodes;

 public:
  Heap() {root = nullptr; lastnode = root; totalnodes = 0;}
  ~Heap() {;}

  void swap (TreeNode<T> *node1, TreeNode<T> *node2);
  void godown(TreeNode<T> *node);
  void heapify (TreeNode<T> *node);
  void heapifyup (TreeNode<T> *node);
  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  TreeNode<T> *getRoot(){ return root;}
  void printHeap(const string& prefix, bool isLeft=false);
  //  void displayAboveThresh(int thresh);
};

#endif


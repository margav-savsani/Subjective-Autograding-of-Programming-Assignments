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
  int nodes; //number of nodes

 public:
  Heap() {root = nullptr; nodes=0;}
  ~Heap() {;}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printBST(const string& prefix, bool isLeft, TreeNode<T> *node);
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};

#endif


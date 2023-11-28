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
  TreeNode<T> *end;

 public:
  Heap() {root = nullptr; end=nullptr;}
  ~Heap() {recursiveDelete(root); end = nullptr;}
  void recursiveDelete(TreeNode<T> *node) {
    if (node == nullptr) {
      return;
    }
    else {
      recursiveDelete(node->left);
      node->left=nullptr;
      recursiveDelete(node->right);
      node->right=nullptr;
      delete node;
      return;
    }
  }
  void Heapify();
  void insert(T obj);
  void delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};

#endif


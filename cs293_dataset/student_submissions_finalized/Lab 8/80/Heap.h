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
  TreeNode<T> *last;

 public:
  Heap() {
    root = nullptr;
    last = nullptr;
  }
  ~Heap() {;}

  TreeNode<T> * parent_next(TreeNode<T> *node);
  TreeNode<T> * prev_node(TreeNode<T> *node);

  void insert(T obj);
  void delMax();
  T getMax() {return root->object;}
  void Heapify(TreeNode<T> *node);
  void printHeap(TreeNode<T> *node);
  TreeNode<T> *get_root(){
    return root;
  }

  //  void displayAboveThresh(int thresh);
};

#endif


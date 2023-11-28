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
  TreeNode<T> *lastparent;
  TreeNode<T> *presentelement;
  // TreeNode<T*> *presentelementparent;


 public:
  Heap() {root = nullptr;
  last = root;}
  ~Heap() {;}

  void insert(T obj);
  void heapify(TreeNode<T> * r);
  TreeNode<T> * lastelement(TreeNode<T> *root);
  T  delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif


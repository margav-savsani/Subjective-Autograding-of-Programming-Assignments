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
  TreeNode<T>* root;
  int count,numberOfLayers;

 public:
  Heap() {root = nullptr;count=0;numberOfLayers = 0;}
  ~Heap() {;}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node,const string prefix ="",bool isLeft = false );
  void heapify(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif


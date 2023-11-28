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
 public:
 TreeNode<T> *root;
  int num;
  Heap() 
  {
    root = nullptr;
    num=0;
  }
  ~Heap() {;}
  int getHeight();
  void insert(T obj);
  void printH(const string& prefix, bool isLeft=false);
  void delMax();
  void Heapify(TreeNode<T> *node);
  bool checkheap(TreeNode<T> *node);
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif
//by saran 210050036

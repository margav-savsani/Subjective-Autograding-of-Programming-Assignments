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
  TreeNode<T> *prevTail;

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = prevTail = nullptr;
  }

  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T> *root;
  TreeNode<T> *tail;
  int size;

 public:
 
  Heap() {root = tail = nullptr; size = 0;}
  ~Heap() {;}

  void swapdata(TreeNode<T> *A,TreeNode<T> *B);
  void Heapify(TreeNode<T> *node);
  void delHeapify(TreeNode<T> *node);
  void taleoftail(TreeNode<T>  *node);
  void insert(T obj);
  void delMax();
  T getMax() {return root->object;}
  void printSupport(TreeNode<T> *node,const string& prefix,bool isLeft,int z);
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};

#endif

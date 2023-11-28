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
  int count;
  int min_h;

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
    count=1;
    min_h=0;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {
  

 public:
 TreeNode<T> *root;
 //TreeNode<T> *last;
  Heap() {root = nullptr;}
  ~Heap() {;}
  Heap(TreeNode<T> * roots){root=roots;}

  void insert(T obj);
  void delMax();
  void Heapify(TreeNode<T> *root);
  int height(TreeNode<T> * a);
  int minHeight(TreeNode<T> * a);
  TreeNode<T> *getlast(TreeNode<T> *a);
  // insert your own code here if needed
  T getMax() { return root->object;}
  void printHeap(TreeNode<T> *node);
  void print(TreeNode<T> *node,const string& prefix, bool isLeft);
  
};
#endif


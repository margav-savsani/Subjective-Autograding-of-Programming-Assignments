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
   TreeNode<T> *prevend;
  TreeNode(){
    left = right = parent = nullptr;
  }
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
  Heap() {root = nullptr;}
  ~Heap() {;}
  void setend(TreeNode<T> *t);
  void heapify(TreeNode<T> *t);
  void revheapify(TreeNode<T> *t);
  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  void printt(TreeNode<T>*node,const string &prefix, bool isLeft = false);
  //  void displayAboveThresh(int thresh);
};

#endif


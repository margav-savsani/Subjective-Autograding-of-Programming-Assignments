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
  int num_nodes = 0;
 public:
  Heap() {root = nullptr;}
  ~Heap() {;}
  void recur(TreeNode<T> *node,int nodes1,int nodes2,T obj,int no,int level);
  
  void insert(T obj);
  void insert1(TreeNode<T>*node);
  void delMax();
  T getMax() {
    return root->object; // insert your own code here if needed
  }
  void heapify(int rating);
  void printHeap(TreeNode<T> *node);
  void print(TreeNode<T> *node,const string& prefix, bool isLeft);
  //  void displayAboveThresh(int thresh);
};

#endif


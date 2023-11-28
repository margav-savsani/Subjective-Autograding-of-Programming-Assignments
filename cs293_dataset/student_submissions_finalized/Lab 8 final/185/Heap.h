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
  void printInfo();

  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T> *root;

 public:
 TreeNode<T> *last;
  Heap() {root = nullptr;}
  ~Heap() {;}
  int x = 1;
  int m = 0;


  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void Heapify(TreeNode<T> *node);
  void Heapify_del(TreeNode<T> *node);
  int* bin_arr(int x);
  void printHeap(TreeNode<T> *node);
  void printTheHeap(TreeNode<T> *root, const string& prefix, bool isLeft);
  void printInfo();
  void print();
  //  void displayAboveThresh(int thresh);
};

#endif


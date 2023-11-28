#ifndef HEAP_H
#define HEAP_H
// check
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
  TreeNode<T> *root;  // root changed to *root.
  TreeNode<T> *last;
    

 public:
  Heap() {
    root = nullptr;
    last = nullptr;
  }
  ~Heap() {;}

  void heapify(TreeNode<T> *node);
  void insert(T obj);
  void heapify_root(TreeNode<T> *node);
  void delMax();
  T getMax() {return root->object;}
  //int height(TreeNode<T> *node);
  //void print_level(TreeNode<T> *node, int level);
  void printHeap(TreeNode<T> *node);
   // void printHeap();
    //
  //  void displayAboveThresh(int thresh);
};
#endif


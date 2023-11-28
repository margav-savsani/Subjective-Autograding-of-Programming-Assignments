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
  int count; // specifies the size of the heap, helps to determine where to insert a new element

 public:
  Heap() {root = nullptr; count = 0;}
  ~Heap() {recursiveDelete(root);} // the destructor frees all memory
  
  void recursiveDelete(TreeNode<T> *currNode); // helper function for the desctructor
  void print(const string& prefix, TreeNode<T> *node, bool isLeft=false); // helper function for printHeap
  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
};

#endif


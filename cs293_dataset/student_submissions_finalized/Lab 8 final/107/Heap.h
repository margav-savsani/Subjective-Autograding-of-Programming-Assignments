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
  TreeNode<T> *root;  // root
  TreeNode<T> *last;  // last node
  TreeNode<T> *nextInsert;  // next insert at this node
  bool nextleftInsert;  // true if next insert will be at left child of nextInsert

 public:
  // Constructor
  Heap() {root = nullptr; last=nullptr; nextInsert=nullptr; nextleftInsert=false;}

  // Destructor
  ~Heap() {recursiveDelete(root);}

  // Delete last element of the heap
  void delLast();

  // Insert Treenode with it's object as given in argument
  void insert(T obj);

  // Delete the head (max element) of the heap
  void delMax();

  // Get the maximum element of the heap
  T getMax() {return root->object;}

  // Print the heap
  void printHeap(TreeNode<T> *node);

  // Delete the entire heap recursively
  void recursiveDelete(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};

#endif

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
  int count;

 public:
  Heap() {
    count=0;
    root = nullptr;}
  ~Heap() {;}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);

  // healper function for printing the tree
  void printBinaryTree(TreeNode<T> *root, const string& prefix, bool isLeft=false);

  // helper function made by me for inserting
  void insert_comp(TreeNode<T>* child,TreeNode<T>* parent);

  // swapping the elements
  void swap(TreeNode<T>* a,TreeNode<T>* b);

  // made by me to ensure heap property
  void Heapify(TreeNode<T> * to_do);
};

#endif


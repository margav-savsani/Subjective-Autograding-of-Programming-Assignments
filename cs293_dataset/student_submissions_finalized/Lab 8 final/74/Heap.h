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

 public:
  Heap() {root = nullptr;}
  ~Heap() {;}


  //extra helper functions
  void heapifyinsert(TreeNode<T> *node);           // heapify function used while inserting
  void insertnode(TreeNode<T> *node , T obj);      // insert with arg as node
  int leftheight(TreeNode<T> *node);              //left height of node
  int rightheight(TreeNode<T> *node);              // right height of node
  TreeNode<T>* lastelement(TreeNode<T> *node);              //lastelement in heap with root as node
  void heapifydelete(TreeNode<T> *node);                              // heapify down function used in deleting nodes

  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap();
  void printHeapTree(TreeNode<T> *root,const string& prefix, bool isLeft);
  //  void displayAboveThresh(int thresh);
};

#endif


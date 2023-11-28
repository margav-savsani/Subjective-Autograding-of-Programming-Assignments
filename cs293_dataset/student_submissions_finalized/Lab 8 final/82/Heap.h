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
  int index;

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {

 public:
  TreeNode<T>* root;
  TreeNode<T>* nextLoc;
  TreeNode<T>* lastLoc;
  Heap() {root = nullptr; nextLoc = nullptr; lastLoc = nullptr;}
  ~Heap() {;}

  void insert(T obj);
  T delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  void getNextLoc(int index, TreeNode<T>* &node);
  void heapify(TreeNode<T>* node);
  bool isLeftMost(TreeNode<T>* node);
  //  void displayAboveThresh(int thresh);
};

#endif

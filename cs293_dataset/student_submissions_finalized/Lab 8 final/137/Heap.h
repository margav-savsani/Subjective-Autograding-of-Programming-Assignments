#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
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
  ~Heap() {reccDel(root); return;}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  TreeNode<T> *findNextLoc(TreeNode<T> *node);
  void Heapify(TreeNode<T> *node);
  void reccDel(TreeNode<T> *root);
  void printBinaryTree(TreeNode<T> *root, const string& prefix, bool isLeft);
  TreeNode<T> *getRoot();
  //  void displayAboveThresh(int thresh);
};
#endif


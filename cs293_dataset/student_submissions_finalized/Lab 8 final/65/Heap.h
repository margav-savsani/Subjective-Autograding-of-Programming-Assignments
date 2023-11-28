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
  TreeNode<T> *end;

 public:

  
  Heap() {root = nullptr;
  end = nullptr;}
  ~Heap() {;}

  TreeNode<T>* getend(TreeNode<T>* node);
  bool check(TreeNode<T>* node);
  bool isLeftof(TreeNode<T>* node, TreeNode<T>* Parent);
  void recc_heapify(TreeNode<T>* node);
  void Heapify(TreeNode<T>* node);
  bool isLeft(TreeNode<T>* node);
  void insert(T obj);
  void delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
};
#endif


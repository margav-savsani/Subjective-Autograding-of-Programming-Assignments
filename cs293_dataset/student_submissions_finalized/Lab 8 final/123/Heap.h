#ifndef HEAP_H
#define HEAP_H
#endif

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
  int posn;

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
    posn = 0;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T> *root;
 public:
  Heap() {root = nullptr;}
  ~Heap() {;}

  void insert(T obj);
  void delMax();
  TreeNode<T>* getNodeatPos(int pos);
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  void Heapify(int pos);
  TreeNode<T>* prvsChild(TreeNode<T>* obj);
  //  void displayAboveThresh(int thresh);
};



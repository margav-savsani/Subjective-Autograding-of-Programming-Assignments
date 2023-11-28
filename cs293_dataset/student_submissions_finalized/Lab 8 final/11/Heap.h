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
  ~TreeNode() { 
      if (left != nullptr) delete left ; 
      if (right != nullptr) delete right ; 
  }
};

template <typename T> class Heap {
  TreeNode<T>* root;
  int lastIndex ; 
 public:
  Heap() {root = nullptr; lastIndex = -1 ; }
  ~Heap() {
     delete root ; 
  }
  void Heapify(TreeNode<T>* root) ;
  TreeNode<T>* elementAtIndex(int index) ;
  void insert(T obj);
  void delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  // void printHeap(const string& prefix, bool isLeft);
  // void displayAboveThresh(int thresh);
};
#endif


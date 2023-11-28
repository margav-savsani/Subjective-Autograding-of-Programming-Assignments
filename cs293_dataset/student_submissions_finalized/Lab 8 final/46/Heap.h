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

  int cnt=0;
  void insert(T obj);
  void delMax();
  T getMax() {
    if(root==nullptr) return T() ;
    return root->object;
    }
  int height(TreeNode<T> *tree);
  void printHeap(const string& prefix, bool isLeft);
  //  void displayAboveThresh(int thresh);
};
#endif


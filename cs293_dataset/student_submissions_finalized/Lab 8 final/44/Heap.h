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
  int height;
  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
    // height  = 0;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {
  // TreeNode<T> *root;
  int N; //would store the number of nodes in the tree

public:
TreeNode<T> *root;
  Heap() {root = nullptr; N = 0;} //while making heap number of nodes in the tree are zero.
  ~Heap() {;}

  void insert(T obj);
  void delMax();
  
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  // void Heapify();
  void printBST(const string& prefix, bool isLeft, TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif


#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#include<bits/stdc++.h>
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
  TreeNode<T> *lastNode;
  vector<bool> lastNodeCode;
  int count;

 public:
  Heap() {root = nullptr;}
  ~Heap() {;}

  void insert(T obj);
  void delMax();
  T getMax() {if(root == nullptr) return Review(-1, 99999, "");return root->object; // insert your own code here if needed
  }
  void Heapify(TreeNode<T> *node);
  void printHeap(TreeNode<T> *node);
  void helper(const string& prefix, bool isLeft = false);
  void recursiveDelete(TreeNode<T>* node);
  //  void displayAboveThresh(int thresh);
};

#endif


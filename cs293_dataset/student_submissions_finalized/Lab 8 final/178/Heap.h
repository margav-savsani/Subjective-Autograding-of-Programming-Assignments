#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif
#include<iostream>
#include <sstream>  // for string streams
#include <string> 
#include <cmath>
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
 int n= 0;
  Heap() {root = nullptr;}
  ~Heap() {;}
  int decimalToBinary(int N);
  void insertheapify(TreeNode<T> *node);
  void insert(T obj);

  TreeNode<T>* find();
  void Heapify(TreeNode<T> *node);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(const string& prefix, bool isLeft);
  //  void displayAboveThresh(int thresh);
};

#endif


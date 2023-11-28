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
  int numNodes;
  
  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
  }
  void print(){
    cout << object;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T>* root;
  TreeNode<T>* last;
  void heapify(TreeNode<T>* node);
 public:
  Heap() {root = nullptr;last = nullptr;}
  ~Heap() {;}

  void insert(T obj);
  T delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  void myprint();
  //  void displayAboveThresh(int thresh);
};
#endif


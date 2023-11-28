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
  int ent; //to keep track of no of elements present in heap.

 public:
  
  Heap() {root = nullptr;ent=0;}
  ~Heap() {
    while(ent >= 0){ //calling delmax function continuously untill all elements present in the heap are deleted
      delMax();
    }
  }

  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  void heapify(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};

#endif


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
  public:
  TreeNode<T> *root;
  TreeNode<T> *last; // to keep track of the node where insertion needs to be done 
  TreeNode<T> *lastparent; // parent of last node 
  TreeNode<T> *presentelement; // last element inserted in the heap
  // TreeNode<T*> *presentelementparent;


 
  Heap() {root = nullptr;
  last = root;}
  ~Heap()  ; // to free up the memory after use
  void insert(T obj);
  void heapify(TreeNode<T> * r);
  // TreeNode<T> * lastelement(TreeNode<T> *root);
  T  delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  void recursiveDelete(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif


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
  Heap() {
    root = nullptr;    
  }
  ~Heap() {
    recursivedelete(root);
  }

  void insert(T obj);
  void insertNode(TreeNode<T>*x,T obj);
  void Heapifyup(TreeNode<T>*x);
  TreeNode<T>* lastinsert(TreeNode<T> *x);
  void Heapifydown(TreeNode<T>*x);
  void delMax();
  void recursivedelete(TreeNode<T>*x);
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap();
  void printHeapTree(TreeNode<T> *root,const string& prefix, bool isLeft);
  int maxheight(TreeNode<T> *x);
  int minheight(TreeNode<T> *x);
  //  void displayAboveThresh(int thresh);
};

#endif


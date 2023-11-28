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
  int cntl=0;
 int cntr=0;
  //void insert(T obj);
  void checkpos(TreeNode<T> *ob,T obj);
  //void equate(T obj,T p);
  void insert(T obj);
  void prthp(const string& prefix, bool isLeft=false);
  void del(TreeNode<T>*p);
  void delMax();
  void Heapify(TreeNode<T>*p);
  T getMax() {return root->object;}; // insert your own code here if needed}
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif


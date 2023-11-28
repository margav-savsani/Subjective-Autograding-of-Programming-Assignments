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
    height=0;
  }
  ~TreeNode() {;}

  bool operator>(const TreeNode<T>& other){
    return this->object > other.object;
  }
  bool operator<(const TreeNode<T>& other){
    return this->object < other.object;
  }
};

template <typename T> class Heap {
  int num_nodes;

  TreeNode<T>* findInsertionParent();
  TreeNode<T>* findElementAt(int index);
  void bubbleUp(TreeNode<T>* node);
  void printHeapMain(TreeNode<T>* node, string pref);
  void heapify(TreeNode<T>* node);

 public:
  TreeNode<T> *root;
  Heap() {root = nullptr;num_nodes=0;}
  ~Heap() {;}

  void insert(T obj);
  T delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  int getHeight();
  //  void displayAboveThresh(int thresh);
};

#endif
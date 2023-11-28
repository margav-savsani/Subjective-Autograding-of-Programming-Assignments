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
  TreeNode<T> *parent_node;             //new nodes will be added to this node
  TreeNode<T> *last_node;               //points to the last node of the heap
  
 public:
  
  Heap() {root = parent_node = last_node = NULL; }
  ~Heap() {recursiveDel(root);}
  void recursiveDel(TreeNode<T>* node);      // recursively deletes all the nodes
  void heapify(TreeNode<T>* node);           // heapify the heap from the given node
  void insert(T obj);
  void delMax();
  T getMax() {return root->object;} // insert your own code here if needed
  void print(TreeNode<T>* node, const string& prefix, bool isLeft=false);
  void printHeap(TreeNode<T> *node);
  //void displayAboveThresh(int thresh);
};

#endif


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

// bool Review::operator< (Review obj){

// }

template <typename T> class Heap {
  TreeNode<T> *root;
  int total_nodes;

 public:
  Heap() {root = nullptr; total_nodes = 0;}
  ~Heap() {;}

  void delete_r_node();
  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node, string prefix = " ", bool isLeft = false);
  void switch_nodes(TreeNode<T> *node1, TreeNode<T> *node2);
  void heapify(TreeNode<T>* node);
  TreeNode<T>* find_node(int n);
  TreeNode<T>* findInsertionParent();
  void bubble_up(TreeNode<T>* node);
  TreeNode<T>* getRoot(){return root;}
  // int num_children()
  //  void displayAboveThresh(int thresh);
};

#endif


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
  TreeNode<T>* root;
  TreeNode<T>* cur_node;
  int size;


 public:
  Heap() {root = nullptr; cur_node=nullptr; size=0;}
  ~Heap() {;}

  bool check_power_of_two(int n) {int c=n&(n-1); if(c==0) return true; else return false;}
  void relocate_cur_node();
  void get_old_cur_node();
  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  void printHeapHelper(TreeNode<T> *root, string prefix, bool isLeft);

  //  void displayAboveThresh(int thresh);
};

#endif


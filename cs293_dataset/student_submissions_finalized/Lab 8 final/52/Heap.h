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
  int n;

 public:
  Heap() {root = nullptr; n=0;}
  ~Heap() {recursiveDelete(root);}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  void displayAboveThresh(int thresh);

  void binary(int n, vector<int>& v);
  TreeNode<T>* getRoot(){ return root; }
  void recursiveDelete(TreeNode<T>* node){
    if(node == nullptr) return;
    recursiveDelete(node->left);
    recursiveDelete(node->right);
    delete node;
  }
};
#endif


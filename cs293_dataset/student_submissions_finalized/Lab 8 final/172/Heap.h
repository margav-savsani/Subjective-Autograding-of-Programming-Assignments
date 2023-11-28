
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
  int num_of_nodes;
 public:
  Heap() {root = nullptr; lastNode=nullptr; num_of_nodes=0; }
  ~Heap() {
    recursive_delete(root);
  }
  void recursive_delete(TreeNode<T>* node);
  TreeNode<T> *lastNode;
   TreeNode<T> *root;
  void insert(T obj);
  T delMax();
  T getMax(){
    T a;
    if(root==nullptr) return a;
    else return root->object;
  }
  void printHeap(TreeNode<T>* node);
  void printHeap1(const string& a, bool isLeft );
  //  void displayAboveThresh(int thresh);
};

#endif
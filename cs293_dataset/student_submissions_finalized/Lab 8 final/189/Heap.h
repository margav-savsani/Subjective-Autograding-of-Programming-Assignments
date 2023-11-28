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
  void switching(TreeNode<T> *Node);
  int leftHeight(TreeNode<T> * Node);
  int rightHeight(TreeNode<T> * Node);
  bool isComplete(TreeNode<T> * Node);
  TreeNode<T>* getRightmostNodeOfLastLevel(TreeNode<T>* Node);
  
  bool isLeftChild(TreeNode<T> *Node){
    if(Node->parent->left==Node) return true;
    else return false;
  }
  void heapify(TreeNode<T> * Node);
  void Insert(T obj,TreeNode<T> * Node);
  void insert(T obj);
  T delMax();
  T getMax() {return root->object;}
  void printHeap1(TreeNode<T> * root,const string& prefix, bool isLeft);
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif


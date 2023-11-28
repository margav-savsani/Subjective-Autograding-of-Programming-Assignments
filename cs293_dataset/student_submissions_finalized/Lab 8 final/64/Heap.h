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
  TreeNode<T> *prevTail;;

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T>* root;

 public:
  Heap() {root = nullptr;}
  TreeNode<T>* tail = nullptr;

  void recursiveDelete(TreeNode<T>* currNode){
    if (currNode != nullptr) {
      TreeNode<T> *leftChild = currNode->left;
      TreeNode<T> *rightChild = currNode->right;
    
      delete currNode;
      recursiveDelete(leftChild);
      recursiveDelete(rightChild);
    }
    return;
  }

  ~Heap() {
    recursiveDelete(root);
  }

  void insert(T obj);
  void delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  void print(TreeNode<T> *node, const string& prefix, bool isLeft);
  void setTail(TreeNode<T>* node);
  void swapNodeData(TreeNode<T>* a, TreeNode<T>* b);
  void maxHeapify(TreeNode<T>* node);
  void revMaxHeapify(TreeNode<T>* node);
  TreeNode<T>* getRoot(){return root;};
  //  void displayAboveThresh(int thresh);
};
#endif


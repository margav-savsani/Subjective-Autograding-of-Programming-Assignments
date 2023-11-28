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
  TreeNode<T> *lastfilled;

 public:
  Heap() {root = nullptr;
    lastfilled= nullptr;
  }
  ~Heap() {
          destructRecursive(root);
  }

  void destructRecursive(TreeNode<T> *node){
    if(node == nullptr) return;
    if(node->left == nullptr && node->right == nullptr){
        delete node;
        return;
    }
    destructRecursive(node->left);
    destructRecursive(node->right);
    delete node;
  }

  void insert(T obj);
  void heapify(TreeNode<T> *node);
  void  delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  void printHeapRecursive(TreeNode<T> *node, const string& prefix, bool isLeft=false);
  //  void displayAboveThresh(int thresh);
};
#endif


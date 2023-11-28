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
  TreeNode<T> *last;
 public:
  Heap() {
    root = nullptr;
    last = nullptr;
  }

  void free_up(TreeNode<T> *t){
    if ( t==nullptr ){
      return;
    }
    TreeNode<T> *l = t->left;
    TreeNode<T> *r = t->right;
    delete(t);
    free_up(l);
    free_up(r);
  }
  ~Heap() {
      free_up(root);

  }
  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  void pHeap(const string& prefix, TreeNode<T> *Node, bool isLeft=false);
  //  void displayAboveThresh(int thresh);
};

#endif


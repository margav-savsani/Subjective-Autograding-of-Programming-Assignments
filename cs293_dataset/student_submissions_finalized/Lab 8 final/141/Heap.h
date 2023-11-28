#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#include "Trie.h"

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


  int size; // stores the size of the Heap. 

 public:
  
  Heap() {root = nullptr; size = 0;}
  ~Heap() {;}

  void insert(T obj);
  T delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
  template <class U>
  friend void printer(const string& prefix, TreeNode<U>* root, bool isLeft);
};
#endif

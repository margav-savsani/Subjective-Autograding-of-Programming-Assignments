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
  int numOfNodes;

 public:
  Heap(){
    root = nullptr;
    numOfNodes=0;
  }
  ~Heap(){
    for(int i=0;i<numOfNodes;i++){
      delMax();
    }
  }

  void insert(T obj);
  void delMax();
  TreeNode<T>* getRoot(){return root;}
  T getMax() {return root->object;//insert your own code if needed.
  }
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
  int logarithm2(int x);
  int exp(int b);
  void printTree(TreeNode<T> *root,const string& prefix, bool isLeft);
};
#endif


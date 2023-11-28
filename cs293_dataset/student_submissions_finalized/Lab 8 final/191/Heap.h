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
  TreeNode<T> *next;
  TreeNode<T> *last;

 public:
  Heap() {root = nullptr;next=nullptr;last=nullptr;}
  ~Heap();

  void insert(T obj);
  void delMax();
  T getMax() {
  	if(root != nullptr){
  		return root->object;
  	}
  	else{
  		return T();
  	}
   // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  void Heapify(TreeNode<T> *node);
  void swap(TreeNode<T>* node1, TreeNode<T>* node2);
  void recursive_delete(TreeNode<T>* node);
  //  void displayAboveThresh(int thresh);
};

#endif


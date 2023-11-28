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
  TreeNode<T> *prevTail; //pointer to tail before this tail

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T> *root;
  TreeNode<T> *tail; //extra variable which stores the pointer to the node whose children will be given the value in insert
 public:
  Heap() {root = nullptr; tail = nullptr;nodes=0;}
  ~Heap() {
    delNode(root); //destructor
    ;}

  int nodes;
  void insert(T obj);
  void delMax();
  T getMax() {
    return root->object;
     // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  void Heapify(TreeNode<T> *node);
  void Swap(TreeNode<T> *node1, TreeNode<T> *node2);
  void findTail(TreeNode<T> *node);
  void HeapifyDown(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};

template<typename T> 
void delNode(TreeNode<T> *node){ //deletes node and calls the deletion of its children recursively
  if(node==nullptr){
    return;
  }
  delNode(node->left);
  delNode(node->right);
  delete node;
}

#endif


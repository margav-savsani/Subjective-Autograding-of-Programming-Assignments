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
  int numNodes;

  void heapify(TreeNode<T>* cnode); // Function to heapify
  void heapify_up(TreeNode<T>* node); // Function to heapify from bottom-up
  void printHeapHelper(const string& prefix, bool isLeft=false); // Helper function for printHeapHelper()

 public:
  Heap() {root = nullptr; numNodes = 0;}
  ~Heap() {;}

  void insert(T obj); // Function to insert node into heap
  void delMax(); // Function to delete maximum element from heap
  T getMax() {return root->object; // insert your own code here if needed
  }
  
  void printHeap(TreeNode<T> *node); // Print heap from node
  //  void displayAboveThresh(int thresh);
};

#endif


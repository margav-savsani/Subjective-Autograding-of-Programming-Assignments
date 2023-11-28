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
  TreeNode<T> root;
  int *harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of heap
    int heap_size; // Current number of elements in heap
  public:
  Heap() {root = nullptr;}
  ~Heap() {;}
  Heap(int capacity);
  
    // to heapify a subtree with the root at given index
    void Heapify(int );
  
    int parent(int i) { return (i-1)/2; }
  
    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }
  
    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }
  
    // to extract the root which is the minimum element
    int extractMax();
  
    // Decreases key value of key at index i to new_val
    void decreaseKey(int i, int new_val);

  

  void insert(T obj);
  T delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif
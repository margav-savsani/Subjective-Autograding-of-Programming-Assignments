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
  int nodesAtLastLevel=0; //Stores the numberof nodes stored at the base of Binary Tree rooted at this node
  int lastlevel=0;// Last level is the height of Binary tree rooted at this node. 
                    //lastlevel=0 => nodesAtLastLevel=0.

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T> *root;
  void swap(TreeNode<T> *A, TreeNode<T> *B); //Swaps the objects stored in nodes A and B.
  void Heapify(TreeNode<T> *A); //Heapifies the Heap rooted at node A.

 public:
  Heap() {root = nullptr;}
  ~Heap() {;}

  void insert(T obj); //Inserts new node in Heap
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
   void displayAboveThresh(int thresh);
  TreeNode<T>* getRoot(); //returns the root of Heap
};

#endif


#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;
//Class TreeNode definition
template <typename T> class TreeNode {
 public:
 //Object
  T object;
  //Left Child
  TreeNode<T> *left;
  //Right Child
  TreeNode<T> *right;
  //Parent
  TreeNode<T> *parent;
  //Default Constructor
  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
  }
  //Destructor
  ~TreeNode() {;}
};

//Heap Class Definition
//Using Binary Tree Node
//It is a max heap
template <typename T> class Heap {
  //Root of Heap
  TreeNode<T> *root;
  //Size of the Heap
  int size;

 public:
 //Default Constructor
  Heap() {
    root = nullptr;
    size = 0;
    }
    //Destructor
  ~Heap() {;}

  //Inserts a given object in the heap
  void insert(T obj);
  //Deletes the maximum element from the heap
  void delMax();
  //Returns the maximum element from the heap without deleting it
  T getMax() {return root->object;}
  //Prints the Heap
  void printHeap(TreeNode<T> *node);
  //Implements Heapify on the arg node
  void Heapify(TreeNode<T> *node);
  //Prints a BST rooted at the arg node
  void printBST(TreeNode<T> *node,bool isLeft=false);
  //void displayAboveThresh(int thresh);
};
#endif

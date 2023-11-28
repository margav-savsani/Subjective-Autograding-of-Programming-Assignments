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
  ~TreeNode() {
    left = right = parent = nullptr;
  }
};

template <typename T> class Heap {
  TreeNode<T> *root;
  int numNodes;

// reccusive delete function to delete all nodes from heap when destructor is called
//to free up space
  void recursiveDelete(TreeNode<T> *currNode) {
    if (currNode != nullptr) {
      TreeNode<T> *leftChild = currNode->left;
      TreeNode<T> *rightChild = currNode->right;
    
      delete currNode;                        //deletes the given node
      recursiveDelete(leftChild);
      recursiveDelete(rightChild);
    }
    return;
  }

 public:
  Heap() {
    root = nullptr;
    numNodes=0;
  }
  ~Heap() {
    recursiveDelete(root);  
  }
  
  void insert(T obj);
  void delMax();

  //heapify function to heapify all nodes of heap
  void heapify(TreeNode<T> *node);
  
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};

#endif


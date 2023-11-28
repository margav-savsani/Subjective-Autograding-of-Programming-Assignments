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

  // New constructor made
  // To assign parent in addition to object
  TreeNode(T initObj, TreeNode<T>* par) {
    object = initObj;
    left = right = nullptr;
    parent = par;
  }

  ~TreeNode(){;}
};

template <typename T> class Heap {
  TreeNode<T> *root; //root of the Heap
  int num; //stores count of number of elements in heapd

 public:
  Heap() {root = nullptr;  num = 0;}

  // Recursively Deletes all nodes of the tree
  // rooted at currNode
  void recursiveDelete(TreeNode<T> *currNode) {
    if (currNode != nullptr) {
      TreeNode<T> *leftChild = currNode->left;
      TreeNode<T> *rightChild = currNode->right;
    
      delete currNode;
      recursiveDelete(leftChild);
      recursiveDelete(rightChild);
    }
    return;
  }

  // Destructor
  ~Heap(){recursiveDelete(root);}

  // This function returns the address to the TreeNode
  // given the index of the node, ordered as in Heap
  TreeNode<T>* getNode(int index);

  // This function swaps the objects present in 
  // nodeA and nodeB
  void swap(TreeNode<T>* nodeA, TreeNode<T>* nodeB);

  // This method updates the heap tree upwards
  // to restore the Heap property
  void updateUp(TreeNode<T>* currNode);

  // Inserts a new node with object obj into the Heap
  void insert(T obj);

  // A recursive function to restore the heap property of the 
  // heap, starting from the node. This works only when the 
  // left child and right child of node are heap balanced
  // but the node spoils the balance as a whole
  void Heapify(TreeNode<T>* node);

  // Deleting the max element of the heap
  void delMax();

  // returns max of the heap, which is situated at the root,
  // since this is a max heap
  T getMax() {return root->object;}

  // Prints Heap Tree the same way as we did for Binary Tree, starting from root
  void printHeapTree(TreeNode<T> *root, const string& prefix, bool isLeft);
  void printHeap(TreeNode<T> *node);
  // void displayAboveThresh(int thresh);
};

#endif


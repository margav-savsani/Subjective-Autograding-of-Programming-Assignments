#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class TreeNode {
 public:
  T object;               // object stored in a Node
  TreeNode<T> *left;
  TreeNode<T> *right;
  TreeNode<T> *parent;
  int level;              // level of the Node in the Heap

  TreeNode(T initObj) {   // Constructor
    object = initObj;
    left = right = parent = nullptr;
    level = 0;
  }
  ~TreeNode() {;}         // Destructor
};

template <typename T> class Heap {
  TreeNode<T> *root;            // Root Node
  TreeNode<T> *lastNode;        // A pointer to keep track of last Node inserted
  int numNodes;                 // Current number of nodes present in Heap

 public:

  // Constructor
  Heap() {
    root = nullptr; 
    numNodes = 0; 
    lastNode = nullptr;
  }

  // Destructor
  ~Heap() {;}

  void insert(T obj);        // Insert a new Node in Heap
  void delMax();             // Delete the Maximum element 
  T getMax() {               // Get the Maximum element from the Heap
    return root->object;
  }
  void printHeap(TreeNode<T> *node);    // Print Heap
  //  void displayAboveThresh(int thresh);
  TreeNode<T> *insertNode(TreeNode<T> *node, TreeNode<T> *newNode, int height);   // Helper function for inserting new Node
  void printTree(const string& prefix, bool isLeft);                              // Helper function for printing Heap
  bool isComplete(TreeNode<T> *node);               // Check if the Heap is a complete Binary Tree
  void Heapify(TreeNode<T> *node);                  // To maintain Heap condition after inserting new Node 
  void DelHeapify(TreeNode<T> *node);               // To maintain Heap condition after deleting the Max Node
  void updateLast(TreeNode<T> *node, int height, TreeNode<T> *&newLast);            // Update last Node pointer after deletion
  int height(TreeNode<T> *node);                    // Get Height of Subtree rooted at a given Node
  TreeNode<T> *getRoot(){           // Function to get root Node
    return root;
  }             

};

#endif


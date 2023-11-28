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
  TreeNode<T> *lastNode;
  int noOfNodes;

 public:
  Heap() {root = nullptr; noOfNodes=0;}
  ~Heap() {DestroyRecursive(root);}

  void insert(T obj);
  void delMax();
  T getMax() {return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  void HeapifyUp(TreeNode<T> *node);
  void HeapifyDown(TreeNode<T> *node);
  void printHeap();
  void displayAboveThresh(const string& thresh, bool isleft);
  void DestroyRecursive(TreeNode<T> *&node);
};

// template<typename T>
// void Heap<T>::DestroyRecursive(TreeNode<T> *node)
// {
//     if (node)
//     {
//         DestroyRecursive(node->left);
//         DestroyRecursive(node->right);
//         delete node;
//         cout<<"deleted\n";
//     }
// }

// template<typename T>
// Heap<T>::~Heap()
// {
//     DestroyRecursive(root);
// }

#endif


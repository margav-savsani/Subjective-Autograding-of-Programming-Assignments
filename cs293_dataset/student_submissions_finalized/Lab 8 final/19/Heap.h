#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T>
class TreeNode
{
public:
  T object;
  TreeNode<T> *left;
  TreeNode<T> *right;
  TreeNode<T> *parent;

  TreeNode(T initObj)
  {
    object = initObj;
    left = right = parent = nullptr;
  }
  ~TreeNode() { ; }
};

template <typename T>
class Heap
{
  TreeNode<T> *root;
  int count;

public:
  Heap()
  {
    root = nullptr;
    count = 0;
  }
  void heapify(TreeNode<T> *node);
  void insert(T obj);
  void delMax();
  T getMax()
  {
    return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);

  // destructor 
  void recursiveDelete(TreeNode<T> *currNode)
  {
    if (currNode != nullptr)
    {
      TreeNode<T> *leftChild = currNode->left;
      TreeNode<T> *rightChild = currNode->right;
      delete currNode;
      recursiveDelete(leftChild);
      recursiveDelete(rightChild);
    }
    return;
  }
  ~Heap()
  {
    recursiveDelete(root);
  }
};
#endif

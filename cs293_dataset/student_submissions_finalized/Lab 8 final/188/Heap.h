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

  void recursiveDelete(TreeNode *currNode)
  {
    if (currNode != nullptr)
    {
      TreeNode *leftChild = currNode->left;
      TreeNode *rightChild = currNode->right;

      delete currNode;
      recursiveDelete(leftChild);
      recursiveDelete(rightChild);
    }
    return;
  }

public:
  Heap() { root = nullptr; }
  ~Heap()
  {
    recursiveDelete(root);
  }

  void insert(T obj);
  TreeNode<T> *Heapify(TreeNode<T> *node);
  void delMax();
  T getMax() { return root->object; }
  void printHeap(TreeNode<T> *node);
  TreeNode<T> *prevSibling(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif

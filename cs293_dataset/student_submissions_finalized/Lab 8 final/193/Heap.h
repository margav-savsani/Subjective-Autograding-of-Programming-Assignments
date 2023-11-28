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

public:
  TreeNode<T> *root;
  Heap()
  {
    root = nullptr;
    totalinserted = 0;
  }
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
  ~Heap() { recursiveDelete(root); }
  int totalinserted;
  void insert(T obj);
  void delMax();
  T getMax() { return root->object; }
  void print() { printHeap(root, false); }
  void printHeap(TreeNode<T> *node);
  void printHeap_tree(const string &prefix, TreeNode<T> *node, bool isLeft);
  void Heapify(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);
};
#endif

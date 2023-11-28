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
  int Height()
  {
    if (left == nullptr || right == nullptr)
    {
      return 1;
    }
    else
    {
      return 1 + min(left->Height(), right->Height());
    }
  }
  int Height2()
  {
    if (left == nullptr && right == nullptr)
    {
      return 0;
    }
    if (left == nullptr)
    {
      return 1;
    }
    if (right == nullptr)
    {
      return 1;
    }
    else
    {
      return 1 + max(left->Height2(), right->Height2());
    }
  }
  bool imbalance() { return left != NULL; }
  ~TreeNode() { ; }
};

template <typename T>
class Heap
{
  TreeNode<T> *root;

public:
  Heap() { root = nullptr; }
  ~Heap() { ; }

  void insert(T obj);
  void delMax();
  T getMax()
  {
    return root->object;
  }
  void printHeap(TreeNode<T> *node);
  void print(TreeNode<T> *node, const string &prefix, bool isLeft);
  //  void displayAboveThresh(int thresh);
};
#endif

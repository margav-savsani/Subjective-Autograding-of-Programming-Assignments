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
  TreeNode<T> *last;
  int curr_num = 0;
public:
  Heap() { root = nullptr; }
  ~Heap() { ; }

  void insert(T obj);
  void delMax();
  void heapify(TreeNode<T> *node);
  void Swap(TreeNode<T> *a, TreeNode<T> *b);
  TreeNode<T> * max(TreeNode<T> *a, TreeNode<T> *b);
  T getMax()
  {
    return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);
  void print(TreeNode<T> *r, const string& prefix, bool isLeft);
  //  void displayAboveThresh(int thresh);
};

#endif

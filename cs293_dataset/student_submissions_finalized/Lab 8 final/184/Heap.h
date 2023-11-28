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
  TreeNode<T> *tail;

public:
  Heap()
  {
    root = nullptr;
    tail = nullptr;
  }
  ~Heap() { ; }

  bool should_heapify(TreeNode<T> *node);
  void heapify(TreeNode<T> *node);
  void recursive_heapify(TreeNode<T> *node);
  void insert(T obj);
  void delMax();
  T getMax()
  {
    return root->object; // insert your own code here if needed
  }
  TreeNode<T> *getlast();
  void printHeap(TreeNode<T> *node);
  //  void displayAboveThresh(int thresh);

  void printBinaryTree(TreeNode<T> *node, const string &prefix, bool isLeft)
  {
    if (node != nullptr)
    {
      cout << prefix;

      cout << (isLeft ? "|--" : "|__");

      // print the value of the node
      cout << node->object.rating;
      cout << endl;
      TreeNode<T> *curr = node;
      node = node->left;
      // enter the next tree level - left and right branch
      printBinaryTree(node, prefix + (isLeft ? "│   " : "    "), true);
      node = curr->right;
      printBinaryTree(node, prefix + (isLeft ? "│  " : "    "), false);
      node = curr;
    }
    else
    {
      cout << "NULL tree" << endl;
    }
  }
};

#endif

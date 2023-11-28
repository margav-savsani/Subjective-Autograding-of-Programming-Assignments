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
  TreeNode(T initObj, TreeNode<T> *parent)
  {
    object = initObj;
    left = right = nullptr;
    this->parent = parent;
  }
  ~TreeNode() { ; }
};

template <typename T>
class Heap
{

public:
  TreeNode<T> *root;
  TreeNode<T> *last;
  TreeNode<T> * end;
  int count;
  Heap()
  {
    root = nullptr;
    count = 0;
  }
  ~Heap() { ; }

  void preOrder(TreeNode<T> *node)
  {
    if (node == nullptr)
    {
      // cout<<endl;
      return;
    }
      
    cout << node->object << " ";
    preOrder(node->left);
    preOrder(node->right);
  }
  void inOrder(TreeNode<T> *node)
  {
    if (node == nullptr)
    {
      // cout<<endl;
      return;
    }

    inOrder(node->left);
    cout << node->object <<" ";
    inOrder(node->right);
  }
  void maintainHeap(TreeNode<T> *node);
  int height(TreeNode<T> *node);
  void setLast(TreeNode<T> *last, int count);
  void insert(T obj);
  void delMax();
  void setEnd(TreeNode<T> *root,int count);
  T getMax()
  {
    return root->object; // insert your own code here if needed
  }
  void printHeap(TreeNode<T> *node);

  //  void displayAboveThresh(int thresh);
};

#endif


#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here

  if (root == NULL)
  {
    root = new TreeNode<T>(obj);
    return;
  }
  TreeNode<T> *x = root;
  while (true)
  {
    if (x->Height() == 1)
    {
      if (x->imbalance())
      {
        x->right = new TreeNode<T>(obj);
        x->right->parent = x;
        x = x->right;
      }
      else
      {
        x->left = new TreeNode<T>(obj);
        x->left->parent = x;
        x = x->left;
      }
      break;
    }
    if (x->left->Height() > x->right->Height())
    {
      x = x->right;
    }
    else
    {
      x = x->left;
    }
  }
  while (true)
  {
    if (x->parent == NULL)
    {
      return;
    }
    if (!(x->object < x->parent->object))
    {
      T Z = x->object;
      x->object = x->parent->object;
      x->parent->object = Z;
      x = x->parent;
    }
    else
      break;
  }
  return;
}

template <typename T>
void Heap<T>::delMax()
{
  TreeNode<T> *x = root;
  // insert your code here
  int k;
  if (root->left == nullptr && root->right == nullptr)
  {
    root = nullptr;
        return;
  }
  while (x->left != nullptr)
  {
    if (x->right != nullptr)
    {
      if (x->left->Height2() == x->right->Height2())
      {
        x = x->right;
        k = 0;
      }
      else
      {
        x = x->left;
        k = 1;
      }
    }
    else
    {
      x = x->left;
      k = 1;
    }
  }
  root->object = x->object;
  if (k == 0)
    x->parent->right = nullptr;
  else
    x->parent->left = nullptr;
  TreeNode<T> *y = root;
  TreeNode<T> *z;
  TreeNode<T> *l = new TreeNode<T>(root->object);
  int r = 0;
  while (true)
  {
    if (y->left != nullptr && y->right != nullptr)
    {
      if (y->left->object < y->right->object)
      {
        z = y->right;
        r = 0;
      }
      else
      {
        z = y->left;
        r = 1;
      }
    }
    else if (y->left != nullptr)
    {
      z = y->left;
      r = 1;
    }
    else
      break;
    if (y->object < z->object)
    {
      l->object = y->object;
      y->object = z->object;
      z->object = l->object;
      if (r == 1)
      {
        y = y->left;
      }
      else
        y = y->right;
    }
    else
      break;
  }
  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  print(node, "", true);
  return;
}
template <typename T>
void Heap<T>::print(TreeNode<T> *node, const string &prefix, bool isLeft)
{
  if (node != nullptr)
  {
    cout << prefix;
    cout << (isLeft ? "|--" : "|__");
    // print the value of the node
    // node->printInfo();
    cout << node->object << endl;
    TreeNode<T> *curr = node;
    node = node->left;
    // enter the next tree level - left and right branch
    print(node, prefix + (isLeft ? "│   " : "    "), true);
    node = curr->right;
    print(node, prefix + (isLeft ? "│   " : "    "), false);
    node = curr;
  }
}

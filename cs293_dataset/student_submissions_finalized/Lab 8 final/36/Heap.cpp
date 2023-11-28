#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <bits/stdc++.h>

template <typename T>
int Heap<T>::level_filled_completely(TreeNode<T> *node)
{
  if (node == nullptr)
  {
    return 0;
  }
  return 1 + level_filled_completely(node->left) + level_filled_completely(node->right);
}

template <typename T>
void Heap<T>::climb(TreeNode<T> *node)
{
  while (node->parent->object < node->object)
  {
    T temp = node->object;
    node->object = node->parent->object;
    node->parent->object = temp;
    node = node->parent;
    if (node->parent == nullptr)
    {
      break;
    }
  }
}

template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here
  if (root == nullptr)
  {
    root = new TreeNode(obj);
    return;
  }
  TreeNode<T> *temp = root;
  while (temp != nullptr)
  {
    if (temp->left == nullptr && temp->right == nullptr)
    {
      temp->left = new TreeNode(obj);
      temp->left->parent = temp;
      climb(temp->left);
      return;
    }
    if (temp->left != nullptr && temp->right == nullptr)
    {
      temp->right = new TreeNode(obj);
      temp->right->parent = temp;
      climb(temp->right);

      return;
    }
    int l = level_filled_completely(temp->left), r = level_filled_completely(temp->right);
    l = int(log2(l + 1));
    r = int(log2(r + 1));

    if (l == r)
    {
      temp = temp->left;
      continue;
    }
    else
    {
      temp = temp->right;
      continue;
    }
  }
  return;
}

template <typename T>
void Heap<T>::heapify(TreeNode<T> *node)
{
  while (node != nullptr)
  {
    if (node->left == nullptr && node->right == nullptr)
    {
      return;
    }
    if (node->left != nullptr && node->right == nullptr)
    {
      if (node->object < node->left->object)
      {
        T temp = node->object;
        node->object = node->left->object;
        node->left->object = temp;
      }
      return;
    }
    if (node->object < node->left->object || node->object < node->right->object)
    {
      if (node->right->object < node->left->object)
      {
        T temp = node->object;
        node->object = node->left->object;
        node->left->object = temp;
        node = node->left;
      }
      else
      {
        T temp = node->object;
        node->object = node->right->object;
        node->right->object = temp;
        node = node->right;
      }
    }
    else
    {
      return;
    }
  }
}

template <typename T>
void Heap<T>::delMax()
{
  TreeNode<T> *node = root;
  if (node == nullptr)
  {
    return;
  }
  // insert your code here
  TreeNode<T> *temp = node;
  while (temp != nullptr)
  {
    if (temp->left == nullptr && temp->right == nullptr)
    {
      if (temp == node)
      {
        root = nullptr;
        return;
      }
      node->object = temp->object;
      if (temp->parent->right != nullptr)
      {
        temp->parent->right = nullptr;
      }
      else
      {
        temp->parent->left = nullptr;
      }
      // adffb
      heapify(node);
      return;
    }
    if (temp->left != nullptr && temp->right == nullptr)
    {
      if (temp == node)
      {
        node->object = temp->left->object;
        node->left = nullptr;
        return;
      }
      node->object = temp->left->object;
      temp->left = nullptr;
      heapify(node);
      return;
    }
    int l = level_filled_completely(temp->left), r = level_filled_completely(temp->right);
    int l_ = int(log2(l + 1));
    int r_ = int(log2(r + 1));
    if (l_ == r_)
    {
      if (l == r)
      {
        temp = temp->right;
        continue;
      }
      temp = temp->left;
      continue;
    }
    else
    {
      int x = log2(l - r);
      if (x == r_)
      {
        temp = temp->left;
        continue;
      }
      else
      {
        temp = temp->right;
        continue;
      }
    }
  }
  return;
}

template <typename T>
void Heap<T>::printBST(const string &prefix, bool isLeft)
{
    if (root != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->object<< endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *root)
{
  printBST("",0);
}

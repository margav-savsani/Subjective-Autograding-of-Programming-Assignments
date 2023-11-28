#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <cmath>
#include <string>

template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here
  int height = int(log2(num_nodes + 1));
  int remainder = (num_nodes + 1) - ((2 * *height) - 1);
  string directions = "";
  TreeNode *temp = new TreeNode(obj);
  TreeNode<T> iter = root;
  for (int i = 0; i < height; i++)
  {
    if (remainder == 1)
    {
      directions = string(remainder % 2) + directions;
    }
    else
    {
      directions = string(remainder % 2) + directions;
      remainder = (remainder / 2) + (remainder % 2);
    }
  }
  if (iter == nullptr)
  {
    // ADD the node at root
    root = *temp;
  }
  else
  {
    for (int i = 0; i < height - 1; i++)
    {
      if (directions[i] == "1")
      {
        iter = *(iter.left);
      }
      else
      {
        iter = *(iter.right);
      }
    }
    if (directions[height - 1] == "1")
    {
      iter.left = temp;
      *temp.parent = &iter;
    }
    else
    {
      iter.right = temp;
      *temp.parent = &iter;
    }
  }
  // Need to kind of HEAPIFY the stuff
  return;
}

template <typename T>
void Heap<T>::delMax()
{
  // insert your code here
  if (num_nodes > 0)
  {
    int height = int(log2(num_nodes));
    int remainder = (num_nodes) - ((2 * *height) - 1);
    string directions = "";
    TreeNode<T> iter = root;
    for (int i = 0; i < height; i++)
    {
      if (remainder == 1)
      {
        directions = string(remainder % 2) + directions;
      }
      else
      {
        directions = string(remainder % 2) + directions;
        remainder = (remainder / 2) + (remainder % 2);
      }
    }
    for (int i = 0; i < height - 1; i++)
    {
      if (directions[i] == "1")
      {
        iter = *(iter.left);
      }
      else
      {
        iter = *(iter.right);
      }
    }
    if (height - 1 >= 0)
    {
      if (directions[height - 1] == "1")
      {
        root.object = iter.left->object;
        del iter.left;
        iter.left = nullptr;
      }
      else
      {
        root.object = iter.right->object;
        del iter.right;
        iter.right = nullptr;
      }
      num_nodes--;
    }
    else
    {
      del &root;
      root = nullptr;
    }

    // HEAPIFY
  }
  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

  // insert your code here

  return;
}

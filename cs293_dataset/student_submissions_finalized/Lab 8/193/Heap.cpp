#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <vector>

template <typename T>
void Heap<T>::insert(T obj)
{
  // A number iterator that would be stored in a vector to represent the path of the root
  // where the insert is to be made.
  int num_itr = totalinserted + 1;

  // If root has not been inserted yet.
  if (totalinserted == 0)
  {
    this->root = new TreeNode<T>(obj);
  }
  // Vector to store the path of the nodes in the form of integers.
  vector<int> path;

  // Pushing into the vector the numbers that would represent the "virtual"
  // indices of the TreeNodes
  while (num_itr != 0)
  {
    path.push_back(num_itr);
    num_itr /= 2;
  }

  // An iterator object
  TreeNode<T>* iterate = root;

  // child object
  int child = 1;
  while (path.size() != 1)
  {
    path.pop_back();
    if (path.back() == 2 * child)
    {
      iterate = iterate->left;
      child = path.back();
    }
    else
    {
      iterate = iterate->right;
      child = path.back();
    }
  }
  // Adding a new
  iterate = new TreeNode<T>(obj);
  totalinserted++;
  return;
}

template <typename T>
void Heap<T>::delMax()
{
  if (this->root == NULL)
  {
    return;
  }
  TreeNode<T> *iterate; // An iterator
  vector<int> path;
  int num_itr = totalinserted;
  while (num_itr != 0)
  {
    path.push_back(num_itr);
    num_itr /= 2;
  }
  int child = 1;
  while (path.size() != 1)
  {
    path.pop_back();
    if (path.back() == 2 * child)
    {
      iterate = iterate->left;
      child = path.back();
    }
    else
    {
      iterate = iterate->right;
      child = path.back();
    }
  }
  swap(root->object, iterate->object);
  iterate = NULL;
  totalinserted--;
  Heapify(this->root);
  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  if (node == NULL)
    return;
  cout << node->object << endl;
  printHeap(node->left);
  printHeap(node->right);
  return;
}

template <typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{
  // if(node == NULL) return;
  if (node->left == NULL)
  { // Which means this is the last level
    return;
  }
  if (node->right == NULL)
  {
    if (node->left->object < node->object)
    {
      return;
    }
    else
    {
      T temp = node->object;
      node->object = node->left->object;
      node->left->object = temp;
    }
  }
  // When none of children is greater than the node.
  if (!(node->object < node->right->object) && !(node->object < node->left->object))
    return;

  // Finally we have an object greater than the root.
  if (node->right->object < node->left->object)
  {
    swap(node->left->object, node->object);
  }
  else
  {
    swap(node->right->object, node->object);
  }
}

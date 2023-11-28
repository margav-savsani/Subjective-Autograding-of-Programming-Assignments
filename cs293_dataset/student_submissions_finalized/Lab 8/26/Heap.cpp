#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::insert(T obj)
{

  if (root == nullptr)
  {
    root = new TreeNode<T>(obj);
    tail = root;
  }
  jielse if (tail->left == nullptr)
  {
    tail->left = new TreeNode<T>(obj);
    tail->left->parent = tail;
    maxHeapify(tail->left);
  }
  else
  {
    tail->right = new TreeNode<T>(obj);
    tail->right->parent = tail;
    maxHeapify(tail->right);
    TreeNode<T> *prevTail = tail;
    setTail(tail);
    tail->prevTail = prevTail;
  }
  size++;

  // insert your code here

  return;
}

template <typename T>
T Heap<T>::delMax()
{
  if (root == nullptr)
  {

    return nullptr;
  }
  if (tail == root)
  {
    tail = nullptr;
    root = nullptr;
  }
  else
  {
    if (tail->right != nullptr)
    {
      swapNodeData(tail->right, root);
      tail->right = nullptr;
      revMinHeapify(root);
    }
    else if (tail->left != nullptr)
    {
      swapNodeData(tail->left, root);
      tail->left = nullptr;
      revMinHeapify(root);
    }
    else
    {
      tail = tail->prevTail;
      deleteRoot();
      size++;
    }
  }
  size--;

  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  // insert your code here

  return;
}
template <typename T>
void maxHeapify(TreeNode<T> *node)
{
  if (node->parent != nullptr)
  {
    if (node->parent->data < node->data)
    {
      swapNodeData(node->parent, node);
      maxHeapify(node->parent);
    }
  }
}
template <typename T>
void swapNodeData(TreeNode<T> *a, TreeNode<T> *b)
{
  T temp = a->object;
  a->object = b->object;
  b->object = temp;
}
template <typename T>
void setTail(TreeNode<T> *node)
{

  /*
    If we reach this stage that means a level is completely filled
    and we need to proceed to the next level by going to the extreme left.
   */
  if (node->parent == nullptr)
  {
    tail = node;
    while (tail->left != nullptr)
    {
      tail = tail->left;
    }
  }
  /*
    If current node is the left node, go to the right node and
    proceed left from there to reach the left most node.
   */
  else if (node->parent->left == node)
  {
    tail = node->parent->right;
    while (tail->left != nullptr)
    {
      tail = tail->left;
    }
  }
  else if (node->parent->right == node)
  {
    setTail(node->parent);
  }
}
template <typename T>
void revMaxHeapify(TreeNode<T>* node)
{
  if (node == nullptr || node->left == nullptr)
    return;
  TreeNode<T> *max = node->left;
  if (node->right != nullptrs && max->data < node->right->data)
  {
    max = node->right;
  }
  if (max->data < node->data)
  {
    swapNodeData(node, max);
    revMaxHeapify(max);
  }
}
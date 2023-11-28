#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
TreeNode<T> *Heap<T>::prevSibling(TreeNode<T> *node)
{
  if (node == root)
  {
    return nullptr;
  }
  if (node->parent->right == node)
  {
    return node->parent->left;
  }
  else
  {
    TreeNode<T> *ptr = node->parent;
    if (prevSibling(ptr) == nullptr)
    {
      return nullptr;
    }
    return prevSibling(ptr)->right;
  }
}

template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here
  TreeNode<T> *element = new TreeNode<T>(obj);
  if (root == nullptr)
  {
    root = element;
    return;
  }
  //cout << "hi1" << endl;
  TreeNode<T> *node = root;
  TreeNode<T> *parent = nullptr;
  while (node->right != nullptr)
  {
    parent = node;
    node = node->right;
  }
  while (true)
  {
    if (node->left != nullptr)
    {
      node->right = element;
      element->parent = node;
      break;
    }
    else
    {
      //cout << "hi3" << endl;
      TreeNode<T> *adj = prevSibling(node);
      //cout << "hi4" << endl;
      if (adj == nullptr)
      {
        node->left = element;
        element->parent = node;
        break;
      }
      if (adj->right != nullptr && adj->left != nullptr)
      {
        node->left = element;
        element->parent = node;
        break;
      }
      else
      {
        node = adj;
      }
    }
  }
  node = element;
  while (node->parent->object < node->object)
  {
    T temp = node->parent->object;
    node->parent->object = node->object;
    node->object = temp;
    node = node->parent;
    if (node->parent == nullptr)
      break;
  }
  //cout << "hi2" << endl;
  return;
}

template <typename T>
void Heap<T>::delMax()
{
  // insert your code here
  T dummy = T();
  root->object = dummy;
  TreeNode<T> *node = Heapify(root);
  if (node->parent->left == node)
  {
    node->parent->left == nullptr;
  }
  if (node->parent->right == node)
  {
    node->parent->right == nullptr;
  }
  node->parent == nullptr;
  return;
}

template <typename T>
TreeNode<T> *Heap<T>::Heapify(TreeNode<T> *node)
{
  // insert your code here
  TreeNode<T> *maxi;
  if (node->left == nullptr && node->right == nullptr)
  {
    return node;
  }
  else
  {
    maxi = node->left;
    if (node->right != nullptr)
    {
      if (node->left->object < node->right->object)
      {
        maxi = node->right;
      }
    }
  }
  if (node->object < maxi->object)
  {
    T temp = node->object;
    node->object = maxi->object;
    maxi->object = temp;
    Heapify(maxi);
  }
  return node;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  // insert your code here
  bool isLeft = false;
  if (node != nullptr)
  {
    //cout << (isLeft ? "|--" : "|__");
    // print the value of the node
    //cout << node->object << endl;
    TreeNode<T> *curr = node;
    node = node->left;
    isLeft = true;
    // enter the next tree level - left and right branch
    printHeap(node);
    node = curr->right;
    isLeft = false;
    printHeap(node);
    root = curr;
  }
}

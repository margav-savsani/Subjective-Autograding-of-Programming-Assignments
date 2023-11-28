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
  int i = count + 1;
  TreeNode<T> *node = root;
  T swap;
  TreeNode<T> *newNode = new TreeNode(obj);
  if (root == nullptr)  //base case
  {
    root = newNode;
    count++;
    return;
  }

  if (root->left == nullptr)  //base case
  {
    root->left = newNode;
    root->left->parent = root;
    if (root->object < obj)
    {
      swap = root->object;
      root->object = root->left->object;
      root->left->object = swap;
    }
    count++;
    return;
  }

  if (root->right == nullptr) //base case
  {
    root->right = newNode;
    root->right->parent = root;
    if (root->object < obj)
    {
      swap = root->object;
      root->object = root->right->object;
      root->right->object = swap;
    }
    count++;
    return;
  }

  TreeNode<T> *temp;
  int *m = new int();   //used binary implementation to solve this problem
  int z = 0;
  while (i != 1)
  {
    m[z] = i % 2;
    z++;
    i = i / 2;
  }
  z--;

  int side = -1;
  while (z >= 0)
  {
    if (m[z] == 0)
    {
      temp = node;
      node = node->left;
      side = 1;
    }
    else
    {
      temp = node;
      node = node->right;
      side = 2;
    }
    z--;
  }
  if (side == 1)
  {
    node = newNode;
    temp->left = node;
  }
  if (side == 2)
  {
    node = newNode;
    temp->right = node;
  }
  while (temp != nullptr) // swapping the required elements here
  {
    if (temp->object < obj)
    {
      swap = temp->object;
      temp->object = node->object;
      node->object = swap;
      node = temp;
      temp = temp->parent;
    }
    else
      break;
  }
  count++;
  return;
}

template <typename T>
void Heap<T>::delMax()
{

  // insert your code here
  int i = count;
  TreeNode<T> *node = root;

  T swap;
  if (root == nullptr)
    return;
  if (root->left == nullptr)  //base cases
  {
    root = nullptr;
    count--;
    return;
  }
  if (root->right == nullptr)
  {
    root->object = root->left->object;
    root->left = nullptr;
    count--;
    return;
  }

  int *m = new int(); // binary method to find the node that is going to be deleted
  int z = 0;
  TreeNode<T> *temp;
  while (i != 1)
  {
    m[z] = i % 2;
    z++;
    i = i / 2;
  }
  z--;
  int side = -1;
  while (z >= 0)
  {
    if (m[z] == 0)
    {
      temp = node;
      node = node->left;
      side = 1;
    }
    else
    {
      temp = node;
      node = node->right;
      side = 2;
    }
    z--;
  }
  root->object = node->object;
  if (side == 1)
    temp->left = nullptr;
  if (side == 2)
    temp->right = nullptr;
  TreeNode<T>*elem = root;

  while (elem->left != nullptr && elem->right != nullptr) //swapping the required elements
  {
    if (elem->object < elem->left->object || elem->object < elem->right->object)
    {
      if (elem->right->object < elem->left->object)
      {
        swap = elem->left->object;
        elem->left->object = elem->object;
        elem->object = swap;
        elem = elem->left;
      }
      else
      {
        swap = elem->right->object;
        elem->right->object = elem->object;
        elem->object = swap;
        elem = elem->right;
      }
    }
    else
    {
      count--;
      return;
    }
  }
  if (elem->left != nullptr && elem->right == nullptr && elem->object < elem->left->object)
  {
    swap = elem->left->object;
    elem->left->object = elem->object;
    elem->object = swap;
  }
  count--;
  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node, const string &prefix, bool isLeft)
{

  // insert your code here

  if (node != nullptr)  // printing the nodes as we have done in BST
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    cout << node->object << endl;
    TreeNode<T> *curr = node;
    printHeap(node->left, prefix + (isLeft ? "│   " : "    "), true);
    node = curr;
    printHeap(node->right, prefix + (isLeft ? "│   " : "    "), false);
    node = curr;
  }

  return;
}

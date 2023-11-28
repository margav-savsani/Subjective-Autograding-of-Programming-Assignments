#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif
#include <cmath>
#ifndef HEAP_H
#include "Heap.h"
#endif

/// @brief function used to heapify the heap when a new node is inserted
/// @tparam T Type of the object present n the node
/// @param node node from which heapify has to begin, the node just inserted
template <typename T>
void Heap<T>::heapify(TreeNode<T> *node)
{
  if (node == root)
    return;
  else
  {
    while (true)
    {
      // when node reaches the root
      if (node->parent == nullptr)
        break;
      
      // compare with the parent and swap their values
      else if (node->parent->object < node->object)
      {
        T obj = node->parent->object;
        node->parent->object = node->object;
        node->object = obj;
        node = node->parent;
      }
      else
        break;
    }
  }
}

/// @brief inserting a new node in the heap, inserted at the bottom of the heap
/// @tparam T type of the object to be inserted
/// @param obj object to be inserted in the node
template <typename T>
void Heap<T>::insert(T obj)
{
  // if root is empty, insert the node there
  if (root == nullptr)
  {
    root = new TreeNode<T>(obj);
    size++;
  }

  // find the binary representation of the size and move left and right accordingly from the root to find the node where new node is to be inserted, then heapify the heap
  else
  {
    size++;
    int i = size, n = 0, k = 0;
    while (i != 1)
    {
      k = (10 * k) + i - (2 * (i / 2));
      i = i / 2;
      n++;
    }
    TreeNode<T> *current = root;
    for (int j = 0; j < n - 1; j++)
    {
      int s = k % 10;
      if (s)
        current = current->right;
      else
        current = current->left;
      k = k / 10;
    }
    if (k)
    {
      current->right = new TreeNode<T>(obj);
      current->right->parent = current;
      heapify(current->right);
    }
    else
    {
      current->left = new TreeNode<T>(obj);
      current->left->parent = current;
      heapify(current->left);
    }
  }
  return;
}

/// @brief heapifying the function when the root is deleted.
/// @tparam T type of the objects in the node
template <typename T>
void Heap<T>::delheapify()
{
  TreeNode<T> *current = root;
  while ((current != nullptr))
  {
    if (current->left == nullptr)
    {
      break;
    }
    else if (current->right == nullptr)
    {
      if (current->object < current->left->object)
      {
        T obj = current->object;
        current->object = current->left->object;
        current->left->object = obj;
      }
      break;
    }

    // heapifying the heap in different scenarios
    else
    {
      T a = current->left->object;
      T b = current->right->object;
      T c = current->object;
      if (a < c && b < c)
      {
        break;
      }
      else if (c < a && b < a)
      {
        current->object = a;
        current->left->object = c;
        current = current->left;
      }
      else if (c < b && a < b)
      {
        current->object = b;
        current->right->object = c;
        current = current->right;
      }
      else if (c < a && c < b)
      {
        current->object = a;
        current->left->object = c;
        current = current->left;
      }
      else break;
    }
  }
}

/// @brief function to delete the max object, i.e., the root of the heap. swap root with last node, delete last node and then heapify(delheapify)
/// @tparam T type of the object in the node
template <typename T>
void Heap<T>::delMax()
{
  if (size == 1)
  {
    root = nullptr;
    size = 0;
  }

  // finding the binary representation of the size to traverse to the last node
  else
  {
    int i = size, n = 0, k = 0;
    while (i != 1)
    {
      k = (10 * k) + i - (2 * (i / 2));
      i = i / 2;
      n++;
    }
    TreeNode<T> *current = root;
    for (int j = 0; j < n - 1; j++)
    {
      int s = k % 10;
      if (s)
        current = current->right;
      else
        current = current->left;
      k = k / 10;
    }
    if (k)
    {
      root->object = current->right->object;
      current->right = nullptr;
    }
    else
    {
      root->object = current->left->object;
      current->left = nullptr;
    }
    size--;
    delheapify();
  }
  return;
}

/// @brief printing the heap, much like BST
/// @tparam T type of the objects in the heap
/// @param prefix used in printing the left or the right node
/// @param isLeft tells whether the next node to be printed is left or right
template <typename T>
void Heap<T>::printHeap(const string &prefix, bool isLeft)
{
  if (root != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->object.rating << endl;
        TreeNode<T> *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printHeap(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printHeap(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
  return;
}

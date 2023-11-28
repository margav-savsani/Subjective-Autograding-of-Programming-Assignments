#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <cmath>

template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here

  /*
  1. Insert the object to the "empty" slot.
  2. Shift the object upward until it reaches the root.
  3. Update size.
  */
  if (size == 0)
  {
    root = new TreeNode<T>(obj);
    size++;
    return;
  }

  size += 1;
  int num = size;
  TreeNode<T> *currNode = root;
  TreeNode<T>* resultNode = nullptr;
  // using the binary representation of the size decide where to go.

  int counter = floor(log(num) / log(2));
  num = num % static_cast<int>(floor(round(pow(2, counter))));
  int bit;
  for (int i = counter; i > 0; i--)
  {
    
    bit = num / floor(round(pow(2, i - 1)));
    num = num % static_cast<int>(floor(round(pow(2, i - 1))));
    if (i == 1)
    {
      if (bit == 0)
      {
        currNode->left = new TreeNode<T>(obj);
        resultNode = currNode->left;
        currNode->left->parent = currNode;
      }
      if (bit == 1)
      {
        currNode->right = new TreeNode<T>(obj);
        resultNode = currNode->right;
        currNode->right->parent = currNode;
      }
      break;
    }
    if (bit == 0)
    {
      currNode = currNode->left;
    }
    else if (bit == 1)
    {
      currNode = currNode->right;
    }
  }

  // we also need to heapify now (on the node inserted). 

  while (resultNode != root) {
    if (resultNode->parent->object < resultNode->object) {
      swap (resultNode->object, resultNode->parent->object);
      resultNode = resultNode->parent;
    }
    else {
      break;
    }
  }
  
  return;
}

template <typename T>
T Heap<T>::delMax()
{

  // insert your code here

  /*
  1. Remove the root -- NEVER change pointers. only swap objects.
  2. Bring the greater child upwards.
  3. Shift focus to the next node.
  */

  TreeNode<T> *currNode = root;
  T result = currNode->object;

  // replacing last element of the heap with the root.
  int num = size;
  int counter = floor(log(num) / log(2));
  num = num % static_cast<int>(floor(round(pow(2, counter))));

  int bit;

  if (size == 1) {
    size--;
    return result;
  }
  
  for (int i = counter; i > 0; i--)
  {
    bit = num / floor(round(pow(2, i - 1)));
    num = num % static_cast<int>(floor(round(pow(2, i - 1))));
    if (i == 1)
    {
      if (bit == 0)
      {
        root->object = currNode->left->object;
        currNode->left = nullptr;
      }
      else if (bit == 1)
      {
        root->object = currNode->right->object;
        currNode->right = nullptr;
      }
      break;
    }
    if (bit == 0)
    {
      currNode = currNode->left;
    }
    else if (bit == 1)
    {
      currNode = currNode->right;
    }
  }

  // Now performing a Heapify. i.e. swapping with higher element.

  currNode = root;

  while (currNode != nullptr)
  {
    if (currNode->left == nullptr) {
      break;
    }
    else if (currNode->right == nullptr) {
      swap(root->left->object, root->object);
      break;
    }
    else if (currNode->left->object < currNode->right->object) {
      swap(currNode->object, currNode->right->object);
      currNode = currNode->right;
    }
    else {
      swap(currNode->object, currNode->left->object);
      currNode = currNode->left; 
    }
  }
  size--;
  return result;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  const string prefix = "";
  cout << root->object << endl;
  printer(prefix, node->left, true);
  printer(prefix, node->right, false);
  return;
}

template <typename T>
void printer(const string &prefix, TreeNode<T> *root, bool isLeft)
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << root->object << endl;
    TreeNode<T> *curr = root;
    root = curr->left;
    // enter the next tree level - left and right branch
    printer(prefix + (isLeft ? "│   " : "    "), root, true);
    root = curr->right;
    printer(prefix + (isLeft ? "│   " : "    "), root, false);
    root = curr;
  }
}

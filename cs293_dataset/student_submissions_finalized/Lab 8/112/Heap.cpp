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
  return;
}

template <typename T>
void Heap<T>::delMax()
{

  // insert your code here

  return;
}

// Lab5 Tree.h printBinaryTree function
template <typename T>
void printBinaryTree(TreeNode<T> *root, const string &prefix, bool isLeft)
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    root->printInfo();
    cout << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printBinaryTree(root, prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
  else
  {
    cout << "NULL heap" << endl;
  }
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  printBinaryTree(root, "[", false);
  // insert your code here

  return;
}

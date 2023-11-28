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
  if (root == nullptr)
  {
    root = new TreeNode<T>(obj);
    number_of_nodes++;
    return;
  }
  TreeNode<T> *curr = root;
  int temp[20];
  int element = 0;
  int x = number_of_nodes + 1;
  while (x != 1)
  {
    temp[element] = x;
    element++;
    x = x / 2;
  }
  for (int i = element - 1; i > 0; i--)
  {
    if (temp[i] % 2 == 0)
    {
      curr = curr->left;
    }
    else if (temp[i] % 2 == 1)
    {
      curr = curr->right;
    }
  }
  if (temp[0] % 2 == 0)
  {
    curr->left = new TreeNode<T>(obj);
    curr->left->parent = curr;
    number_of_nodes++;
    Heapify(curr->left);
  }
  else if (temp[0] % 2 == 1)
  {
    curr->right = new TreeNode<T>(obj);
    curr->right->parent = curr;
    number_of_nodes++;
    Heapify(curr->right);
  }
  printHeap(root);
  return;
}

template <typename T>
void Heap<T>::delMax()
{

  // insert your code here
  if (root == nullptr)
  {
    return;
  }
  if (number_of_nodes == 1)
  {
    root = nullptr;
  }
  TreeNode<T> *curr = root;
  int temp[20];
  int element = 0;
  int x = number_of_nodes;
  while (x != 1)
  {

    temp[element] = x;
    element++;
    x = x / 2;
  }
  for (int i = element - 1; i > 0; i--)
  {
    if (temp[i] % 2 == 0)
    {
      curr = curr->left;
    }
    else if (temp[i] % 2 == 1)
    {
      curr = curr->right;
    }
  }
  if (temp[0] % 2 == 0)
  {
    root->object = curr->left->object;
    curr->left = nullptr;
    number_of_nodes--;
  }
  else if (temp[0] % 2 == 1)
  {
    root->object = curr->right->object;
    curr->right = nullptr;
    number_of_nodes--;
  }
  Heapify(root);
  return;
}

template <typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{

  TreeNode<T> *curr = node;

  if (curr->left != nullptr && curr->right == nullptr)
  {
    if (curr->object < curr->left->object)
    {
      T temp = curr->object;
      curr->object = curr->left->object;
      curr->left->object = temp;
      Heapify(curr->left);
    }
  }
  if (curr->left != nullptr && curr->right != nullptr)
  {
    if (curr->object < curr->left->object || curr->object < curr->right->object)
    {
      if (curr->right->object < curr->left->object)
      {
        T temp = curr->object;
        curr->object = curr->left->object;
        curr->left->object = temp;
        Heapify(curr->left);
      }
      else
      {
        T temp = curr->object;
        curr->object = curr->right->object;
        curr->right->object = temp;
        Heapify(curr->right);
      }
    }
  }
  if(curr->parent != nullptr)
  {
    if (curr->parent->object < curr->object)
    {

      T temp = curr->object;
      curr->object = curr->parent->object;
      curr->parent->object = temp;
      Heapify(curr->parent);
    }
  }
  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  static string prefix = "";
  static bool isleft = true;
  // insert your code here
  if (node != nullptr)
  {
    cout << prefix;

    cout << (isleft ? "|--" : "|__");

    // print the value of the node
    cout << node->object << endl;
    // enter the next tree level - left and right branch
    string temp = prefix;
    prefix = prefix + (isleft ? "│   " : "    ");
    isleft = true;
    printHeap(node->left);
    isleft = false;
    printHeap(node->right);
    prefix = temp;
  }
  return;
}

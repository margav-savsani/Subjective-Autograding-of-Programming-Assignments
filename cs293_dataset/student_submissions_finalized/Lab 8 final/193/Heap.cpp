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
  // where the insert is to be made
  // If root has not been inserted yet.

  if (totalinserted == 0)
  {
    this->root = new TreeNode<T>(obj);
    totalinserted++;
    return;
  }
  int num_itr = totalinserted + 1;
  // Vector to store the path of the nodes in the form of integers.
  vector<int> path;
  // Pushing into the vector the numbers that would represent the "virtual"
  // indices of the TreeNodes
  while (num_itr != 1)
  {
    path.push_back(num_itr);
    num_itr = num_itr / 2;
  }
  // An iterator object
  TreeNode<T> *iterate = root;
  // child object
  int child = 1;
  while (int(path.size()) != 1)
  {
    if (path.back() == 2 * child)
    {
      iterate = iterate->left; // Making the iterator the left of current
      child = path.back();
    }
    else
    {
      iterate = iterate->right; // Making the iterator the right of current
      child = path.back();
    }
    path.pop_back();
  }
  //For left child 
  if (path.back() == 2 * child)
  {
    iterate->left = new TreeNode<T>(obj);
    iterate->left->parent = iterate;
    iterate = iterate->left;
  }
  //For right child
  else
  {
    iterate->right = new TreeNode<T>(obj);
    iterate->right->parent = iterate;
    iterate = iterate->right;
  }
  //Check for the parents.
  while (iterate != root)
  {
    if (iterate->object < iterate->parent->object)
    {
      break;
    }
    swap(iterate->object, iterate->parent->object);
    iterate = iterate->parent;
  }
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
  else if (totalinserted == 1)
  {
    totalinserted--;
    root = NULL;
    return;
  }
  vector<int> path;
  int num_itr = totalinserted;
  // Pushing into the vector the numbers that would represent the "virtual"
  // indices of the TreeNodes
  while (num_itr != 1)
  {
    path.push_back(num_itr);
    num_itr = num_itr / 2;
  }
  // An iterator object
  TreeNode<T> *iterate = root;

  // child int to keep track of child of previous node
  int child = 1;
  while (int(path.size()) != 1)
  {
    if (path.back() == 2 * child)
    {
      iterate = iterate->left; // Making the iterator the left of current
      child = path.back();
    }
    else
    {
      iterate = iterate->right; // Making the iterator the right of current
      child = path.back();
    }
    path.pop_back();
  }
  if (path.back() == 2 * child)
  {
    swap(root->object, iterate->left->object);
    delete (iterate->left);
    iterate->left = NULL;
  }
  else
  {
    swap(root->object, iterate->right->object);
    delete (iterate->right);
    iterate->right = NULL;
  }
  totalinserted--;
  Heapify(this->root);
  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  printHeap_tree(" ", root, false);
}

template <typename T>
void Heap<T>::printHeap_tree(const string &prefix, TreeNode<T> *node, bool isLeft)
{
  if (node != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << node->object << endl;
    TreeNode<T> *curr = node;
    node = node->left;
    // enter the next tree level - left and right branch
    printHeap_tree(prefix + (isLeft ? "│   " : "    "), node, true);
    node = curr->right;
    printHeap_tree(prefix + (isLeft ? "│   " : "    "), node, false);
    node = curr;
  }
}

template <typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{
  // if(node == NULL) return;
  if (node == nullptr)
  {
    return;
  }
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
      return;
    }
  }
  // When none of children is greater than the node.
  if ((node->right->object < node->object) && (node->left->object < node->object))
    return;

  // Finally we have an object greater than the root.
  if (node->right->object < node->left->object)
  {
    swap(node->left->object, node->object);
    Heapify(node->left);
    return;
  }
  else
  {
    swap(node->right->object, node->object);
    Heapify(node->right);
    return;
  }
}

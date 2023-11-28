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
  TreeNode<T> *new_node = new TreeNode<T>(obj);
  if (lastinsert == root)
  {
    if (lastinsert->rating < root->rating)
      root->left = new_node;
    else
    {
      swap(root, new_node);
      root->left = new_node;
    }
    lastinsert = new_node;
    return;
  }
  else if (lastinsert->parent->left == lastinsert)
  {
    lastinsert->parent->right = new_node;
    new_node->parent = lastinsert->parent;
  }
  else
  {
    TreeNode<T> *curr = lastinsert;
    while (curr->parent->right == curr)
    {
      curr = curr->parent;
    }
    curr = curr->parent->right;
    while (curr->left != NULL)
    {
      curr = curr->left;
    }
    curr->left = new_node;
    new_node->parent = curr;
    curr = new_node;
    while ((curr->parent->rating < curr->rating) && curr->parent != NULL)
    {
      swap(curr->parent->rating, curr->rating);
      curr = curr->parent;
    }

    lastinsert = new_node;
  }

  return;
}

template <typename T>
void Heap<T>::delMax()
{

  // insert your code here
  swap(root->rating, lastinsert->rating);
  if (lastinsert->parent->left == lastinsert)
  {
    lastinsert->parent->left = NULL;
    TreeNode<T> *curr = lastinsert->parent;
    while(curr->parent->left==curr){
      curr=curr->parent;
    }
    curr=curr->parent->left;
    while(curr->right !=NULL){
      curr=curr->right;
    }
    lastinsert=curr->right;
  }
  else
  {
    lastinsert->parent->right = NULL;
    lastinsert = lastinsert->parent->left;
  }

  Heapify(root);
  return;
}
template <typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{
  TreeNode<T> *curr = node;
  if (node->right == NULL && node->left == NULL)
    return;
  else if (node->right == NULL)
  {
    if ((node->left->rating) > node->rating)
      swap(node->left->rating, node->rating);
    return;
  }
  else if (node->left == NULL)
  {
    if ((node->right->rating) > node->rating)
      swap(node->right->rating, node->rating);
    return;
  }
  else if (node->right->rating > node->rating && node->right->rating > node->left->rating)
  {
    swap(node->right->rating, node->rating);
    curr = node->right;
  }
  else if (node->left->rating > node->rating && node->left->rating > node->right->rating)
  {
    swap(node->left->rating, node->rating);
    curr = node->left;
  }
  Heapify(curr);
  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

  // insert your code here
  if (node == NULL)
    return;
  else
  {
    cout << node->rating << " ";
    printHeap(node->left);
    printHeap(node->right);
  }

  return;
}

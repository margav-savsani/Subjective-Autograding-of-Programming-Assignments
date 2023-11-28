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
  if (root == nullptr)
  {
    root = new_node;
    lastinsert = new_node;
   // printHeap("");
    return;
  }
  if (lastinsert == root)
  {
    if (new_node->object < root->object)
    {
      root->left = new_node;
      new_node->parent = root;
    }
    else
    {
      swap(root->object, new_node->object);
      root->left = new_node;
      new_node->parent = root;
    }
    lastinsert = new_node;
    //printHeap("");
    return;
  }
  else if (lastinsert->parent->left == lastinsert)
  {
    lastinsert->parent->right = new_node;
    new_node->parent = lastinsert->parent;
    lastinsert = new_node;

    TreeNode<T> *curr = new_node;
    while (curr->parent != NULL)
    {
      if (curr->parent->object < curr->object)
      {
        swap(curr->parent->object, curr->object);
      }
      curr = curr->parent;
    }
  }
  else
  {
    TreeNode<T> *curr = lastinsert;
    while (curr->parent->right == curr)
    {
      curr = curr->parent;
      if (curr == root)
        break;
    }
    if (curr != root)
      curr = curr->parent->right;

    while (curr->left != NULL)
    {
      curr = curr->left;
    }
    curr->left = new_node;
    new_node->parent = curr;

    curr = new_node;
    while (curr->parent != NULL)
    {
      if (curr->parent->object < curr->object)
      {
        swap(curr->parent->object, curr->object);
      }
      curr = curr->parent;
    }

    lastinsert = new_node;
  }
 // printHeap("");
  return;
}

template <typename T>
void Heap<T>::delMax()
{

  // insert your code here
  if (lastinsert == root)
  {
    root = NULL;
    lastinsert = NULL;
    return;
  }
  else if (root->right == NULL)
  {
    root->object = lastinsert->object;
    root->left = NULL;
    lastinsert = root;
    return;
  }

  swap(lastinsert->object, root->object);
  if (lastinsert == lastinsert->parent->right)
  {
    lastinsert->parent->right = NULL;
    lastinsert = lastinsert->parent->left;
  }
  else if (lastinsert == lastinsert->parent->left)
  {
    TreeNode<T> *curr = lastinsert->parent;
    lastinsert->parent->left = NULL;
    while (curr->parent->left == curr)
    {
      curr = curr->parent;
      if (curr == root)
        break;
    }
    if (curr != root)
      curr = curr->parent->left;

    while (curr->right != NULL)
    {
      curr = curr->right;
    }
    lastinsert = curr;
  }
  Heapify(root);
  return;
}
template <typename T>
void Heap<T>::Heapify(TreeNode<T> *node)
{
  //TreeNode<T> *curr = node;
  if (node == NULL)
    return;
  if (node->right == NULL && node->left == NULL)
    return;
  else if (node->right == NULL)
  {
    if (node->object < (node->left->object))
    {
      swap(node->left->object, node->object);
      node = node->left;
     // Heapify(node);
    }
    return;
  }
  // else if (node->left == NULL)
  // {
  //   if (node->object < (node->right->object))
  //     swap(node->right->object, node->object);
  //   return;
  // }
  else if ((node->object < node->right->object) && (node->left->object < node->right->object))
  {
    swap(node->right->object, node->object);
    node = node->right;
  }
  else if ((node->object < node->left->object) && (node->right->object < node->left->object))
  {
    swap(node->left->object, node->object);
    node = node->left;
  }
  else if ((node->object < node->left->object) && (node->object < node->right->object))
  {
    swap(node->object, node->left->object);
    node = node->left;
  }
  else if(( node->left->object < node->object ) && ( node->right->object < node->object )) return;
  else return;
  //printHeap("");
  Heapify(node);
  return;
}

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
}

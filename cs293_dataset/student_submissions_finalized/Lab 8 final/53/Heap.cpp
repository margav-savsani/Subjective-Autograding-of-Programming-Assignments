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
  TreeNode<T> *x = new TreeNode<T>(obj);
  TreeNode<T> *currNode;
  TreeNode<T> *parentNode;
  // case-1 : The heap is empty
  if (last_inserted == nullptr)
  {
    root = x;
    last_inserted = x;
  }
  // case 2 : otherwise
  else
  {
    currNode = last_inserted;
    parentNode = currNode->parent;
    while (parentNode != nullptr)
    { // Traversing from last_inserted node to find the first node such that it is the left child of its parent
      if (parentNode->left == currNode)
        break;
      else
      {
        currNode = parentNode;
        parentNode = parentNode->parent;
      }
    // If no such node was found till root was reached
    }
    if (parentNode == nullptr)
    {
      while (currNode->left != nullptr)
      {
        currNode = currNode->left;
      }
      currNode->left = x;
      x->parent = currNode;
      last_inserted = x;
    }
    // If such a node was found in the traversal
    else
    { // Traversing to the right most node from the found parent node . This right most node will give the place where insertion takes place
      currNode = parentNode->right;
      if (currNode == nullptr)
      {
        parentNode->right = x;
        x->parent = parentNode;
        last_inserted = x;
      }
      else
      {
        while (currNode->left != nullptr)
        {
          currNode = currNode->left;
        }
        currNode->left = x;
        x->parent = currNode;
        last_inserted = x;
      }
    }
  }
  // Insertion of the new node has been done, but it may not satisfy the max heap property
  // Swaping positions until max heap condition is satisfied
  parentNode = x->parent;
  while (parentNode != nullptr)
  {
    if (parentNode->object < x->object)
    {
      swap(x->object, parentNode->object);
      x = parentNode;
      parentNode = parentNode->parent;
    }
    else
    {
      break;
    }
  }
  //Insertion in the max heap is complete
  return;
}

template <typename T>
void Heap<T>::delMax()
{

  // insert your code here
  // The delete is based on Naveen Garg's lectures
  // The most important task is to find the new last_inserted node after deletion
  // swapping the last_inserted node content with root content
  swap(root->object, last_inserted->object);
  TreeNode<T> *parentNode = last_inserted->parent;
  // Case 1: when only root is present in the heap(basic case)
  if (parentNode == nullptr)
  {
    root = nullptr;
    last_inserted = nullptr;
    return;
  }
  // Case 2: When the last_inserted node is the left child
  if (parentNode->left == last_inserted)
  {
    TreeNode<T> *currentNode = last_inserted;
    parentNode->left = nullptr;
    while (parentNode != nullptr)
    {
      if (parentNode->right == currentNode)
      {
        break;
      }
      currentNode = parentNode;
      parentNode = parentNode->parent;
    }
    if (parentNode != nullptr)
    {
      currentNode = parentNode->left;
    }
    while (currentNode->right != nullptr)
    {
      currentNode = currentNode->right;
    }
    last_inserted = currentNode;
    heapify(root);
  }
  // Case 3: When the last_inserted node is the right child of its parent
  // The left child of the parent node just becomes the last inserted node
  else
  {
    parentNode->right = nullptr;
    last_inserted = parentNode->left;
    heapify(root);
  }
  return;
}

template <typename T>
void Heap<T>::heapify(TreeNode<T> *node)
{ // Implementing heapify with respect to the node given
  // Note that as there is no structural change in heap during heapify, the last_inserted node remains the same during the process
  // Base case: When the node is a leaf node
  TreeNode<T> *maxNode;
  if (node->left == nullptr && node->right == nullptr)
  {
    return;
  }
  // Case 2: When only the right child is a null pointer
  if (node->right == nullptr)
  {
    if (node->object < node->left->object)
    {
      swap(node->object, node->left->object);
      node = node->left;
      heapify(node);
      return;
    }
    else
    {
      return;
    }
  }
  // Case 3: Generalised case when both childs are existing
  else
  { // Comparing left and right child 
    // If left child has greater rating
    if (node->right->object < node->left->object)
    { // Check if there is any need of swapping with the parent node
      if (node->object < node->left->object)
      {
        swap(node->object, node->left->object);
        node = node->left;
        heapify(node);
        return;
      }
      else
        return;
    }
    // If right child has greater rating
    else
    { // Check if there is any need of swapping with the parent node
      if (node->object < node->right->object)
      {
        swap(node->object, node->right->object);
        node = node->right;
        heapify(node);
        return;
      }
      else
        return;
    }
  }
}

// *****IMP: call printHeap("") to print the heap at any point of time ***** //
template <typename T>
void Heap<T>::printHeap(const string &prefix, bool isLeft)
{
  // insert your code here
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

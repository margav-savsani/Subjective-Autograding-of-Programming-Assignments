#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
TreeNode<T> * Heap<T>::findNextLoc(TreeNode<T> *node)
{
  if(node == root)
  {
    TreeNode<T> *n = root;
    while(n->left != nullptr)
    {
      n = n->left;
    }
    return n;
  }
  else if(node == node->parent->left)
  {
    return node->parent->right;
  }
  else if(node == node->parent->right)
  {
    return findNextLoc(node->parent)->left;
  }
}

void Heap<T>::Heapify(TreeNode<T> *node)
{
  if(node->left == nullptr && node->right == nullptr)
  {
    return;
  }
  else if(node->right == nullptr)
  {
     if(node->object < node->left->object)
     {
        T temp = node->left->object;
        node->left->object = node->object;
        node->object = temp;
        node = node->left;
     }
     else
     {
      return;
     }
  }
  else if(node->left == nullptr)
  {
    if(node->object < node->right->object)
     {
        T temp = node->right->object;
        node->right->object = node->object;
        node->object = temp;
        node = node->right;
     }
     else
     {
      return;
     }
  }
  else
  {
    if(node->object < node->left->object || node->object < node->right->object)
    {
      if(!(node->right->object < node->left->object))
      {
        T temp = node->right->object;
        node->right->object = node->object;
        node->object = temp;
        node = node->right;
      }
      else
      {
        T temp = node->left->object;
        node->left->object = node->object;
        node->object = temp;
        node = node->left;
      }
      Heapify(node);
      else
      {
        return;
      }
    }
  }
}

void Heap<T>::insert(T obj) {
  // insert your code here
  if(root == NULL)
  {
    root = new TreeNode<T>(obj);
  }
  else
  {
    TreeNode<T> *node = root;
    while(node->left != nullptr)
    {
      node = node->left;
    }
    if(node->parent == nullptr)
    {
      if(node->left == nullptr)
      {
        node->left = new TreeNode<T>(obj);
      }
      else
      {
        node->right = new TreeNode<T>(obj);
      }
    }
    else
    {
      node = node->parent;
      while(true)
      {
        if(node->left == NULL)
        {
          node->left = new TreeNode<T>(obj);
          node = node->left;
          break;
        }
        else if(node->right == NULL)
        {
          node->right = new TreeNode<T>(obj);
          node = node->right;
          break;
        }
        else
        {
          node = findNextLoc(node);
        }
      }
    }
    while(true)
    {
      if(node->parent == NULL)
      {
        break;
      }
      else if(node->parent->object < node->object)
      {
        T temp = node->object;
        node->object = node->parent->object;
        node->parent->object = temp;
      }
      node = node->parent;
    }
  }
  return;
}

template<typename T>
void Heap<T>::delMax() {

  // insert your code here
  if(root == nullptr)
  {
    return;
  }
  else
  {
    TreeNode<T> *node = root;
    while(node != NULL)
    {
      node = node->left;
    }
    while(findNextLoc(node) != NULL)
    {
      node = findNextLoc(node);
    }
    root->object = node->object;
    if(node == node->parent->left)
    {
      node->parent->left = nullptr;
    }
    else
    {
      node->parent->right = nullptr;
    }
    node = nullptr;
    Heapify(root);
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {

  // insert your code here
  return;
}

  

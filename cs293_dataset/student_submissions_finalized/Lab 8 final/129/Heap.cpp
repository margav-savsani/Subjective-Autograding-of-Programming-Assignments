#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
// template<typename T>
// TreeNode<T>* Heap<T>::lastelement(TreeNode<T> *root){

// }
template <typename T>
void Heap<T>::heapify(TreeNode<T> *r) // Heapify works as it should
{
  if (r->left != nullptr && r->right != nullptr)
  {
    T max;
    if (r->left->object < r->right->object)
    {
      max = r->right->object;
    }
    else
    {
      max = r->left->object;
    }
    if (max < r->object)
    {
      return;
    }
    else
    {
      if (r->right->object < r->left->object)
      {
        swap(r->object, r->left->object);
        heapify(r->left);
      }
      else
      {
        swap(r->object, r->right->object);
        heapify(r->right);
      }
    }
  }
  else if (r->left != nullptr)
  {
    if (r->object < r->left->object)
    {
      swap(r->object, r->left->object);
      return;
    }
    else
    {
      return;
    }
  }
  else
  {
    return;
  }
}
template <typename T>
void Heap<T>::insert(T obj) // inserting a node
{
  // insert your code here
  if (root == nullptr)
  {
    root = new TreeNode<T>(obj);
    // presentelementparent=lastparent;
    presentelement = root;
    last = root->left;
    lastparent = root;
    return;
  }
  else
  {
    last = new TreeNode<T>(obj); // updating presentelement,last,lastparent
    if (lastparent->left == nullptr)
    {
      lastparent->left = last;
      last->parent = lastparent;
      // presentelementparent = lastparent;
      presentelement = last;
      last = lastparent->right;
      // return;
    }
    else if (lastparent->right == nullptr)
    {
      lastparent->right = last;
      last->parent = lastparent;
      // presentelementparent=lastparent;
      presentelement = last;
      bool a = true;
      while (lastparent->parent != nullptr)
      {
        if (lastparent->parent->left == lastparent)
        {
          lastparent = lastparent->parent;
          a = false;
          break;
        }
        lastparent = lastparent->parent;
      }
      if (a == true)
      {
        while (lastparent->left != nullptr)
        {
          lastparent = lastparent->left;
        }
        last = lastparent->left;
        // return;
      }
      else
      {
        lastparent = lastparent->right;
        while (lastparent->left != nullptr)
        {
          lastparent = lastparent->left;
        }
        last = lastparent->left;
      }
    }
  }
  TreeNode<T> *p = presentelement;
  while (p->parent != nullptr)
  {
    if (p->object < p->parent->object)
    {
      break;
    }
    else
    {
      swap(p->parent->object, p->object);
      p = p->parent;
    }
  }
  return;
}

template <typename T>
T Heap<T>::delMax() // deleting the root
{
  T x = root->object;
  swap(root->object, presentelement->object); // updating presentelement,last,lastparent
  if (presentelement == root)
  {
    root = nullptr;
    return x;
  }
  // presentelement->parent = lastparent;
  lastparent = presentelement->parent;
  if (lastparent->left == presentelement)
  {
    lastparent->left = nullptr;
  }
  else
  {
    lastparent->right = nullptr;
  }
  presentelement = nullptr;
  last = presentelement;
  TreeNode<T> *p = lastparent;
  if (p->left == nullptr)

  {
    bool b = true;
    while (p->parent != nullptr)
    {
      if (p->parent->right == p)
      {
        p = p->parent;
        b = false;
        break;
      }
      p = p->parent;
    }
    if (b == false)
    {
      p = p->left;
      while (p->right != nullptr)
      {
        p = p->right;
      }
    }
    else
    {
      while (p->right != nullptr)
      {
        p = p->right;
      }
    }
    presentelement = p;
  }
  else
  {
    presentelement = p->left;
  }
  heapify(root);

  // insert your code here

  return x;
}
template <typename T>
void Heap<T>::recursiveDelete(TreeNode<T> *node) // recursive deletion
{
  if (node == nullptr)
  {
    return;
  }
  else
  {
    TreeNode<T> *node1 = node->left;
    TreeNode<T> *node2 = node->right;

    recursiveDelete(node1);
    recursiveDelete(node2);
    delete node;
  }
}
template <typename T>
Heap<T>::~Heap()
{
  recursiveDelete(root);
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  if (node != nullptr)
  {
    static bool isLeft = true;
    static string y = "";
    static string z;
    z = isLeft ? "|--" : "|__";
    string x = y;
    cout << y;
    cout << z;
    cout << node->object << endl;
    TreeNode<T> *Y = node;
    node = node->left;
    isLeft = true;
    y = y + (isLeft ? "│   " : "    ");
    printHeap(node);
    node = Y->right;
    isLeft = false;
    y = x + (isLeft ? "│   " : "    ");
    printHeap(node);
    node = Y;
  }

  // insert your code here

  return;
}

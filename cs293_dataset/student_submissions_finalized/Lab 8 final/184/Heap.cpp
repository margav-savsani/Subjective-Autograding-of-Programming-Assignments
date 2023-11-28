#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

// bool function to know whether heapify is required or not.
template <typename T>
bool Heap<T>::should_heapify(TreeNode<T> *node)
{
  int left_val = 0;
  int right_val = 0;
  int node_val = node->object.rating;

  if (node->left == nullptr) // if there is no left child, then there wont be a right child for a heap.
  {
    return false;
  }
  else if (node->right == nullptr) // there is no right child but has left child.
  {
    left_val = node->left->object.rating;
    if (left_val > node_val)
      return true;
    else
      return false;
  }
  else
  {
    right_val = node->right->object.rating;
    left_val = node->left->object.rating;
    if (left_val > node_val || right_val > node_val) // if either left or right child rating is greater than node.
      return true;
    else
      return false;
  }
}
// bool function to know whether heapify is required or not.

// HEAPIFY
template <typename T>
void Heap<T>::heapify(TreeNode<T> *node)
{
  int left_val = 0;
  int right_val = 0;
  int node_val = node->object.rating;

  if (node->left == nullptr) // no child is present
  {
    return;
  }

  else if (node->right == nullptr) // only left child is present
  {
    left_val = node->left->object.rating;

    if (left_val > node_val)
    {
      T exchange = node->object;
      node->object = node->left->object;
      node->left->object = exchange;
    }
  }

  else // both left and right chils are present
  {
    left_val = node->left->object.rating;
    right_val = node->right->object.rating;

    if (left_val >= right_val)
    {
      if (left_val > node_val)
      {
        T exchange = node->object;
        node->object = node->left->object;
        node->left->object = exchange;
      }
    }
    else if (right_val > left_val)
    {
      if (right_val > node_val)
      {
        T exchange = node->object;
        node->object = node->right->object;
        node->right->object = exchange;
      }
    }
  }
  return;
}
// HEAPIFY

// RECURSIVE HEAPIFY
template <typename T>
void Heap<T>::recursive_heapify(TreeNode<T> *node) // recursive heap for the case of delete function.
{
  //cout << should_heapify(node) << endl; //
  if (should_heapify(node))
  {
    heapify(node);

    if (node->right == nullptr)
    {
      int left_val = node->left->object.rating;
      int node_val = node->object.rating;
      if (left_val > node_val)
      {
        T exchange = node->object;
        node->object = node->left->object;
        node->left->object = exchange;
      }
    }
    else
    {
      recursive_heapify(node->left);
      recursive_heapify(node->right);
    }
  }
  return;
}
// RECURSIVE HEAPIFY

// INSERT function
template <typename T>
void Heap<T>::insert(T obj)
{
  //cout << "entered insertion" << endl;
  // insert your code here

  if (root == nullptr) // root case: no element in the heap
  {
    //cout << "root is empty" << endl;
    root = new TreeNode<T>(obj);
    //cout << "rating of the first review:" << root->object.rating << endl;
    tail = root;
    //cout << tail->object.rating << endl;
  }
  else if (tail->left == nullptr)
  {
    //cout << "adding the new node as left child to the tail" << endl;
    tail->left = new TreeNode<T>(obj); // assigning the new node as left child of the tail
    tail->left->parent = tail;         // assigning parent pointer to the tail
    //cout << tail->left->object.rating << endl;
    // heapifying from inserted node, up the chain
    TreeNode<T> *h = tail;
    while (h != nullptr)
    {
      //cout << "entered heapify" << endl;
      //cout << should_heapify(h) << endl;
      if (should_heapify(h))
      {
        //cout << "heapify required" << endl;
        heapify(h);
        h = h->parent;
      }
      else
      {
        break;
      }
    }
    //cout << "heapify completed" << endl;
    // heapifying completed
  }
  else if (tail->right == nullptr)
  {
    //cout << "adding as right child to the tail" << endl;
    tail->right = new TreeNode<T>(obj);
    tail->right->parent = tail;
    //cout << tail->right->object.rating << endl;

    // heapifying from inserted node, up the chain
    TreeNode<T> *h = tail;
    while (h != nullptr)
    {
      //cout << "entered heapify" << endl;
      //cout << should_heapify(h) << endl;
      if (should_heapify(h))
      {
        //cout << "heapify required" << endl;
        heapify(h);
        h = h->parent;
      }
      else
      {
        //cout << "heapify not required" << endl;
        break;
      }
    }
    //cout << "heapify completed" << endl;
    // heapifying completed
    // if (tail != root)
    // {
    //   cout << tail->object.rating << endl;
    //   cout << tail->left->object.rating << endl;
    //   cout << tail->right->object.rating << endl;
    //   cout << tail->parent->object.rating << endl;
    // }
    // after heapifying need to change the tail so we know where to insert the next element
    if (tail == root) // root case
    {
      tail = tail->left;
      //cout << "tail became left child of the root" << endl;
    }
    else if (tail == tail->parent->left)
    {
      //cout << "tail becoming the right sibling" << endl;
      tail = tail->parent->right;
      //cout << "tail became the right sibling" << endl;
    }
    else if (tail == tail->parent->right)
    {
      //cout << "tail becoming x" << endl;
      TreeNode<T> *x = tail->parent;
      while (x != nullptr)
      {
        if (x == root)
        {
          while (x->left != nullptr)
          {
            x = x->left;
          }
          tail = x;
          break;
        }
        else if (x == x->parent->left)
        {
          x = x->parent->right;
          while (x->left != nullptr)
          {
            x = x->left;
          }
          tail = x;
          break;
        }
        else if (x == x->parent->right)
        {
          x = x->parent;
        }
      }
    }
  }
  //cout << "leaving insert" << endl;
  //cout << endl;
  return;
}

// function to get last node of the heap
template <typename T>
TreeNode<T> *Heap<T>::getlast()
{
  TreeNode<T> *x = tail;
  if (tail->left == nullptr)
  {
    //cout << "hi" << endl;
    while (x != nullptr & x != root)
    {
      if (x == x->parent->left)
      {
        //cout << x->object.rating << endl;
        x = x->parent;
        //cout << x->object.rating << endl;
      }
      else
      {
        break;
      }
    }
    if (x == root)
    {
      while (x->right != nullptr)
      {
        x = x->right;
      }
      return x;
    }
    else if (tail == tail->parent->right)
    {
      //cout << "enter right" << endl;
      x = tail;
      return x->parent->left->right;
    }
    else if (tail == tail->parent->left)
    {
      x = tail->parent;
      while (x != nullptr && x->parent != nullptr)
      {
        if (x == x->parent->right)
        {
          x = x->parent->left;
          while (x->right != nullptr)
          {
            x = x->right;
          }
          return x;
        }
        else if (x == x->parent->left)
        {
          x = x->parent;
        }
      }
    }
  }
  else if (tail->right == nullptr)
  {
    x = x->left;
  }
  //cout << "last element of the heap: " << x->object.rating << endl;
  return x;
}
// function to get last node of the heap

// delete function for maximum rated node, which is obviously root.
template <typename T>
void Heap<T>::delMax()
{

  // insert your code here
  T exchange = root->object;
  TreeNode<T> *last = getlast();
  //cout << tail->object.rating << endl; //
  root->object = last->object;
  //cout << root->object.rating << endl; //
  last->object = exchange;
  //cout << last->object.rating << endl; //
  tail = last->parent;
  //cout << tail->object.rating << endl; //

  if (last == tail->left)
  {
    tail->left = nullptr;
    //cout << "left deleted" << endl;
  }
  else if (last == tail->right)
  {
    tail->right = nullptr;
    //cout << "right deleted" << endl;
  }

  recursive_heapify(root);
  //cout << tail->object.rating << endl;
  //cout << (tail->left == nullptr) << endl;

  return;
}
// delete function for maximum rated node, which is obviously root.

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

  // insert your code here
  printBinayTree(node, " ", false );
  return;
}

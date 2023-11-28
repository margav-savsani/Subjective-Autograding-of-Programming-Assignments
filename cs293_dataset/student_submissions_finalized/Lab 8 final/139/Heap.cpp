#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::heapify(TreeNode<T> *node)
{
  int Left = 0;
  int Right = 0;
  int Value = node->object.rating;

  if (node->left == nullptr) // base case
  {
    return;
  }

  else if (node->right == nullptr) // only left child is present
  {
    Left = node->left->object.rating;

    if (Left > Value)
    {
      // swapping current node's and left child's data
      T temp = node->object;
      node->object = node->left->object;
      node->left->object = temp;
    }
  }

  else // both left and right children are present
  {
    Left = node->left->object.rating;
    Right = node->right->object.rating;

    if (Left >= Right)
    {
      if (Left > Value)
      {
        // swapping current node's and left child's data
        T temp = node->object;
        node->object = node->left->object;
        node->left->object = temp;
      }
    }
    else if (Right > Left)
    {
      if (Right > Value)
      {
        // swapping current node's and right child's data
        T temp = node->object;
        node->object = node->right->object;
        node->right->object = temp;
      }
    }
  }
  return;
}

template <typename T>
bool Heap<T>::Do_we_need_to_heapify(TreeNode<T> *node)
{
  int Left = 0;
  int Right = 0;
  int Value_of_the_current_node = node->object.rating;

  if (node->left == nullptr)
  // if there is no left child,obviously there wont be right child(heap prop).
  {
    return false;
  }
  else if (node->right == nullptr) // there is no right child but has left child.
  {
    Left = node->left->object.rating;
    if (Left > Value_of_the_current_node)
    {
      // if child is greater than parent, then it need to be changed urgently, so returned true.
      return true;
    }
    else // esle false.(no need).
      return false;
  }
  else
  {
    // has both chilren
    Right = node->right->object.rating;
    Left = node->left->object.rating;
    if (Left > Value_of_the_current_node || Right > Value_of_the_current_node) // if either left or right child rating is greater than node, it needs to be verified
      return true;
    else
      return false;
  }
}
// bool function to know whether heapify is required or not.

template <typename T>
void Heap<T>::Recursively_heapify(TreeNode<T> *node) {
  //This recursive function we use in case of delete function.
  if (Do_we_need_to_heapify(node))
  {
    heapify(node);

    if (node->right == nullptr)
    {
      int Value = node->object.rating, Left = node->left->object.rating;
      if (Left > Value)
      {
        T temp = node->object;
        node->object = node->left->object;
        node->left->object = temp;
      }
    }
    else
    {
      Recursively_heapify(node->left);
      Recursively_heapify(node->right);
    }
  }
  return;
}

// INSERT function
template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here

  if (root == nullptr)
  {
    // basecase: root is the obj;
    root = new TreeNode<T>(obj);
    // setting tail to root.
    tail = root;
  }
  else if (tail->right == nullptr)
  {
    // else, setting the tail's right child to it.
    tail->right = new TreeNode<T>(obj);
    tail->right->parent = tail; // assigning parent pointer to the tail
    // heapifying from this node, upwards

    TreeNode<T> *dummy = tail;
    int count = 0;
    while (dummy != nullptr)
    {
      count++;
      if (should_heapify(dummy))
      {
        heapify(dummy);
        dummy = dummy->parent;
      }
      else
        break;
    }

    // after heapifying,
    // we need to update our tail ptr.
    // basecase:
    if (tail == root)
      tail = tail->left;
    else if (tail == tail->parent->left)
    {
      // if tail is parent's left child, we need to set it to parents right child.
      tail = tail->parent->right;
    }
    else if (tail == tail->parent->right)
    {
      // if tail is parent's right child,
      TreeNode<T> *crawl = tail->parent;
      while (crawl != nullptr)
      {
        if (crawl == root)
        {
          while (crawl->left != nullptr)
            crawl = crawl->left;
          tail = crawl;
          break;
        }
        else if (crawl == crawl->parent->left)
        {
          crawl = crawl->parent->right;
          while (crawl->left != nullptr)
            crawl = crawl->left;
          tail = crawl;
          break;
        }
        else if (crawl == crawl->parent->right)
        {
          crawl = crawl->parent;
        }
      }
    }
  }
  else if (tail->left == nullptr)
  {
    tail->left = new TreeNode<T>(obj); // assigning the new node as left child of the tail
    tail->left->parent = tail;         // assigning parent pointer to the tail
    // heapifying from inserted node, up the chain
    // let the dummy pointer is tail
    int count = 0;
    TreeNode<T> *dummy = tail;
    while (dummy != nullptr)
    {
      count++;
      // checking whether heapifying is possible or not.if possible, the heapify, else then break out of the loop means, heaped.
      if (should_heapify(dummy))
      {
        heapify(dummy);
        dummy = dummy->parent;
      }
      else
        break;
    }
    // cout<<count<<endl;
  }
  return;
}

// function to get last node of the heap
template <typename T>
TreeNode<T> *Heap<T>::getla()
{
  TreeNode<T> *x = tail;
  if (tail->left == nullptr)
  {
    while (x != nullptr & x != root)
    {
      if (x == x->parent->left)
      {
        x = x->parent;
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
  return x;
}

// function to get last node of the heap

// delete function for maximum rated node, which is obviously root.
template <typename T>
void Heap<T>::delMax()
{

  // insert your code here
  T temp = root->object;

  //last node
  TreeNode<T> *last = getla();
  root->object = last->object;
  last->object = temp;
  tail = last->parent;


  if (last == tail->right)
  {
    tail->right = nullptr;
  }
  else if (last == tail->left)
  {
    tail->left = nullptr;
  }

  //recursively heapify
  Recursively_heapify(root);

  return;
}
// delete function for maximum rated node, which is obviously root.

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

  // insert your code here
  printBinayTree(node, " ", false);
  return;
}

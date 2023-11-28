#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

/*
Printing the Heap Recursively by using th eisLeft variable which denote if its the left element or rght element and then varying the prefix accordingly
*/
template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  static string prefix = "";
  static bool isLeft = false;
  static int recursion = 0;
  recursion++;
  if (node != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << node->object;
    cout << endl;
    TreeNode<T> *curr = node;
    node = node->left;
    // enter the next tree level - left and right branch
    isLeft = true;
    string store = prefix;
    prefix = prefix + (isLeft ? "│   " : "    ");

    printHeap(node);
    node = curr->right;
    isLeft = false;
    prefix = store + (isLeft ? "│   " : "    ");

    printHeap(node);
    node = curr;
  }
  else
  {
    cout << "NULL tree" << endl;
  }
  recursion--;
  if (recursion == 0)
  {
    isLeft = false;
    prefix = "";
  }
  // insert your code here

  return;
}
/*
This is a basic heapify alogrithm used when we insert an element at the last position we call the heapify on it and then if its value is ggreater than its parent value we swap it there and then recall the heapify again
*/

template <typename T>
void Heap<T>::Heapify(TreeNode<T> *x)
{
  if (x->parent != nullptr)
  {
    if (x->parent->object < x->object)
    {

      swap(x->object, x->parent->object);
      Heapify(x->parent);
    }
  }
}
/*
When first inserting for the first time, we set the value of last element in the heap as root of the heap. Next, time if the last element's left child is empty we insert the element there then call heapify on it to maintain the property of the heap. If the last elements's right child is empty we insert it there then we readjust the last element's location bby going to its parent then going to the left most child of the heap. We also store the last location of the last element as an attribute for future reference.
*/
template <typename T>
void Heap<T>::insert(T obj)
{

  if (root == nullptr)
  {
    root = new TreeNode<T>(obj);
    last = root;
  }
  else if (last->left == nullptr)
  {
    last->left = new TreeNode<T>(obj);
    last->left->parent = last;
    Heapify(last->left);
  }
  else
  {
    last->right = new TreeNode<T>(obj);
    last->right->parent = last;
    Heapify(last->right);

    TreeNode<T> *updater = last;
    ///////////////////
    while (true)
    {
      if (last->parent == nullptr)
      {
        while (last->left != nullptr)
        {
          last = last->left;
        }
        break;
      }
      else if (last->parent->left == last)
      {
        last = last->parent->right;
        while (last->left != nullptr)
        {
          last = last->left;
        }
        break;
      }
      else if (last->parent->right == last)
      {
        last=last->parent;
      }
      else{
        break;
      }
    }

    //////////////////
    last->updater = updater;
  }
  //  insert your code here

  return;
}
/*
This a reverse process of Heapify mentioned, in this we start from node and then switch it with its greater value child if its value is less than its child recursively
*/
template <typename T>
void Heap<T>::reverse(TreeNode<T> *x)
{
  if (x == nullptr)
  {
    return;
  }
  if (x->left == nullptr)
  {
    return;
  }

  TreeNode<T> *compare = x->left;
  if (x->right != nullptr)
  {
    if (compare->object < x->right->object)
    {

      compare = x->right;
    }
  }
  if (x->object < compare->object)
  {
    swap(x->object, compare->object);
    reverse(compare);
  }
}
/*
In this we delete the root of the tree. For the deleting it, we swap it with last element and then delete the last position, we removing the maximum value element. After that we call the reverse heaify. If the last element is such that it doesnt have a tail, we use last location of the last element in the heap and then delete its child as these were the last element inserted.
*/
template <typename T>
void Heap<T>::delMax()
{
  if (root == nullptr)
  {

    return;
  }
  if (last == root)
  {
    if (last->right != nullptr)
    {
      swap(last->right->object, root->object);
      last->right = nullptr;
      reverse(root);
    }
    else if (last->left != nullptr)
    {
      swap(last->left->object, root->object);
      last->left = nullptr;
      reverse(root);
    }
    else
    {
      last = nullptr;
      root = nullptr;
    }
  }
  else
  {
    if (last->right != nullptr)
    {
      swap(last->right->object, root->object);
      last->right = nullptr;
      reverse(root);
    }
    else if (last->left != nullptr)
    {
      swap(last->left->object, root->object);
      last->left = nullptr;
      reverse(root);
    }
    else
    {
      last = last->updater;
      delMax();
    }
  }

  return;
}

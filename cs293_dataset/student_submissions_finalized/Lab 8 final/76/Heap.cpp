#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::insert(T obj)
{

  if (root == nullptr)
  {
    root = new TreeNode<T>(obj); // if root is null I have created a node at root and inserted there
  }
  else
  {
    TreeNode<T> *p = root;
    checkpos(p, obj);
  }

  return;
}

template <typename T>
void Heap<T>::checkpos(TreeNode<T> *op, T obj)
{

  bool b = false;

  if (op->left == nullptr)
  { // check left pointer

    op->left->object = obj;
    op = op->left;
    b = true;
    while (op != nullptr && op->parent->object < op->object)
    { // swapping objects

      swap(op->object, op->parent->object); // heapify
      op = op->parent;                      // from the inserted element
    }
    return;
  }
  else if (op->left != nullptr && op->right == nullptr)
  { // if right poiner is null,insert at right

    op->right->object = obj;
    op = op->right;
    b = true;
    while (op != nullptr && op->parent->object < op->object)
    {
      swap(op->object, op->parent->object);
      op = op->parent;
    }
    return;
  }
  else if (op->left != nullptr && op->right != nullptr)
  { // if both are not null pointers,we recursively go to last element it is supposed to be inserted
    // and add pointer to its parent appropriately
    TreeNode<T> *m;
    TreeNode<T> *n;
    m = op->left;
    n = op->right;
    cntl++;
    cntr++; // I will count the iterations it is participation recursively and constraint to 1 for each function and recurse
    if (cntl < 2)
    {
      checkpos(m, obj);
    }
    if (b == false && cntr < 2)
    {
      checkpos(n, obj);
    }
    cntl = 0;
    cntr = 0;
  }
  return;
}
template <typename T>
void Heap<T>::Heapify(TreeNode<T> *op)
{
  TreeNode<T> *lar = root;
  if (op->left != nullptr && (lar->object < op->left->object)) // if left is greater than parent,largest will be the left and we update it
  {
    lar = op->left;
  }
  if (op->right != nullptr && (lar->object < op->right->object)) // if right is greater than parent,largest will be the right and we update it
  {
    lar = op->right;
  }
  if (lar != root)
  {
    swap(lar->object, root->object); // we will store the largest node and swap acoordingly
    Heapify(op);
  }
  else
    return;
}
template <typename T>
void Heap<T>::delMax()
{
  if (root == nullptr) // if the root is a null pointer it will return
    return;
  else
    del(root); // else it takes argument as root
  return;
}
template <typename T>
void Heap<T>::del(TreeNode<T> *op)
{
  bool b = false;
  TreeNode<T> *s;

  if (op->left == nullptr) // if left is nullptr
  {
    swap(op->object, root->object);
    op = nullptr;
    b = true;
    return;
  }

  else if (op->right == nullptr) // if right is nullptr
  {
    swap(op->left->object, root->object);
    op->left = nullptr;
    b = true;
    return;
  }
  else if (op->left != nullptr && op->right != nullptr) // if both not nullptrs
  {
    TreeNode<T> *m;
    TreeNode<T> *n;
    m = op->left;
    del(m);
    if (b == false)
    {
      n = op->right;
      del(n);
    }
  }
}

template <typename T>
void Heap<T>::prthp(const string &prefix, bool isLeft)
{
  if (root != nullptr)
  {
    cout << prefix;

    cout << (isLeft ? "|--" : "|__");

    // print the value of the node
    cout << root->JourneyCode << endl;
    TreeNode<T> *curr = root;
    root = root->left;
    // enter the next tree level - left and right branch
    prthp(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    prthp(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}
template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

  prthp("");
  return;
}

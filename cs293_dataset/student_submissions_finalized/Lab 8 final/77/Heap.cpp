#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include <cmath>

// minHeight gives minimum height at which leaf is present
template <typename T>
int Heap<T>::minHeight(TreeNode<T> *a)
{
  if (a == NULL)
  {
    return 0;
  }
  return (1 + min(minHeight(a->left), minHeight(a->right)));
}
// Inserts object into Heap.
// Insert is done using recursion.
template <typename T>
void Heap<T>::insert(T obj)
{
  // If root is NULL it creates new TreeNode<T>
  // Base case for recursion
  if (root == NULL)
  {
    root = new TreeNode<T>(obj);
    return;
  }
  // To satisfy heap constraints I'm checking object here only. If new object is greater then swaping here .
  if (root->object < obj)
  {
    swap(root->object, obj);
  }
  // Checks if root->left is null
  if (root->left == NULL)
  {
    Heap *leftpart = new Heap(root->left);
    leftpart->insert(obj);
    root->left = leftpart->root;
    leftpart->root->parent = root;
  }
  // Checks if root->right is null
  else if (root->right == NULL)
  {
    Heap *rightpart = new Heap(root->right);
    rightpart->insert(obj);
    root->right = rightpart->root;
    rightpart->root->parent = root;
  }
  // If both root->left and root->right not NULL.
  else
  {
    // If left part is filled completely(If left has min. height n+1 and right has n then inserts into right)
    if (minHeight(root->left) > minHeight(root->right))
    {
      Heap *rightpart = new Heap(root->right);
      root->right = rightpart->root;
      rightpart->root = root->right;
      rightpart->insert(obj);
    }
    // If left part is not filled completely.
    else
    {
      Heap *leftpart = new Heap(root->left);
      leftpart->root = root->left;
      root->left = leftpart->root;
      leftpart->insert(obj);
    }
  }
  return;
}

// Calculates the height of node
template <typename T>
int Heap<T>::height(TreeNode<T> *a)
{
  if (a == NULL)
  {
    return 0;
  }
  return (1 + max(height(a->left), height(a->right)));
}

// This function heapifies the node (going downwards)
// Heapify uses Recursion
template <typename T>
void Heap<T>::Heapify(TreeNode<T> *root)
{
  // Corner case
  if (root == NULL)
  {
    return;
  }
  // Base case
  else if (root->left == NULL && root->right == NULL)
  {
    return;
  }
  // If left is NULL
  else if (root->left == NULL)
  {
    if (root->object < root->right->object)
    {
      swap(root->right->object, root->object);
    }
    Heapify(root->right);
  }
  // If right is NULL
  else if (root->right == NULL)
  {

    if (root->object < root->left->object)
    {
      swap(root->left->object, root->object);
    }
    Heapify(root->left);
  }
  // If both left and right of root are not NULL
  else
  {
    bool leftAndRoot = false;
    if (root->left->object < root->object)
    {
      leftAndRoot = true;
    }
    bool rightAndRoot = false;
    if (root->right->object < root->object)
    {
      rightAndRoot = true;
    }
    bool leftAndRight = false;
    if (root->left->object < root->right->object)
    {
      leftAndRight = true;
    }
    if (leftAndRoot && rightAndRoot)
    {
      Heapify(root->left);
      Heapify(root->right);
    }
    if (!leftAndRoot && !leftAndRight)
    {
      swap(root->object, root->left->object);
      Heapify(root->left);
      Heapify(root->right);
    }
    if (!rightAndRoot && leftAndRight)
    {
      swap(root->object, root->right->object);
      Heapify(root->left);
      Heapify(root->right);
    }
  }
}

// Gives last element in the Heap
// Last means rightmost element in last level of heap
template <typename T>
TreeNode<T> *Heap<T>::getlast(TreeNode<T> *a)
{
  if (a->left == NULL && a->right == NULL)
  {
    return a;
  }
  int l = height(a->left);
  int r = height(a->right);
  if (l > r)
  {
    return (getlast(a->left));
  }
  return (getlast(a->right));
}

// Deletes the root
template <typename T>
void Heap<T>::delMax()
{
  if(root->left==NULL && root->right==NULL){
    root=NULL;
    return;
  }
  TreeNode<T> *last = getlast(root);
  swap(root->object, last->object);
  if (last->parent != NULL)
  {
    if (last->parent->left == last)
    {
      last->parent->left = NULL;
    }
    else
    {
      last->parent->right = NULL;
    }
  }
  delete last;
  Heapify(root);
  //printHeap(root);
  return;
}

// To print Heap like binary tree, I used BST print function.
template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  print(node, "", true);
  return;
}
// BST print function.
template <typename T>
void Heap<T>::print(TreeNode<T> *node, const string &prefix, bool isLeft)
{
  if (node != nullptr)
  {
    cout << prefix;
    cout << (isLeft ? "|--" : "|__");
    // print the value of the node
    // node->printInfo();
    cout << node->object << endl;
    TreeNode<T> *curr = node;
    node = node->left;
    // enter the next tree level - left and right branch
    print(node, prefix + (isLeft ? "│   " : "    "), true);
    node = curr->right;
    print(node, prefix + (isLeft ? "│   " : "    "), false);
    node = curr;
  }
}

/*
// This is used to check whether heap is working or not
int main(){
  Heap<int> a;

  a.insert(8);
  a.insert(14);
  a.insert(17);
  a.insert(43);
  a.insert(7);
  a.insert(90);
  a.insert(19);
  a.insert(86);
  cout<<a.getMax()<<endl;
  a.delMax();
  cout<<a.getMax()<<endl;
}
*/
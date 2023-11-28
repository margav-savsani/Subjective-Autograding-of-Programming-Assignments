#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::Swap(TreeNode<T> *a, TreeNode<T> *b)
{
  T temp = a->object;
  a->object = b->object;
  b->object = temp;
}
template <typename T>
TreeNode<T> *Heap<T>::max(TreeNode<T> *a, TreeNode<T> *b)
{
  if (a->object < b->object)
  {
    return b;
  }
  else
  {
    return a;
  }
}
template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here
  TreeNode<T> *S = new TreeNode<T>(obj);
  if (root == nullptr)
  {
    root = S;
    last = root;
    curr_num++;
    return;
  }
  else if(curr_num == 1)
  {
    root->left = S;
    last = root->left;
    curr_num++;
    return;
  }
  else
  {
    int num = floor(log2(curr_num));
    int max = pow(2, num - 1) - 1;
    if (last->parent->left == last && max != curr_num)
    {
      last = last->parent->right;
      last = S;
    }
    else if (last->parent->right == last && max == curr_num)
    {
      last = root;
      while (last->left != nullptr)
      {
        last = last->left;
      }
      last->left = S;
      last = last->left;
      
    }
    else if (last->parent->right == last && max != curr_num)
    {
      int i = curr_num;
      int j = curr_num + 1;
      while (i != j)
      {
        i = (i - 1) / 2;
        j = (j - 1) / 2;
        last = last->parent;
      }
      last = last->right;
      while (last->left != nullptr)
      {
        last = last->left;
      }
      last->left = S;
      last = last->left;
    }
    while ((last->parent->object < last->object) && (last->parent != nullptr))
    {
      Heap<T>::Swap(last, last->parent);
    }
    curr_num++;
    return;
  }
}

template <typename T>
void Heap<T>::delMax()
{

  // insert your code here
  Heap<T>::Swap(last, root);
  if (last->parent->left == last)
  {
    last->parent->left = nullptr;
    int i = curr_num;
    int j = curr_num - 1;
    while (i != j)
    {
      i = (i - 1) / 2;
      j = (j - 1) / 2;
      last = last->parent;
    }
    last = last->left;
    while (last->right != nullptr)
    {
      last = last->right;
    }
  }
  else if (last->parent->right == last)
  {
    last->parent->right = nullptr;
    last = last->parent->left;
  }
  TreeNode<T> *M = root;
  while (true)
  {
    if (root == nullptr)
    {
      break;
    }
    TreeNode<T> *N = max(root->left, root->right);
    if (root->object < N->object)
    {
      Heap<T>::Swap(N, root);
      root = N;
    }
    else
    {
      break;
    }
  }
  root = M;
  return;
}

template <typename T>
void Heap<T>::print(TreeNode<T> *r, const string &prefix, bool isLeft)
{
  if (r != prefix)
  {
    cout << prefix;
    cout << (isLeft ? "|--" : "|__");
    cout << r->object;
    cout << endl;
    TreeNode<T> *curr = r;
    r = r->left;
    print(r, prefix + (isLeft ? "|  " : "   "), true);
    r = curr->right;
    print(r, prefix + (isLeft ? "|  " : "   "), false);
    r = curr;
  }
  else
  {
    cout << "NULL tree" << endl;
  }
  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

  // insert your code here
  print(node, "", false);
  // cout<<root->object;
  // Heap<T>::printHeap(node->left);
  // Heap<T>::printHeap(node->right);
  return;
}
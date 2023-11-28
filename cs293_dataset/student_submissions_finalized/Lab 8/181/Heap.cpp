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

  if (root == NULL)
  {
    root = new TreeNode(obj);
    return;
  }
  TreeNode<T> *x = root;
  while (true)
  {
    if (x->Height() == 1)
    {
      if (x->imbalance())
      {
        x->right = new TreeNode(obj);
        x->right->parent = x;
        x = x->right;
      }
      else
      {
        x->left = new TreeNode(obj);
        x->left->parent = x;
        x = x->left;
      }
      break;
    }
    if (x->left->Height() > x->right->Height())
    {
      x = x->right;
    }
    else
    {
      x = x->left;
    }
  }
  while (true)
  {
    if (x->parent == NULL)
    {
      return;
    }
    if (x->object > x->parent->object)
    {
      T Z = x->object;
      x->object = x->parent->object;
      x->parent->object = Z;
      x = x->parent;
    }
    else
      break;
  }
  return;
}

template <typename T>
void Heap<T>::delMax()
{
  TreeNode<T> *x = root;
  // insert your code here

  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

  // insert your code here
  TreeNode<T> *x = root;
  cout<<root->object<<endl;
   
  return;
}

int main()
{
  Heap<int> *h = new Heap<int>();
   h->insert(100);
  h->insert(20);
  h->insert(10);
  h->insert(30);
  h->insert(5);
  h->insert(25);
  h->insert(450);
  h->insert(45);
 h->insert(15);
 h->insert(1200);
  cout << h->getMax();
}
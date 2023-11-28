#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
bool is_child_left(TreeNode<T> *chi, TreeNode<T> *par)
{
  if (par == nullptr || chi == nullptr)
    return false;
  else if (par->left == chi)
    return true;
  else if (par->right == chi)
    return false;
  else
    return false;
}

template <typename T>
void swap_elements(TreeNode<T> *&chi, TreeNode<T> *&par)
{
  T temp = chi->object;
  chi->object = par->object;
  par->object = temp;
}

template <typename T>
void Heap<T>::insert(T obj)
{
  if (root == nullptr)
  {
    root = node;
    height++;
    current = node;
    return;
  }
  TreeNode<T> *curr = current;
  bool left_present = false;
  while (curr->parent != nullptr && !is_child_left(curr, curr->parent))
  {
    curr = curr->parent;
  }
  if (is_child_left(curr, curr->parent))
  {
    curr = curr->parent;
    left_present = true;
  }
  if (left_present)
  {
    TreeNode<T> *temp_par = curr;
    curr = curr->right;
    if (curr == nullptr)
    {
      temp_par->right = node;
      node->parent = temp_par;
      pre_current = current;
      current = node;
    }
    else
    {
      temp_par = curr;
      curr = curr->left;
      while (curr != nullptr)
      {
        temp_par = curr;
        curr = curr->left;
      }
      if (curr == nullptr)
      {
        temp_par->left = node;
        node->parent = temp_par;
        pre_current = current;
        current = node;
      }
    }
  }
  else
  {
    TreeNode<T> *temp_par = curr;
    curr = curr->left;
    while (curr != nullptr)
    {
      temp_par = curr;
      curr = curr->left
    }
    if (curr == nullptr)
    {
      temp_par->left = node;
      node->parent = temp_par;
      pre_current = current;
      current = node;
      height++;
    }
  }

  TreeNode<T> *upward_moving = node;
  while ((upward_moving->object) > (upward_moving->parent->object) || upward_moving->parent == nullptr)
  {
    swap_elements(upward_moving, upward_moving->parent);
    node = node->parent;
    if (node->parent == nullptr)
    {
      root = node;
    }
  }
  return;
}
template <typename T>
void Heapify(TreeNode<T> *node)
{
  if(node->right == nullptr && node->left!= nullptr && node->left->object < node->object)
  {
    swap_elements(node->left, node);
    return;
  }
  else if(node->right == nullptr && node->left== nullptr)
  {
    return;
  }
  else if( (node->left->object < node->object) && (node->right->object < node->object) )
  {
    if(node->left->object >= node->right->object)
    {
      swap_elements(node->left, node);
      Heapify(node->left);
    }
    else
    {
      swap_elements(node->right, node);
      Heapify(node->right);
    }
  }
  else
  {
    return;
  }
  
}
template <typename T>
void Heap<T>::delMax()
{
  TreeNode<T> *rem = root;
  TreeNode<T> *last = current;
  swap_elements(last, rem);
  if(is_child_left(last, last->parent))
  {
    last->parent->left == nullptr;
    last->parent == nullptr;
  }
  else
  {
    last->parent->right == nullptr;
    last->parent == nullptr;
  }
  Heapify(rem);
  root = rem;

}

  // insert your code here

 

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
}

class Heap
{
public:
  int cap;
  int n;
  vll H;

  Heap(int cap)
  {
    this->cap = cap;
    n = 0;
  }

  int parent(int i)
  {
    int j = (i - 1) / 2;
    return j;
  }

  int left(int i)
  {
    return (2 * i) + 1;
  }

  int right(int i)
  {
    return 2 * (i + 1);
  }

  void insert(int val)
  {
    if (n != cap)
    {
      H.push_back(val);
      int i;
      i = n;
      n = n + 1;
      while ((i != 0) && H[parent(i)] > H[i])
      {
        int temp;
        temp = H[i];
        H[i] = H[parent(i)];
        H[parent(i)] = temp;
        i = parent(i);
      }
    }
  }
  int min()
  {
    if (n != 0)
      return H[0];
    return -1;
  }

  void Heapify(int root)
  {
    int l = left(root);
    int r = right(root);
    int s = root;
    if (l < n && H[l] < H[root])
      s = l;
    if (r < n and H[r] < H[s])
      s = r;
    if (s != root)
    {
      int temp;
      temp = H[s];
      H[s] = H[root];
      H[root] = temp;
      Heapify(s);
    }
  }

  void deleteMin()
  {
    if (n > 0)
    {
      if (n == 1)
      {
        H[0] = -1;
        n = 0;
      }
      else
      {
        n = n - 1;
        H[0] = H[n];
        H.pop_back();
        Heapify(0);
      }
    }
  }
};

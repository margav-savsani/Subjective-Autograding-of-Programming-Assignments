#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
#include <cmath>
template <typename T>
TreeNode<T> *Heap<T>::getnode(int n)
{
  if (n < 2)
    return root;

  TreeNode<T> *active = root;

  if (n % 2 == 0) {
    n = n/2;
    return getnode(n)->left;
  }
  else{
    n = n/2;
    return getnode(n)->right;
  }
}

template <typename T>
bool Heap<T>::exchange(TreeNode<T> *node1, TreeNode<T> *node2)
{
  cout<<1<<endl;
  T temp = node1->object;
  node1->object = node2->object;
  node2->object = temp;

  return true;
}

template <typename T>
void Heap<T>::heapfy(TreeNode<T> *active)
{
  if (active == nullptr)
    return;
  else if (active->left == nullptr)
    return;
  else if (active->right == nullptr)
  {
    cout<<1<<endl;
    if (active->object < active->left->object) {
      cout<<1<<endl;
      exchange(active, active->left);
      heapfy(active->parent);
      return;
    }
    else
      return;
  }
  else
  {
    if (active->object < active->left->object || active->object < active->right->object)
    {
      cout<<1<<endl;
      if (active->right->object < active->left->object)
        exchange(active, active->left);
      else
        exchange(active, active->right);
      heapfy(active->parent);
      return;
    }
    else
    {
      heapfy(active->left);
      heapfy(active->right);
    }
  }
}

template <typename T>
void Heap<T>::insert(T obj)
{
  if(root == nullptr) {
    root = new TreeNode<T>(obj);
    return;
  }
  // insert your code here
  TreeNode<T> *active;
  total_nodes++;
  active = getnode(total_nodes / 2);
  if (total_nodes % 2 == 0)
  {
    active->left = new TreeNode<T>(obj);
  }
  else
    active->right = new TreeNode<T>(obj);

    heapfy(root);
  return;
}

template <typename T>
void Heap<T>::delMax()
{

  // insert your code here
  root->object = getnode(total_nodes)->object;
  TreeNode<T> *active = getnode(total_nodes);
  active = nullptr;
  total_nodes--;
  heapfy(root);

  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  static string gap = "";
  if (node == root)
  {
    gap = "";
    cout << gap << "|++" << node->object << endl;
    gap = gap +"  ";
  }

  // insert your code here
  if (node->left != nullptr)
  {
    cout << gap << "|--" << node->left->object << endl;
    gap = gap + "  ";
    printHeap(node->left);
    gap = gap.erase(gap.size() - 2);
  }

  if (node->right != nullptr)
  {
    cout << gap << "|__" << node->right->object << endl;
    gap = gap + "  ";
    printHeap(node->right);
    gap = gap.erase(gap.size() - 2);
  }
  return;
}

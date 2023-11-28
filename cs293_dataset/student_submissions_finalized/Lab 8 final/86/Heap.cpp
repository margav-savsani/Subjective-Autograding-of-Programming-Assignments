#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

using namespace std;

template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here
  TreeNode<T> *newnode = new TreeNode<T>(obj);

  if (root == nullptr)
  {
    root = new TreeNode<T>(obj);
    elem_count = 1;
    return;
  }
  if(root->left == nullptr)
  {
    root->left = newnode;
    newnode->parent = root;
    elem_count++;
    return;
  }
  elem_count++;
  int highorder = 1;
  int power_2 = 2;
  while(true)
  {
    if(elem_count % power_2 == elem_count) break;
    else 
    {
      highorder++;
      power_2 = 2*power_2;
    }
  }
  
  power_2 = power_2 / 2;

  highorder = ((elem_count - (power_2*(elem_count / power_2))) / (power_2 / 2) );
  
  TreeNode<T> *temp = root;
  TreeNode<T> *temp_par;
  while(true)
  {
    temp_par = temp;
    if(highorder == 0) temp = temp->left;
    else temp = temp->right;
    power_2 = power_2 / 2;
    if(power_2 == 1) break;
    highorder = ((elem_count - (power_2*(elem_count / power_2))) / (power_2 / 2) );
  }

  if (elem_count % (2*power_2) == 0)
  {
    temp_par->left = newnode;
    newnode->parent = temp_par;
  }
  else
  {
    temp_par->right = newnode;
    newnode->parent = temp_par;
  }
  int i = elem_count - 1;
  while (i != 0 && temp_par->object < newnode->object)
  {
    T just = newnode->object;
    newnode->object = temp_par->object;
    temp_par->object = just;
    i = (i - 1) / 2;
    newnode = temp_par;
    temp_par = temp_par->parent;
  }
  return;
}

template <typename T>
void Heap<T>::delMax()
{
  // insert your code here
  if (root->left == nullptr)
  {
    root = nullptr;
    return;
  }
  if(root->right == nullptr)
  {
    root = root->left;
    root->left = nullptr;
    return;
  }
  int highorder = 1;
  int power_2 = 2;
  while(true)
  {
    if(elem_count % power_2 == elem_count) break;
    else 
    {
      highorder++;
      power_2 = 2*power_2;
    }
  }
  power_2 = power_2 / 2;
  highorder = ((elem_count - (power_2*(elem_count / power_2))) / (power_2 / 2) );
  
  TreeNode<T> *temp = root;
  TreeNode<T> *temp_par;
  while(true)
  {
    temp_par = temp;
    if(highorder == 0) temp = temp->left;
    else temp = temp->right;
    power_2 = power_2 / 2;
    if(power_2 == 1) break;
    highorder = ((elem_count - (power_2*(elem_count / power_2))) / (power_2 / 2) );
  }
  root->object = temp->object;
  if (temp_par->right == temp)
  {
    temp_par->right = nullptr;
  }
  else
  {
    temp_par->left = nullptr;
  }
  temp = nullptr;
  elem_count--;
  int i = 0;
  temp = root;

  while (temp->left != nullptr)
  {
    if(temp->right == nullptr)
    {
      if(temp->object < temp->left->object)
      {
         T *just = new T();
         TreeNode<T> *replace = temp->left;
         *just = replace->object;
         replace->object = temp->object;
         temp->object = *just;
      }
      break;
    }
    if (temp->left->object < temp->object && temp->right->object < temp->object) //
    {
      break;
    }
    else
    {
      if (temp->right->object < temp->left->object) //
      {
        T *just = new T();
        TreeNode<T> *replace = temp->left;
        *just = replace->object;
        replace->object = temp->object;
        temp->object = *just;
        i = 2 * i + 1;
        temp = temp->left;
      }
      else
      {
        T *just = new T();
        TreeNode<T> *replace = temp->right;
        *just = replace->object;
        replace->object = temp->object;
        temp->object = *just;
        i = 2*i + 2;
        temp = temp->right;
      }
    }
  }
  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  // insert your code here
  
}

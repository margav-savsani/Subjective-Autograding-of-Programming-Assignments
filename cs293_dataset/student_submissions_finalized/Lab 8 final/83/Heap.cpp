#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif
using namespace std;

int *arr(int no)
{
  int count = 0, a = no; // storing no into a and making a variable count.
  for (count; a > 0; a = a / 2)
    count++;
  // Taking the points where parent nodes present
  int *arr = new int[count + 1];
  for (int i = 0; i < count; i++)
  {
    arr[i] = no % 2;
    no = no / 2;
  }
  int begin = 0, finish = count - 1;
  for (begin; begin < finish; begin++)
  {
    int m = arr[begin];
    arr[begin] = arr[finish];
    arr[finish] = m;
    finish--;
  }
  arr[count] = 2;
  return arr;
}

template <typename T>
void swapping(TreeNode<T> *ob1, TreeNode<T> *ob2)
{
  T object1 = ob1->object;
  T object2 = ob2->object;
  ob1->object = object2;
  ob2->object = object1;
}

template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here

  num_elements++;
  TreeNode<T> *new_root = new TreeNode(obj);

  if (root == nullptr)
  {
    root = new_root;
    return;
  }

  TreeNode<T> *current = root;

  int *result = arr(num_elements);
  int j = 0;
  while (result[j] != 2)
    j++;
  for (int i = 1; i < j - 1; i++)
  {
    if (result[i] == 0)
      current = current->left;
    else
      current = current->right;
  }
  if (result[j - 1] == 1)
    current->right = new_root;

  else
    current->left = new_root;

  new_root->parent = current;

  current = new_root;

  while (current->parent != nullptr)
  {
    if(current->parent->object < current->object){
      swapping(current, current->parent);
      current = current -> parent;
    }
    else return;
  }  
  return;
}

template <typename T>
void Heapify(TreeNode<T> *node)
{

  if (node == nullptr)
    return;

  TreeNode<T> *left_child = node->left;
  TreeNode<T> *right_child = node->right;

  if (left_child == nullptr && right_child == nullptr)
    return;

  if ((right_child == nullptr) && (left_child != nullptr))
  {
    if (node->object < left_child->object)
    {
      swapping(node, left_child);
      Heapify(left_child);
      return;
    }
    else
      return;
  }

  if ((right_child != nullptr) && (left_child == nullptr))
  {
    if(node->object < right_child->object)
    {
      swapping(node, right_child);
      Heapify(right_child);
      return;
    }
    else return;
  }

  if (right_child != nullptr && left_child != nullptr)
  {
    if ((node->object < left_child->object) || (node->object < right_child->object))
    {
      if (left_child->object < right_child->object)
      {
        swapping(node, left_child);
        Heapify(left_child);
      }
      else
      {
        swapping(node, right_child);
        Heapify(right_child);
      }
      return;
    }
    else
      return;
  }
}

template <typename T>
void Heap<T>::delMax()
{

  // insert your code here
  if (num_elements == 0)
    return;
  if (num_elements == 1)
  {
    root = nullptr;
    num_elements = 0;
    return;
  }

  TreeNode<T> *current = root;

  int *result = arr(num_elements);

  int i = 1;
  while (result[i] != 2)
  {
    if (result[i] == 1)
      current = current->right;
    else
      current = current->left;
    i++;
  }

  swapping(current, root);
  bool check_left = false;
  if (current->parent->left == current)
    check_left = true;
  if (!check_left)
  {
    current->parent->right = nullptr;
  }
  else
    current->parent->left = nullptr;
  delete (current);

  num_elements -= 1;
  Heapify(root);
  return;
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

  // insert your code here
  printTree("", node, false);
}

template <typename T>
void printTree(const string &prefix, TreeNode<T> *root, bool check_left = false)
{
  if (root != nullptr)
  {
    cout << prefix;
    cout << (check_left ? "|--" : "|__");

    cout << root->object << endl;
    TreeNode<T> *current = root;
    root = root->left;
    // enter the next tree level - left and right branch
    printTree(prefix + (check_left ? "│   " : "    "), root, true);
    root = current->right;
    printTree(prefix + (check_left ? "│   " : "    "), root, false);
    root = current;
  }
}

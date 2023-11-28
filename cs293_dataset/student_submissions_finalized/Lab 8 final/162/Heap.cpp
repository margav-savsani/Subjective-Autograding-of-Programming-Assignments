#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::maintainHeap(TreeNode<T> *node)
{
  TreeNode<T> *ptr = node;
  while (ptr->parent != nullptr && ptr->parent->object < ptr->object)
  {
    T obj = ptr->parent->object;
    ptr->parent->object = ptr->object;
    ptr->object = obj;
    ptr = ptr->parent;
  }
}
template <typename T>
void Heap<T>::setLast(TreeNode<T> *node, int count)
{
 if (count == 1)
  {
    this->last = node;
    // cout << "end: " << node->object << endl;
    return;
  }
  if (count == 2)
  {
    this->last = node;
    // cout << "end: " << node->object << endl;
    return;
  }
  if (count % 2 == 0)
  {
    setLast(node->right, (count - 2) / 2);
  }
  else if (count % 2 == 1)
  {
    setLast(node->left, (count - 1) / 2);
  }
}
template <typename T>
void Heap<T>::insert(T obj)
{
  // insert your code here
  // Insert root;
  if (root == nullptr)
  {
    root = new TreeNode<T>(obj);
    last = root;
    end = root;
    count++;
    return;
  }
  else
  {
    if (last->left == nullptr)
    {
      last->left = new TreeNode<T>(obj, last);
      end = last->left;
      count++;
      maintainHeap(last->left);
      // return;
    }
    else
    {
      last->right = new TreeNode<T>(obj, last);
      count++;
      maintainHeap(last->right);
      TreeNode<T> *ptr = root;
      end = last->right;

      

      // return;
    }
    setLast(root,count);
    return;
  }
}

template <typename T>
void Heap<T>::setEnd(TreeNode<T> *ptr, int count)
{
  if (count == 0)
  {
    this->end = ptr;
    // cout << "end: " << ptr->object << endl;
    return;
  }
  if (count % 2 == 0)
  {
    setEnd(ptr->right, (count - 2) / 2);
  }
  else if (count % 2 == 1)
  {
    setEnd(ptr->left, (count - 1) / 2);
  }
}

template <typename T>
void Heap<T>::delMax()
{

  // insert your code here
  if (end == root)
  {
    delete root;
    root = nullptr;
    return;
  }

  TreeNode<T> *end = this->end;

  root->object = end->object;
  this->last = end->parent;
  // cout << end->object << endl;
  if (end->parent->left == end)
  {

    end->parent->left = nullptr;
  }
  else
  {
    end->parent->right = nullptr;
  }
  count--;

  setEnd(root, count - 1);

  TreeNode<T> *ptr = root;
  TreeNode<T> *left = root->left;
  TreeNode<T> *right = root->right;
  while ((left != nullptr || right != nullptr))
  {
    if (left != nullptr && right != nullptr)
    {

      if (!(ptr->object < left->object) && !(ptr->object < right->object))
      {
        return;
      }
      T obj = ptr->object;
      TreeNode<T> *node = right->object < left->object ? left : right;
      ptr->object = node->object;
      node->object = obj;
      ptr = node;
    }
    else if (left != nullptr)
    {

      if (!( ptr->object < left->object ))
      {
        return;
      }
      T obj = ptr->object;
      ptr->object = left->object;
      left->object = obj;
      ptr = left;

      
    }
    else if (right != nullptr)
    {

      if (!( ptr->object < right->object))
      {
        return;
      }
      T obj = ptr->object;
      ptr->object = right->object;
      right->object = obj;
      ptr = right;
    }
    left = ptr->left;
    right = ptr->right;
  }

  return;
}

template <typename T>
int Heap<T>::height(TreeNode<T> *node)
{
  if (node == nullptr)
    return 0;
  int lheight = height(node->left);
  int rheight = height(node->right);
  int h = 1 + max(lheight, rheight);
  return h;
}


template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{ 
  static string prefix ="";
  bool isLeft = false;
  if(node!= nullptr)
  {     
        if(node != root && node->parent->left == node)
        {
          isLeft = true;
        }
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << node->object << endl;

        // enter the next tree level - left and right branch
        string temp = prefix;
        prefix = prefix + (isLeft ? "│   " : "    ");
        printBST(node->left);
        prefix = temp;
        prefix = prefix + (isLeft ? "│   " : "    ");
        printBST(node->right);
  }
  
}

// void BST::printBST(const string &prefix, bool isLeft = false)
// {
//     if (root != nullptr)
//     {
//         cout << prefix;

//         cout << (isLeft ? "|--" : "|__");

//         // print the value of the node
//         cout << root->JourneyCode << endl;

//         root = root->left;
//         // enter the next tree level - left and right branch
//         printBST(prefix + (isLeft ? "│   " : "    "), true);
//         root = curr->right;
//         printBST(prefix + (isLeft ? "│   " : "    "), false);
//         root = curr;
//     }
// }

  

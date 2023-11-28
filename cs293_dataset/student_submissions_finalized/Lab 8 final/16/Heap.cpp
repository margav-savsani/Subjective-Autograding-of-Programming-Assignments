#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

#include <cmath>
#include <math.h>
#include <string>

// Function to insert node in the hash
template <typename T>
void Heap<T>::insert(T obj)
{
  // Firstly I calculate the height upto which my tree is completely full
  // Will store that in the height variable, height starts from 1 for root
  int height = int(log2(num_nodes + 1));

  // Remainder denotes the position of the element that is to be added
  // in the last level.
  int remainder = (num_nodes + 1) - (round(pow(2, height)) - 1);

  // This directions variable stores a pattern of string of 1's and 0's
  // where 1 denote we need to go right of parent and 0 denotes we need to
  // go to the right of the parent
  string directions = "";

  // The node that is to be inserted in the heap
  TreeNode<T> *temp = new TreeNode<T>(obj);

  // Variable pointer that will find the parent under whom I need to perform
  // the addition of the node
  TreeNode<T> *iter = root;

  // The loop which based on mathematical calculation builds up my string
  // that will guide me which direction I should take to reach the parent
  // The maths being a node is on parent's left if its remainder with 2 is 1
  // and on parent's right if the remainder is 0.

  // After finding left or right, I simply update the remainder by remainder / 2 +
  // remainder % 2, this can be seen easily from pics depicting the hash tree.
  for (int i = 0; i < height; i++)
  {
    if (remainder == 1)
    {
      directions = to_string(remainder % 2) + directions;
    }
    else
    {
      directions = to_string(remainder % 2) + directions;
      remainder = (remainder / 2) + (remainder % 2);
    }
  }

  // Base case if root is null
  if (iter == nullptr)
  {
    // ADD the node at root and increase the count of nodes
    root = temp;
    num_nodes++;
    return;
  }
  else
  {
    // Using the above generated string of directions take the pointer to the parent
    for (int i = 0; i < height - 1; i++)
    {
      if (directions[i] == '1')
      {
        iter = iter->left;
      }
      else
      {
        iter = iter->right;
      }
    }
    // Now using the last character of the string check where the insertion is to be done
    // left or right and then simply add at that place and increase the count
    if (directions[height - 1] == '1')
    {
      iter->left = temp;
      temp->parent = iter;
    }
    else
    {
      iter->right = temp;
      temp->parent = iter;
    }
    num_nodes++;
  }

  // Need to kind of HEAPIFY the stuff (Not in literal terms)
  // Simply re-traverse the tree and exchange the parent and the child
  // if parent is less than the child as we are implementing the max-heap
  while (iter != nullptr)
  {
    if (iter->object < temp->object)
    {
      T inter = iter->object;
      iter->object = temp->object;
      temp->object = inter;
      temp = iter;
      iter = iter->parent;
    }
    // The first instance where we find that parent is greater than the child, we can
    // stop the traversal as all other nodes would necessarily be greater than the parent
    // as they already were in the heap and satisfy the property of the heap
    else
    {
      return;
    }
  }
  return;
}

// Implementing the delete max function
template <typename T>
void Heap<T>::delMax()
{
  // Only procees to deletion if we know there exists atleast 1 element in
  // the heap
  if (num_nodes > 0)
  {
    // following the same steps as in the insert to reach the parent whose child will be deleted
    int height = int(log2(num_nodes));
    int remainder = (num_nodes) - (round(pow(2, height)) - 1);
    string directions = "";
    TreeNode<T> *iter = root;
    for (int i = 0; i < height; i++)
    {
      if (remainder == 1)
      {
        directions = to_string(1) + directions;
      }
      else
      {
        directions = to_string(remainder % 2) + directions;
        remainder = (remainder / 2) + (remainder % 2);
      }
    }
    for (int i = 0; i < height - 1; i++)
    {
      if (directions[i] == '1')
      {
        iter = iter->left;
      }
      else
      {
        iter = iter->right;
      }
    }
    // Now here we know that iter is the parent as explained already in the
    // insert function

    // checking the case if the element to be deleted is root or not
    // if not then proceed inside the if loop and delete the
    // corresponding element to be deleted using the string storing the direction
    if (height - 1 >= 0)
    {
      if (directions[height - 1] == '1')
      {
        root->object = iter->left->object;
        delete iter->left;
        iter->left = nullptr;
      }
      else
      {
        root->object = iter->right->object;
        delete iter->right;
        iter->right = nullptr;
      }
      num_nodes--;

      // Note here we have the parent whose child was deleted
      // But do we need it? No, right. As heapify starts from the root

      // Lets do heapify now from the root, below is the iterative version
      // of the heapify
      TreeNode<T> *deleter = root;
      // Base case will be both child as nullptr, that is pointer is root
      while (deleter->right != nullptr && deleter->left != nullptr)
      {
        // If right child is not there, simply compare with the left
        if (deleter->right == nullptr)
        {
          // comparing the values
          if (deleter->object < deleter->left->object)
          {
            T temp = deleter->object;
            deleter->object = deleter->left->object;
            deleter->left->object = temp;
            deleter = deleter->left;
          }
          // In any position if parent is greater than both the child simply
          // stop the heapify
          else
          {
            return;
          }
        }
        // Same as above case only replace left with right
        if (deleter->left == nullptr)
        {
          if (deleter->object < deleter->right->object)
          {
            T temp = deleter->object;
            deleter->object = deleter->right->object;
            deleter->right->object = temp;
            deleter = deleter->right;
          }
          else
          {
            return;
          }
        }
        // If both child's exist
        else
        {
          // If left is greater than the right, check for inequality between parent and the left child
          if (deleter->right->object < deleter->left->object)
          {
            // if left is bigger, swap parent and the left child, else end heapify
            if (deleter->left->object < deleter->object)
            {
              return;
            }
            // left bigger condition is satisified here
            else
            {
              T temp = deleter->object;
              deleter->object = deleter->left->object;
              deleter->left->object = temp;
              deleter = deleter->left;
            }
          }
          // If left is smaller or equal than the right, check for inequality between parent and the right child
          else
          {
            // if right is bigger, swap parent and the right child, else end heapify
            if (deleter->right->object < deleter->object)
            {
              return;
            }
            // right bigger condition is satisified here
            else
            {
              T temp = deleter->object;
              deleter->object = deleter->right->object;
              deleter->right->object = temp;
              deleter = deleter->right;
            }
          }
        }
      }
    }
    // If root is to be deleted, simply set root to nullptr as tree is now empty
    else
    {
      delete root;
      root = nullptr;
      num_nodes--;
      return;
    }
  }
  return;
}

// Helper function to assist printing of the heap tree,
// this follows exactly the function we saw in all the previous
// labs for printing the BST and heap here is also as Binary tree.
template <typename T>
void Heap<T>::printHeapHelper(const string &prefix, bool isLeft)
{
  if (root != nullptr)
  {
    cout << prefix;
    cout << (isLeft ? "|--" : "|__");
    // print the value of the node
    cout << root->object << endl;
    TreeNode<T> *curr = root;
    root = root->left;

    // enter the next tree level - left and right branch
    printHeapHelper(prefix + (isLeft ? "│   " : "    "), true);
    root = curr->right;
    printHeapHelper(prefix + (isLeft ? "│   " : "    "), false);
    root = curr;
  }
}

// Function to print the heap tree
template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{
  // storing the root here as I change the root itself in the helper function
  TreeNode<T> *curr = root;
  root = node;

  // Calling the helper function to print the tree
  printHeapHelper("", false);
  root = curr;
  return;
}
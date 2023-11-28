#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST
int BST::Height(TreeNode *head)
{
  if (head == NULL)
    return -1;
  if (head->left == NULL && head->right == NULL)
    return 0;
  int left_height = Height(head->left);

  int right_height = Height(head->right);

  if (head->left != NULL)
    head->left->height = left_height;
  if (head->right != NULL)
    head->right->height = right_height;
  if (left_height < right_height)
  {
    return 1 + right_height;
  }
  else
  {
    return 1 + left_height;
  }
}
bool BST::insert(int jrnyCode, int price)
{
  if (find(jrnyCode) == jrnyCode)
  {
    return false;
  }
  else
  {
    TreeNode *T = new TreeNode(jrnyCode, price);
    TreeNode *t = new TreeNode(0, 0);

    t = root;

    if (root == NULL)
    {

      root = new TreeNode(jrnyCode, price);
      root->height = 1;
      return true;
    }
    while (t != NULL)
    {
      if (BSTLessThan(t, T))
      {
        if (t->right == NULL)
        {
          updateBSTParentChild(T, t, false);
          t->right = T;

          T->parent = t;
          T->JourneyCode = jrnyCode;
          T->price = price;
          root->height = Height(root);
          return true;
        }
        else
        {
          t = t->right;
        }
      }
      else if (BSTLessThan(T, t))
      {
        if (t->left == NULL)
        {
          updateBSTParentChild(T, t, true);
          t->left = T;

          T->parent = t;
          T->JourneyCode = jrnyCode;
          T->price = price;
          root->height = Height(root);
          return true;
        }
        else
        {
          t = t->left;
        }
      }
    }
  }

  return true;
}

// Implement insertion in BST

// You MUST use only BSTLessThan to compare two journey codes.  You
// can create a new node containing the journey code to be inserted
// and invoke BSTLessThan on the current node in the tree that you
// are inspecting and the new node to do your comparison.

// REMEMBER to update the heights of appropriate nodes in the tree
// after an insertion.

// We use "return true" below to enable compilation.  Change this as you
// see fit.

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST
 TreeNode *t = new TreeNode(0, 0);
  t->JourneyCode = jrnyCode;
  TreeNode *T = root;
  
  while (T != NULL)
  {
    if (T->JourneyCode == jrnyCode)
    {
      return jrnyCode;
    }
    else if (BSTLessThan(t, T))
    {
      T = T->left;
    }
    else if (BSTLessThan(T, t))
    {
      T = T->right;
    }
    
  }
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.

  return true;
}

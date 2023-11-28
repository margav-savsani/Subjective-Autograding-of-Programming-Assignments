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

bool BST::insert(int jrnyCode, int price)
{
  TreeNode *t = new TreeNode(jrnyCode, price);
  if (root == NULL)
  {
    root = t;
    return true; // adds at root if its null
  }
  TreeNode *temp = new TreeNode(jrnyCode, price);
  temp = root;
  while (temp != NULL)
  {
    if (BSTLessThan(t, temp)) // if less than root goes to left
    {

      if (temp->left == NULL)
      {
        t->updateParentChild(temp, true);
        return true;
      }
      else
      {
        temp = temp->left;
        temp->height++;
      }
    }
    else if (BSTLessThan(temp, t)) // if greater than root goes to right subtree
    {

      if (temp->right == NULL)
      {
        t->updateParentChild(temp, false);
        return true;
      }
      else
      {
        temp = temp->right;
        temp->height++;
      }
    }
    else
      return false;
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
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  TreeNode *temp = root;
  TreeNode *t = new TreeNode(jrnyCode, 0);
  while (temp != NULL)
  {
    if (BSTLessThan(t, temp))
    {
      temp = temp->left; // check in left tree if price is less than root's
    }
    else if (BSTLessThan(temp, t))
    {
      temp = temp->right; // check in right subtree if price is more than root's
    }
    else
      return temp->getprice();
  }

  // Implement find in BST

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

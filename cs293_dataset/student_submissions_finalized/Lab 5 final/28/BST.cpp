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
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  // As every journey code is unique ,there is no need to invoke the find function

  TreeNode *node = new TreeNode(jrnyCode, price);
  if (root == NULL)
  {
    root = node;
    return true;
  }
  TreeNode *curr = root;
  TreeNode *prev = NULL;
  while (curr != NULL)
  {
    // cout<<BSTLessThan(curr, node)<<endl;
    if (BSTLessThan(curr, node))
    {
      prev = curr;
      curr = curr->right;
      // curr->height++;
    }
    else
    {
      prev = curr;
      curr = curr->left;
      // curr->height++;
    }
  }
  if (BSTLessThan(prev, node))
  {
    prev->right = node;
    node->parent = prev;
  }
  else
  {
    prev->left = node;
    node->parent = prev;
  }
  curr = node;
  TreeNode *above = node->parent;
  while (curr != root)             //updating the height
  {
    above->height = above->longpath();
    curr = above;
    above = above->parent;
  }

  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.

  if (root == NULL)
    return false;
  TreeNode *x = root;
  TreeNode *y = new TreeNode(jrnyCode, 1);
  while ((x != NULL) && (BSTLessThan(x, y) || BSTLessThan(y, x)))
  {
    if (BSTLessThan(y, x))
      x = x->left;
    else
      x = x->right;
  }
  if (x != NULL)
    return 1;

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

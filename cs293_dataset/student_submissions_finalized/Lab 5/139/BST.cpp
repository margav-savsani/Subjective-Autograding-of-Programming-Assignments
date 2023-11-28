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
  TreeNode *y = nullptr;
  TreeNode *x = this->root;
  TreeNode *temp = new TreeNode(jrnyCode, price);
  // traversing through the tree (x as the place about to be inserted, y as parent of the x).
  while (x != nullptr)
  {
    y = x;
    if (x == temp)
    {
      return false;
    }
    if (x > temp)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  // constructing new element:
  TreeNode *about_to_insert = new TreeNode(jrnyCode, price);
  about_to_insert->parent = y;
  // first element to be added(root even not defined, we have to insert root).
  if (y == nullptr)
  {
    this->root = about_to_insert;
  }
  // else,adding new element depending upon parent node
  else if (!(about_to_insert > y))
  {
    y->left = about_to_insert;
  }
  else if (about_to_insert > y)
  {
    y->right = about_to_insert;
  }
  return true;
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
  TreeNode *node = this->root;
  TreeNode *temp = new TreeNode(jrnyCode,0);
  //dummy node for comapision
  // traversing through the tree
  while (node != nullptr)
  {
    if (node == temp)
      return node->height;
    else
    {
      if (temp > node)
        node = node->left;
      else
        node = node->right;
    }
  }
  return -1;
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
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

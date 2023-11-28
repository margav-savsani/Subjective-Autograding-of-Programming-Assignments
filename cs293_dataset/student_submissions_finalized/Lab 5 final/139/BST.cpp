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
  // constructing a dummy node with given journey code and price
  TreeNode *temp = new TreeNode(jrnyCode, price);
  // traversing through the tree (x as the place about to be inserted, y as parent of the x).
  while (x != nullptr)
  {
    y = x;
    // if both are equal
    if (!BSTLessThan(x, temp) && !BSTLessThan(temp, x))
    {
      return false;
    }
    if (BSTLessThan(temp, x))
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
    return true;
  }
  // else,adding new element depending upon parent node
  updateBSTParentChild(about_to_insert, y, !(BSTLessThan(y, about_to_insert)));
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  TreeNode *node = this->root;
  // dummy node for comparision
  TreeNode *temp = new TreeNode(jrnyCode, 0);
  //  traversing through the tree:
  while (node != nullptr)
  {
    // if both are equal, then returning a positive value.
    if (!BSTLessThan(node, temp) && !BSTLessThan(temp, node))
      return 1;
    else
    {
      if (BSTLessThan(node, temp))
        node = node->left;
      else
        node = node->right;
    }
  }
  // if not found, returning negative value(-1).
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
}
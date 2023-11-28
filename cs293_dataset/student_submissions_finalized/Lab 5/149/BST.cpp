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

bool addNode(TreeNode *t, int code, int price)
{
  TreeNode *y;
  y = new TreeNode(code, price);
  if (t->JourneyCode == 0)
  {
    t->price = price;
    t->JourneyCode = code;
    return true;
  }
  else if (BSTLessThan)
  {
    if (t->left == nullptr)
    {
      t->left = new TreeNode();
      t->left->parent = t;
      t->left->price = price;
      t->left->JourneyCode = code;
      return true;
    }
    else
    {
      return addNode(t->left, code, price);
    }
  }
  else if (t->JourneyCode < code)
  {
    if (t->right == nullptr)
    {
      t->right = new TreeNode();
      t->right->parent = t;
      t->right->price = price;
      t->right->JourneyCode = code;
      return true;
    }
    else
    {
      return addNode(t->right, code, price);
    }
  }
}

bool BST::insert(int JourneyCode, int price)
{
  if (root == nullptr)
  {
    root = new TreeNode(JourneyCode, price);
    root->parent = nullptr;
    return true;
  }
  else
    return addNode(root, JourneyCode, price);
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

TreeNode *findNode(TreeNode *t, int code, int price)
{
    if (t == nullptr)
    {
        return t;
    }
    else if (t->price == price && t->JourneyCode == code)
    {
        return t;
    }
    else if (t->JourneyCode > code)
    {
        return findNode(t->left, code, price);
    }
    else
    {
        return findNode(t->right, code, price);
    }
}

int BST::find(int JourneyCode, int price)
{
  TreeNode *t = findNode(root, JourneyCode, price);
  if (t == nullptr)
    // cout << "3546" << endl;
    return false;
  else
    return true;
  // You can look at the implementation of insert to code this part up.

  return false;
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

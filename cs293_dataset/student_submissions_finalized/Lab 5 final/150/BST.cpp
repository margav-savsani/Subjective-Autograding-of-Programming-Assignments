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
  // Checking for the case when root is null no imbalance possible 
  // updating roots parent to nullptr,
  if (root == nullptr)
  {
    root = new TreeNode(jrnyCode, price);
    root->parent = nullptr;
    root->height = 0;
    return true;
  }
  // making the node a to insert and assisgning x and y as pointer to travel down the tree 
  //to find the position of insertion
  // when x will point to nullptr y will be the parent of newly assigned node
  TreeNode *a = new TreeNode(jrnyCode, price);
  TreeNode *x = root;
  TreeNode *y = nullptr;
  // travelling down the tree as per the rule of BST while comparing with the BSTLessThan FUNCTION.
  // IF THERE is already a node with same jrncycode it returns false.
  // This will also be increasing the comparison cost.
  while (x != nullptr)
  {
    if (BSTLessThan(x, a))
    {
      y = x;
      x = x->right;
    }
    else if (BSTLessThan(a, x))
    {
      y = x;
      x = x->left;
    }

    else
    {
      return false;
    }
  }
   // the loop will be exited after finding position to insert now making a as 
  //left or right child of y again just by comparing it with the value of y. 
  if (BSTLessThan(a, y))
  {
    updateBSTParentChild(a, y, true);
  }
  else
  {
    updateBSTParentChild(a, y, false);
  }
  // updating the height of all pointers while moving up till the root from 
  //the newly inserted node a all up the way to root.
  a->height = 0;
  while (y != nullptr)
  {
    if (y->left == nullptr)
    {
      y->height = 1 + y->right->height;
      y = y->parent;
    }
    else if (y->right == nullptr)
    {
      y->height = 1 + y->left->height;
      y = y->parent;
    }
    else
    {
      y->height = 1 + max(y->left->height, y->right->height);
      y = y->parent;
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
  // FIND is simply a BST tree walk 
  // just checking the suitable jrncycode acc. to
  // rule of bst by AVLLessThan function.
  // use !(a>x) && !(a<x) => a=x
  TreeNode *a = new TreeNode(jrnyCode, 0);
  TreeNode *x = root;
  while (x != nullptr)
  {
    if (BSTLessThan(x, a))
    {
      x = x->right;
    }
    else if (BSTLessThan(a, x))
    {
      x = x->left;
    }
    else
    {
      return true;
    }
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

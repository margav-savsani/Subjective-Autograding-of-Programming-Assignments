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

  // if the root is null, create a new node and return it
  TreeNode*x=root
    if (x == nullptr)
    {
      return newnode(key);
    }

    // if the given key is less than the root node, recur for the left subtree
    if (key < root->data)
    {
      root->left = insert(root->left, key);
    }
    // if the given key is more than the root node, recur for the right subtree
    else
    {
      root->right = insert(root->right, key);
    }

    return root;
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
    TreeNode *x = root;
    if (x = NULL)
    {
      return NULL;
    }
    if ( p== x->JourneyCode)
    {
      return x;
    }
    if k
      < key[x] then return Search(left[x], k) else return Search(right[x], k) return -1;
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
  }

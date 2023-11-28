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

  TreeNode *temp = new TreeNode(jrnyCode, price); // TreeNode for the pair to be inserted is made.
  if (root == nullptr)
  {
    root = temp; // Special Case of root being nullptr is handled.
    return true;
  }
  TreeNode *test = root;      // Node being tested for insertion
  TreeNode *parent = nullptr; // Parent of the test node is maintained for insertion
  while (test != nullptr)     // When test becomes null, temp can be inserted at that node.
  {
    if (BSTLessThan(temp, test)) // in this case, we need to insert in left of test
    {
      parent = test;
      test = test->left;
    }
    else // in this case we need to insert in right of test
    {
      parent = test;
      test = test->right;
    }
  }
  updateBSTParentChild(temp, parent, BSTLessThan(temp, parent)); // temp is insert as child of parent, at left or right depeneding on which one is less
  int h = 1; // height
  while (parent != root) // We need to update height of nodes in the path from the last parent to root only
  {
    if (h > parent->height) // If the height of last node inserted is more than current height, height is updated
      parent->height = h++;
    parent = parent->parent;
  }
  if (h > parent->height) // height of root is updated
    parent->height = h;

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
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.
  TreeNode *temp = new TreeNode(jrnyCode, 0); // The journeycode to be find is made into TreeNode
  TreeNode *test = root; // test node to traverse through tree.
  while (test != nullptr) // If test becomes null, code not present
  {
    if (BSTLessThan(temp, test))
    {
      test = test->left; // If temp < test, we check in left of test
    }
    else if (!BSTLessThan(test, temp))
    {
      return test->printPrice(); // this case would mean test = temp as neither is less than the other, so node found
    }
    else
    {
      test = test->right; // this case is when temp > test, we check in right of test 
    }
  }

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

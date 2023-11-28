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
  TreeNode *t = new TreeNode(jrnyCode, price); // node to be inserted
  if (root == NULL)
  {
    root = t;
    return true; // adds at root if its null
  }
  BST *T1 = new BST(root->left, perComparisonCost, perParentChildUpdateCost);  // new left sub tree
  BST *T2 = new BST(root->right, perComparisonCost, perParentChildUpdateCost); // new right subtree

  if (BSTLessThan(t, root)) // if it belongs to left subtree
  {
    if (!T1->insert(jrnyCode, price)) // if it doesnt insert
    {
      return false;
    }
    totalComparisonCost += T1->getComparisonCost();               // adding comparison cost
    totalParentChildUpdateCost += T1->getParentChildUpdateCost(); // adding parentchild update cost
    updateBSTParentChild(T1->root, root, true);                   // updating the left child into tree
  }
  else if (BSTLessThan(root, t)) // if it belongs to right subtree
  {
    if (!T2->insert(jrnyCode, price)) // if it doesnt insert
    {
      return false;
    }
    totalComparisonCost += T2->getComparisonCost();               // adding comparison cost
    totalParentChildUpdateCost += T2->getParentChildUpdateCost(); // adding parentchild update cost
    updateBSTParentChild(T2->root, root, false);                  // updating the right child into tree
  }
  else
    return false;

  if (root->right != NULL && root->left != NULL) // if both childs are present
  {
    root->height = 1 + max(root->right->height, root->left->height); // maximum of height
  }
  else if (root->right != NULL) // if only right child exists
  {
    root->height = 1 + root->right->height; // updating the height
  }
  else if (root->left != NULL) // if only left child exists
  {
    root->height = 1 + root->left->height; // updating the height
  }
  else
    root->height = 0; // if no child height to 0
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
  while (temp != NULL) // if it doesnt exist
  {
    if (BSTLessThan(t, temp)) // checks if its in left subtree
    {
      temp = temp->left; // check in left tree if price is less than root's
    }
    else if (BSTLessThan(temp, t)) // checks if its in right subtree
    {
      temp = temp->right; // check in right subtree if price is more than root's
    }
    else
      return temp->getprice(); // returns price
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

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
  TreeNode *comparisonnode = new TreeNode(jrnyCode, price);
  TreeNode *currNode = root;
  TreeNode *parentOfCurrNode = nullptr;
  if (root == NULL)
  {
    root = new TreeNode(jrnyCode, price);
    return true;
  }
  while (currNode != nullptr)
  {
    if (this->BSTLessThan(currNode, comparisonnode))
    {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (this->BSTLessThan(comparisonnode,currNode))
    {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else
    {
      return false;
    }
  }
  if (this->BSTLessThan(comparisonnode,parentOfCurrNode))
  {
    // (parentOfCurrNode->right != NULL){
    //   parentOfCurrNode.
    // }
    // else{

    // }
    currNode = new TreeNode(jrnyCode, price);
    currNode->left = NULL;
    currNode->right = NULL;
    currNode->updateParentChild(parentOfCurrNode, true);
      // parentOfCurrNode->left = currNode;
  }
  else
  {
    currNode = new TreeNode(jrnyCode, price);
    currNode->left = NULL;
    currNode->right = NULL;
    currNode->updateParentChild(parentOfCurrNode, false);
    // parentOfCurrNode->right = currNode;
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
  delete (comparisonnode);
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
  TreeNode* comparisonnode = new TreeNode(jrnyCode, 0);
  TreeNode *x = root; // STARTING FROM ROOT NODE
  while (x != NULL && ((this->BSTLessThan(x,comparisonnode) || this->BSTLessThan(comparisonnode, x))))
  {
    // SEARCH TILL THE EXACT STATION IS FOUND
    // OR WE REACH A NULL.
    if (this->BSTLessThan(comparisonnode,x))
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  if (x == NULL)
  { // IF NO SUCH NODE
    return -1;
  }
  else
  {
    return 1;
  }
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

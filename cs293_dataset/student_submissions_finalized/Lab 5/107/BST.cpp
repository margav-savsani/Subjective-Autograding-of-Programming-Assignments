#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


void BST::updateheight(TreeNode *parentOfCurrNode)
{
  while (parentOfCurrNode!=nullptr)
  {
    // moving up to root... updating shortestPathLength and longestPathLength
    if(parentOfCurrNode->left==nullptr)
    {
      // only right child is present
      parentOfCurrNode->height=((parentOfCurrNode->right)->height) + 1;
    }
    else if(parentOfCurrNode->right==nullptr)
    {
      // only left child is present
      parentOfCurrNode->height=((parentOfCurrNode->left)->height) + 1;
    }
    else
    {
      // both left and right children are present
      parentOfCurrNode->height=max((parentOfCurrNode->left)->height, (parentOfCurrNode->right)->height) + 1;
    }
    parentOfCurrNode=parentOfCurrNode->parent;  // move control up the tree
  }
}


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



  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  TreeNode *toinsert = new TreeNode(JourneyCode, price);

  if(root==nullptr)
  {
    // no root present
    root= toinsert;
    root->height=0;
    return true;
  }

  while (currNode != nullptr) {
    if (BSTLessThan(currNode, toinsert)) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (BSTLessThan(toinsert, currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }
  if(BSTLessThan(toinsert, parentOfCurrNode))
  {
    // left insert
    parentOfCurrNode->left= new TreeNode(JourneyCode, price, nullptr, nullptr, parentOfCurrNode);
    (parentOfCurrNode->left)->height=0;
  }
  else
  {
    // right insert
    parentOfCurrNode->right= new TreeNode(JourneyCode, price, nullptr, nullptr, parentOfCurrNode);
    (parentOfCurrNode->right)->height=0;
  }
  updateheight(parentOfCurrNode);  // Update height up the tree
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

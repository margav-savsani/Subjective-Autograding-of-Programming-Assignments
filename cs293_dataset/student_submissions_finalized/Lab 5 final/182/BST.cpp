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
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  struct TreeNode *n;
  n=new TreeNode(jrnyCode,price);
  
  while (currNode != nullptr) {
   // if (currNode->getJourneyCode() < jrnyCode)
   if(BSTLessThan(currNode,n)) {
      parentOfCurrNode = currNode;
      if(currNode->right->getJourneyCode()!=jrnyCode)currNode->height=max(longestpath(currNode->right)+2,longestpath(currNode->left)+1);
      else return false;
      currNode = currNode->right;
      
    }
    else if (BSTLessThan(n,currNode)) {
      parentOfCurrNode = currNode;
      if(currNode->left->getJourneyCode()!=jrnyCode)currNode->height=max(longestpath(currNode->left)+2,longestpath(currNode->right)+1);
      else return false;
      currNode = currNode->left;
    }
  }
  // jrnyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  if(BSTLessThan(n,parentOfCurrNode))
    {
        updateBSTParentChild(n,parentOfCurrNode,false);
        return true;
    }
  if(BSTLessThan(parentOfCurrNode,n))
    {
        updateBSTParentChild(n,parentOfCurrNode,true);
        return true;
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
  struct TreeNode *currNode = root;
  struct TreeNode *n;
  int price=0;
  n=new TreeNode(jrnyCode,price);
  
  while (currNode != nullptr) {
   // if (currNode->getJourneyCode() < jrnyCode)
   if(BSTLessThan(currNode,n)) {
      currNode = currNode->right;
    }
    else if (BSTLessThan(n,currNode)) {
      currNode = currNode->left;
    }
    else { return currNode->getJourneyCode();
    }
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



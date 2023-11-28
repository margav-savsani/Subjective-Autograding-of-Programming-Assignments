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

  TreeNode *temp = new TreeNode(jrnyCode, price);
  TreeNode *r = root;
  TreeNode *p;
  if (r == NULL)
  {
    root = temp;
    return true;
  }
  while (r != NULL)
  {
    p=r;
    if (BSTLessThan(r,temp))
    {
      r = r->right;
    }
    else if(BSTLessThan(temp,r))
    {
      r = r->left;
    }
    else{
      return false;
    }
    
  }
  if (BSTLessThan(p, temp))
  {
    p->right = temp;
  }
  else
  {
    p->left = temp;
  }
  updateBSTParentChild(temp,p,BSTLessThan(temp,p));

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
  int price;
  TreeNode *temp = new TreeNode(jrnyCode, price);
  TreeNode *r = root;
  // Implement find in BST
  if (r == NULL)
  {
    return -1;
  }
  while(r != NULL)
  {
  if (BSTLessThan(temp, r))
  {
    r = r->left;
  }
  else if(BSTLessThan(r,temp))
  {
     r = r->right;
  }
  else if(!BSTLessThan(temp,r) && !BSTLessThan(r,temp))
  {
   return r->x();
  }
  else{
    return -1;
  }
  }

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

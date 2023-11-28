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
  if (root == nullptr)
  {
    root = new TreeNode(jrnyCode, price);
    return true;
  }
  TreeNode *ptr = new TreeNode(jrnyCode, price);
  if (BSTLessThan(ptr, root))
  {
     if(root->left == nullptr) //When left child of root is Null, then we inserted one.
    {
      TreeNode *newNode = new TreeNode(jrnyCode, price);
      updateBSTParentChild(newNode, root, true);
      if(root->right == nullptr)
      {
        root->height = root->left->height + 1;
      }
      else{
        root->height = max(root->right->height, root->left->height) + 1;
      }
      return true;
    }
    else
    {
      TreeNode * temp = root;
      root = root->left;
      bool sol = BST::insert(jrnyCode, price);
      root = temp;
      if(root->right == nullptr)
      {
        root->height = root->left->height + 1;
      }
      else{
        root->height = max(root->right->height, root->left->height) + 1;
      }
      return sol;
    }
  }
  else if(BSTLessThan(root, ptr))
  {
    if(root->right == nullptr)//When right child of root is Null, then we inserted one.
    {
      TreeNode *newNode = new TreeNode(jrnyCode, price);
      updateBSTParentChild(newNode, root, false);
      if(root->left == nullptr)
      {
        root->height = root->right->height + 1;
      }
      else{
        root->height = max(root->right->height, root->left->height) + 1;
      }
      return true;
    }
    else
    {
      TreeNode * temp = root;
      root = root->right;
      bool sol = BST::insert(jrnyCode, price);
      root = temp;
      if(root->left == nullptr)
      {
        root->height = root->right->height + 1;
      }
      else{
        root->height = max(root->right->height, root->left->height) + 1;
      }
      return sol;
    }
  }
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  TreeNode * temp = root;
  TreeNode * ptr = new TreeNode(jrnyCode, 0);
  if(root == nullptr)
  {
    return -1;
  }
  if(BSTLessThan(ptr, root))
  {
    if(root->left == nullptr)
    {
      return -1;
    }
    BST * leftTree = new BST(root->left, perComparisonCost, perParentChildUpdateCost);
    leftTree->find(jrnyCode);
  }
  else if(BSTLessThan(root, ptr))
  {
    if(root->right == nullptr)
    {
      return -1;
    }
    BST * rightTree = new BST(root->right, perComparisonCost, perParentChildUpdateCost);
    rightTree->find(jrnyCode);
  }
  else 
  {
    return root->getPrice();
  }
  // Implement find in BST
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



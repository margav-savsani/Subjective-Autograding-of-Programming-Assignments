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
  // I used FIND in insert because I used BREAK statements in between . Time complexity of find O(h).
  if (find(jrnyCode) != -1) 
  {
    return false;
  }
  TreeNode *temp = new TreeNode(jrnyCode, price);
  TreeNode *t = new TreeNode();
  t = root;
  if (root == NULL)
  {
    root = temp;
    return true;
  }
  else
  {
    while (t != NULL)
    {
      if (BSTLessThan(t, temp))
      {
        if (t->right == NULL)
        {
          updateBSTParentChild(temp, t, false);
          t->right->left = NULL;
          t->right->right = NULL;
          break;
        }
        t = t->right;
      }
      else
      {
        if (t->left == NULL)
        {
          updateBSTParentChild(temp, t, true);
          break;
        }

        t = t->left;
      }
    }
  }
  updateHeigts(temp);// Update Heights.
  return true;
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
}

// According to question I cannot change the arguments passed in INSERT function.
// So I cannot change heights while inserting.
// So I created a new function which travels the path reverse of insertion :)
// It's worst case time is O(h). 
void BST::updateHeigts(TreeNode *temp)
{
  // Condition for root
  if (temp == root)
  {
    if ((root->left == NULL) && (root->right == NULL))
    {
      temp->height = 0;
    }
    else if (root->left == NULL)
    {
      root->height = 1 + root->right->height;
    }
    else if (root->right == NULL)
    {
      root->height = 1 + root->left->height;
    }
    else
    {
      root->height = 1 + max(root->left->height, root->right->height);
    }
  }
  // If temp is not root and it is internode or a leaf.
  else
  {
    if ((temp->left == NULL) && (temp->right == NULL))
    {
      temp->height = 0;
    }
    else if (temp->left == NULL)
    {
      temp->height = 1 + temp->right->height;
    }
    else if (temp->right == NULL)
    {
      temp->height = 1 + temp->left->height;
    }
    else
    {
      temp->height = 1 + max(temp->left->height, temp->right->height);
    }
    updateHeigts(temp->parent);
  }
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  TreeNode *Tosearch = new TreeNode(jrnyCode, -200);
  TreeNode *temp = new TreeNode();
  temp = root;
  while (temp != NULL)
  {
    if (temp->getJourneyCode() == Tosearch->getJourneyCode())
    {
      return temp->getPrice();
    }
    else if (BSTLessThan(temp, Tosearch))
    {
      temp = temp->right;
    }
    else if (BSTLessThan(Tosearch ,temp)){
      temp = temp->left;
    }
    else break;
  }
  return -1;
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

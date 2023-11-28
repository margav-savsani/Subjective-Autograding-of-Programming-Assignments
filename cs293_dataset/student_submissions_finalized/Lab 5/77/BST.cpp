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
  if (find(jrnyCode) == -1)
  {
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
        if (t->getJourneyCode() == temp->getJourneyCode())
        {
          return false;
        }
        
        else if (t < temp)
        {
          /// DEBUGGING 
          cout<<t->getJourneyCode()<<" "<<temp->getJourneyCode()<<endl;
          cout<<"in"<<endl;
          if (t->right == NULL)
          {
            t->height++;
            t->right = temp;
            t->right->left = NULL;
            t->right->right = NULL;
            return (true);
          }
          t = t->right;
        }
        else
        {
          cout<<"out"<<endl;
          if (t->left == NULL)
          {
            t->height++;
            t->left = temp;
            t->left->left = NULL;
            t->left->right = NULL;
            return (true);
          }
          
          t = t->left;
        }
      }
    }
  }
    return false;

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
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
    else if (temp < Tosearch)
    {
      temp = temp->right;
    }
    else
      temp = temp->left;
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

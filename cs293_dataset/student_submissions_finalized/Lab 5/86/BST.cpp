#ifndef BST_H
#include "BST.h"
#endif
 
#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

TreeNode *BST::search(TreeNode *T, int JourneyCode)
{
    if (T == NULL)
    {
        return NULL;
    }
    TreeNode temp1(JourneyCode,0),temp2(T->JourneyCode);
    if (T->JourneyCode == JourneyCode)
        return T;
    if (temp2 < temp1)
    {
        return search(T->right, JourneyCode);
    }
    else
        return search(T->left, JourneyCode);
}

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int JourneyCode, int price)
{
  if (search(root, JourneyCode) != NULL)
    {
        return false;
    } 
    else
    {
        TreeNode *newnode = new TreeNode;
        newnode->JourneyCode = JourneyCode;
        newnode->price = price;
        newnode->parent = NULL;
        newnode->left = NULL;
        newnode->right = NULL;
        if (root == NULL)
        {
            root = new TreeNode;
            root->parent = NULL;
            root->JourneyCode = JourneyCode;
            root->price = price;
            return true;
        }
        TreeNode *T = root;
        TreeNode *temp = new TreeNode;
        int left_h,right_h;
        while (T != NULL)
        {
            temp = T;
            if (JourneyCode < T->JourneyCode)
                T = T->left;
            else
                T = T->right;
        }
        if (JourneyCode < temp->JourneyCode)
        {
            temp->left = newnode;
            newnode->parent = temp;
            return true;
        }
        else
        {
            temp->right = newnode;
            newnode->parent = temp;
            return true;
        }
    }
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



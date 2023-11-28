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
  TreeNode *i = new TreeNode(jrnyCode,price);
  if(root == NULL)    //initialising root
  {
    root = new TreeNode(jrnyCode,price);
    return true;
  }
  else if(BSTLessThan(i,root))    //inserting in the left subtree if the value of the new node is  less than the value of the root
  {
    if(root->left == NULL)    //creating a new left child if it doesn't exist
    {
      updateBSTParentChild(i,root,true);
      if(root->right != NULL)
      {
        root->height = 1 + max(root->left->height,root->right->height);
      }
      else
      {
        root->height = 1 + root->left->height;
      }
      return true;
    }
    else    //moving to the left child
    {
      root = root->left;
      bool ins = insert(jrnyCode,price);
      root = root->parent;
      if(root->right != NULL)
      {
        root->height = 1 + max(root->left->height,root->right->height);
      }
      else
      {
        root->height = 1 + root->left->height;
      }
      return ins;
    }
  }
  else if(BSTLessThan(root,i))    //inserting in the right subtree if the value of the new node is more than the value of the root
  {
    if(root->right == NULL)   //creating a new right child if it doesn't exist
    {
      updateBSTParentChild(i,root,false);
      if(root->left != NULL)
      {
        root->height = 1 + max(root->left->height,root->right->height);
      }
      else
      {
        root->height = 1 + root->right->height;
      }
      return true;
    }
    else    //moving to the right child
    {
      root = root->right;
      bool ins = insert(jrnyCode,price);
      root = root->parent;
      if(root->left != NULL)
      {
        root->height = 1 + max(root->left->height,root->right->height);
      }
      else
      {
        root->height = 1 + root->right->height;
      }
      return ins;
    }
  }
  else    //new node already exists
  {
    return false;
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
  TreeNode *f = new TreeNode(jrnyCode,-1);    //stroring the value of jrnycode in a new node
  if(BSTLessThan(f,root))   //finding in the left subtree if value of new node is less than the value of root
  {
    root = root->left;
    int p = find(jrnyCode);
    root = root->parent;
    return p;
  }
  else if(BSTLessThan(root,f))    //finding in the right subtree if value of new node is more than the value of root
  {
    root = root->right;
    int p = find(jrnyCode);
    root = root->parent;
    return p;
  }
  else
  {
    return root->getPrice();    //return the value of node if journeycode
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



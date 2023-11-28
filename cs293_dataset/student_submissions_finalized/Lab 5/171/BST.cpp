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
  TreeNode *z;
    z = new TreeNode(JourneyCode,price);
    if(find(JourneyCode,price))
      return false;
    else{
      TreeNode *y = NULL;
      TreeNode *x = root;
      while(x!=NULL){
        y=x;
        if(JourneyCode<x->JourneyCode)
          x = x->left;
        else
          x  = x->right;
      }
      z->parent = y;
      if(y==NULL)
        root = z;
      else {
        if(JourneyCode<y->JourneyCode)
          y->left = z;
        else 
          y->right = z;
      }
      update(root);
      return true; 
    }

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
  // Implement find in BST
  TreeNode *x = root;
  while(x!=NULL){
    if(JourneyCode==x->JourneyCode){
      if(price==x->price){
        a = x;
        return true;
      }
      else{
        return false;
      }
    }
    if(JourneyCode<x->JourneyCode)
      x = x->left;
    else
      x = x->right;
  }
  
  return false;

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
TreeNode* Minimum(TreeNode* x){
  while(x->left!=NULL){
    x=x->left;
  }
  return x;
}

TreeNode* TreeSuccessor(TreeNode* x){
  TreeNode *y = NULL;
  if(x->right!=NULL)
    return Minimum(x->right);
  y=x->parent;
  while(y!=NULL && x==y->right){
    x=y;
    y=y->parent;
  }
  return y;
}

bool BST::remove(int jrnyCode)
{
   if(!find(JourneyCode,price))
      return false;
    else {
      TreeNode *y;
      TreeNode *x = root;
      if(a->left==NULL || a->right==NULL)
        y=a;
      else
        y=TreeSuccessor(a);
      if(y->left!=NULL)
        x=y->left;
      else
        x=y->right;
      if(x!=NULL)
        x->parent=y->parent;
      if(y->parent==NULL)
        root = x;
      else if(y==y->parent->left)
        y->parent->left=x;
      else
        y->parent->right=x;
      if(y!=a){
        a->JourneyCode=y->JourneyCode;
        a->price=y->price;
        
      }
  
    }
    return true;
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



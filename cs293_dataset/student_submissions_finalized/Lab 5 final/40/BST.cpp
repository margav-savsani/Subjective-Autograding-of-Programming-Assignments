#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

#include <algorithm>

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
  TreeNode *aheadnode = root, *behindnode = nullptr;
  TreeNode *main;
  main = new TreeNode(jrnyCode,100);   
  
  while(aheadnode != nullptr){
    if(BSTLessThan(aheadnode, main)){
      behindnode = aheadnode;
      aheadnode = aheadnode->right;
    }
    else{
      behindnode = aheadnode;
      aheadnode = aheadnode->left;
    }
  }

  if(BSTLessThan(behindnode, main)){
    behindnode->right = main;
    behindnode->right->parent = behindnode;
    TreeNode *goingup;
    goingup = behindnode;

    if(behindnode->left == nullptr){
      goingup->parent->height += 1;
      TreeNode *other;
      TreeNode *current = goingup->parent;
      TreeNode *paront = current->parent;

      while(paront != nullptr){
      
        if(current = paront->right) other = paront->left;
        else other = paront->right;

        if(other != nullptr){
          paront->height = max(other->height + 1, current->height + 1);
        }
        else paront->height = current->height + 1;

        current = paront;
        paront = paront->parent;
      }
    }
  }

  else{
      behindnode->left = new TreeNode(jrnyCode, 100);
      behindnode->left->parent = behindnode;
      if(behindnode->right == nullptr){
        goingup->parent->height += 1;
        TreeNode *other;
        TreeNode *current = goingup->parent;
        TreeNode *paront = current->parent;

        while(paront != nullptr){
      
          if(current = paront->right) other = paront->left;
          else other = paront->right;

          if(other != nullptr){
            paront->height = max(other->height + 1, current->height + 1);
          }
          else paront->height = current->height + 1;

          current = paront;
          paront = paront->parent;
      }
    }
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
  TreeNode *main;
  main = new TreeNode(jrnyCode, 100)      //arbitrary price set as 100
  if(!(BSTLessThan(root,main)) && !(BSTLessThan(root,main))) return root->price;
  if(BSTLessThan(root,main)){
    BST Tr(root->right, perComparisonCost, perParentChildUpdateCost);
    return Tr.find(jrnyCode)
  }
  else{
    BST Tl(root->left, perComparisonCost, perParentChildUpdateCost);
    return Tl.find(jrnyCode)
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



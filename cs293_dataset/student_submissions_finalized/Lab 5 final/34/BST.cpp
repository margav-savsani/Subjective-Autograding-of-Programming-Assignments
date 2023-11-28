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
  if(root == nullptr){
    root = new struct TreeNode(jrnyCode, price);
    root->height = 0;
    return true;
  }
  struct TreeNode* insert = new struct TreeNode(jrnyCode, price);
  struct TreeNode* curr = root;
  struct TreeNode* temp_parent = nullptr;
  bool isLeftChild = false;
  while(root != nullptr){
    if(BSTLessThan(insert, root)){
      temp_parent = root;
      root = root->left;
      isLeftChild = true;
    }
    else if(BSTLessThan(root, insert)){
      temp_parent = root;
      root = root->right;
      isLeftChild = false;
    }
    else{
      return false;
    }
  }
  root = new struct TreeNode(jrnyCode, price);
  updateBSTParentChild(root, temp_parent, isLeftChild);
  int curr_height = 0;
  while(root != nullptr){
    if(root->height < curr_height)root->height = curr_height;
    curr_height++;
    root = root->parent;
  }
  root = curr;
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
  struct TreeNode* insert = new struct TreeNode(jrnyCode, 0);
  struct TreeNode* temp = root;
  while(temp != nullptr){
    if(BSTLessThan(insert, temp)){
      temp = temp->left;
    }
    else if(BSTLessThan(insert, temp)){
      temp = temp->right;
    }
    else{
      return true;
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



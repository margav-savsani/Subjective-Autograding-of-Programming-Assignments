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
  if(root==NULL){
      TreeNode* newNode = new TreeNode(jrnyCode,price);
      root = newNode;
      return true;
  }
  if(find(jrnyCode)!=-1) return false;
  TreeNode* newNode = new TreeNode(jrnyCode,price);
  TreeNode* true_root = root;
  if(BSTLessThan(root,newNode)){
      if(root->right==NULL){
          updateBSTParentChild(newNode,root,false);
          int height(0);
          root = root->right;
          while(root->parent!=NULL){
            root = root->parent;
            height++;
            if(height>root->height) root->height = height;
          }
      }
      else{
          root = true_root->right;
          insert(jrnyCode,price);
          root = true_root;
      }
  }
  else{
      if(root->left==NULL){
          updateBSTParentChild(newNode,root,true);
          int height(0);
          root = root->left;
          while(root->parent!=NULL){
            root = root->parent;
            height++;
            if(height>root->height) root->height = height;
          }
      }
      else{
          root = true_root->left;
          insert(jrnyCode,price);
          root = true_root;
      }
  }
  root = true_root;
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
  if(root==NULL) return -1;
  TreeNode* newNode = new TreeNode(jrnyCode,-1);
  if((!BSTLessThan(root,newNode))&&(!BSTLessThan(newNode,root))) return 1;
  TreeNode* true_root = root;
  if(BSTLessThan(root,newNode)){
      root = true_root->right;
      int ans = find(jrnyCode);
      root = true_root;
      delete newNode;
      return ans;
  }
  else{
      root = true_root->left;
      int ans = find(jrnyCode);
      root = true_root;
      delete newNode;
      return ans;
  }
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



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

  //creating the new node
  TreeNode *t=new TreeNode(jrnyCode, price);

  //base case of recursion
  if (root == NULL){
    root=t;
    return true;
  }

  //new node more than root then do insert in right subtree
  else if (BSTLessThan(root,t)){
    TreeNode *curr=root;

    //base case for right case
    if (root->right == NULL){
      updateBSTParentChild(t,root,false);

      //returning true based on whether to check the heights of above nodes
      //but also returning true if there is nothing to go above this node
      if (root->parent != NULL){
        return root->updateBSTHeight();
      }
      else{
        root->updateBSTHeight();
        return true;
      }
    }

    //if not base case then doing recursion and updating the heights based on what it returns
    root=root->right;
    if (insert(jrnyCode,price)){
      root=curr;
      delete t;
      if (root->parent != NULL){
        return root->updateBSTHeight();
      }
      else{
        root->updateBSTHeight();
        return true;
      }
    }
    else{
      root=curr;
      delete t;
      if (root->parent==NULL){
        return true;
      }
      else{
        return false;
      }
    }
  }
  else{
    TreeNode *curr=root;

    //base case for left case
    if (root->left == NULL){
      updateBSTParentChild(t,root,true);

      //doing same thing as in else if
      if (root->parent != NULL){
        return root->updateBSTHeight();
      }
      else{
        root->updateBSTHeight();
        return true;
      }
    }
    root=root->left;
    if (insert(jrnyCode,price)){
      root=curr;
      delete t;
      if (root->parent != NULL){
        return root->updateBSTHeight();
      }
      else{
        root->updateBSTHeight();
        return true;
      }
    }
    else{
      root=curr;
      delete t;
      if (root->parent==NULL){
        return true;
      }
      else{
        return false;
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
  if (root==NULL){
    return -1;
  }
  TreeNode *t=new TreeNode(jrnyCode,1);
  if (BSTLessThan(root,t)){
    TreeNode *curr=root;
    root=root->right;
    int y=find(jrnyCode);
    root=curr;
    delete t;
    return y;
  }
  else if (BSTLessThan(t,root)){
    TreeNode *curr=root;
    root=root->left;
    int y=find(jrnyCode);
    root=curr;
    delete t;
    return y;
  }
  else{
    return root->getPrice();
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



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
  
  // the scratch case
  if (root == NULL){
    root = new TreeNode(jrnyCode,price);
    root->height = 0;
    return true;
  }

  // if already present
  if (find(jrnyCode)!=-1) return false;
  
  // now to search a spot, insert there
  TreeNode* curr = root;
  TreeNode* t = new TreeNode(jrnyCode,price);

  while(true){
      if(BSTLessThan(curr, t)){
          if(curr->right!=NULL) curr = curr->right;
          else {
              updateBSTParentChild(t,curr,false);
              t->height = 0; curr->height = 1;
              break;    
          }
      }
      else if (BSTLessThan(t, curr)){
          if(curr->left!=NULL) curr = curr->left;
          else {
              updateBSTParentChild(t,curr,true);
              t->height = 0; curr->height = 1;
              break;
          }
      }
  }

  while (curr->parent != NULL){
    int hl=0,hr=0;
    if (curr->parent->left!=NULL) hl = curr->parent->left->height;
    if (curr->parent->right!=NULL) hr = curr->parent->right->height;
    curr->parent->height = 1 + max(hl,hr);
    curr = curr->parent;
  }
              
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{  
  TreeNode* curr = root;
  TreeNode* temp = new TreeNode(jrnyCode,0);

  while(true){
    if (curr == NULL) return -1;
    if (BSTLessThan(temp, curr)){ curr = curr->left; }
    else if (BSTLessThan(curr, temp)) { curr = curr->right; }
    else {
      delete temp;
      return curr->retP(); 
    }
  }
  delete temp;
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



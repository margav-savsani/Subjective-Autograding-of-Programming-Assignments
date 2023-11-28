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
  

TreeNode* A = new TreeNode;
A->price=price;
A->JourneyCode=jrnyCode;A->left=NULL;A->right=NULL; A->parent=NULL;

if (find(jrnyCode)) return false;
if (root==NULL) 
{
  root=A;
  return true;
}
TreeNode* x = new TreeNode;
TreeNode* y = new TreeNode;
x=root;
while(x!=NULL)
{
  if (jrnyCode<x->JourneyCode){
    if (x->left==NULL){ 
      x->left=y;
      y->JourneyCode=jrnyCode;
      y->price=price;
      y->parent=x;
      y->left=NULL;
      y->right=NULL;
      return true; }
    x=x->left;}
  if (x->JourneyCode<jrnyCode){
    if (x->right==NULL){ 
      x->right=y;
      y->JourneyCode=jrnyCode;
      y->price=price;
      y->parent=x;
      y->left=NULL;
      y->right=NULL;
      return true; }
    x=x->right;
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
if (root==NULL) return false;
TreeNode *x=new TreeNode;
x=root;
while (x!=NULL){
if (x->JourneyCode==jrnyCode){return x->price;} 
if (jrnyCode<x->JourneyCode){x=x->left;}
else if (x->JourneyCode<jrnyCode) {x=x->right;}
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



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
  if(find(jrnyCode) != -1)false;

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.
  TreeNode *z=new TreeNode(jrnyCode, price);
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  while (currNode != nullptr) {
    if (BSTLessThan(currNode,z)) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (BSTLessThan(z, currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->jrnyCode == jrnyCode
      return false;
    }
  }
  bool var=true;
  if(parentOfCurrNode != nullptr){
    var = BSTLessThan(z,parentOfCurrNode);
  }
  
  updateBSTParentChild(z, parentOfCurrNode, var);
  //Inserting the first node in the tree
  if(root == nullptr)root=z;
  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  while(parentOfCurrNode != nullptr){
    if(parentOfCurrNode->height > (z->height)){
      break;
    }
    parentOfCurrNode->height += 1;
    z = parentOfCurrNode;
    parentOfCurrNode = parentOfCurrNode->parent;
  }

  
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

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.
  TreeNode *cmp = new TreeNode(jrnyCode,0);
  TreeNode *currNode = root;
  while( currNode != nullptr){
    bool v1 = BSTLessThan(currNode, cmp);
    if(v1){
      currNode = currNode->right;
      continue;}
    bool v2 = BSTLessThan(cmp, currNode);
    if(v2){
      currNode = currNode->left;
      continue;}
    if(!(v1 || v2))return currNode->getprice();
  }

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



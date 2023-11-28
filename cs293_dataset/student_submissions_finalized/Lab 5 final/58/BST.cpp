#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


void BST::update(int jrnyCode){

  class TreeNode *nemo=new TreeNode(jrnyCode,7);
  class TreeNode *currNode =root;

  while(currNode!=nullptr){
    if(BSTLessThan(nemo,currNode)){
      int m=currNode->highestlength();
      if(m > currNode->height) currNode->height=m;

      currNode=currNode->left;
    }

    else if(BSTLessThan(currNode,nemo)){
      int m=currNode->highestlength();
      if(m > currNode->height) currNode->height=m;

      currNode=currNode->right;
    }

    else{
      delete nemo;
      return;
    }
  }
}
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
  class TreeNode *childNode = new TreeNode(jrnyCode,price);
  class TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  while (currNode != nullptr) {
    if (BSTLessThan(currNode,childNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (BSTLessThan(childNode,currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else return false;
  } 

  if(parentOfCurrNode!=nullptr){
    bool isleft=BSTLessThan(childNode,parentOfCurrNode);
    updateBSTParentChild(childNode,parentOfCurrNode,isleft);
    update(jrnyCode);
  }

  else{
    root=childNode;
    root->parent=nullptr;
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
  class TreeNode *nemo=new TreeNode(jrnyCode,7);
  class TreeNode *currNode = root, *parentOfCurrNode = nullptr;

  while (currNode != nullptr) {
    if (BSTLessThan(currNode,nemo)) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (BSTLessThan(nemo,currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->jrnyCode == jrnyCode
      return 1;
    }

  } 

  delete nemo;
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



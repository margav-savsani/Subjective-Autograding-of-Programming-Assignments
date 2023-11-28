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
  TreeNode* newNode = new TreeNode(jrnyCode, price);
  TreeNode* currNode = root;
  bool inserted = false;

  //inserting like a normal BST 
  if(root == nullptr){
    root = newNode;
    return true;
  } else {

    while(true){
      //finding the position to insert in the tree.
      if (BSTLessThan(newNode, currNode)){

        if (currNode->left == nullptr) {
          updateBSTParentChild(newNode, currNode,true);
          return true;
        } else {
          currNode = currNode -> left;
        }

      } else if (BSTLessThan(currNode, newNode)){

        if (currNode->right == nullptr) {
          updateBSTParentChild(newNode, currNode, false);
          return true;
        } else {
          currNode = currNode -> right;
        }

      } else {
        return false;
      }
    } 

    return false;
 }


  // Implement insertion in BST

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

  int arbPrice = 999;

  TreeNode * toFind = new TreeNode(jrnyCode, arbPrice);
  TreeNode * currNode = root;
  //if node less than currNode go left, if greater go right. otherwise we have found the element.
  while(currNode != nullptr){
    if (BSTLessThan(currNode, toFind)){
      currNode = currNode->right;
    } else if (BSTLessThan(toFind, currNode)){
      currNode = currNode->left;
    } else {
      return currNode->getPrice();
    }
  }
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

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



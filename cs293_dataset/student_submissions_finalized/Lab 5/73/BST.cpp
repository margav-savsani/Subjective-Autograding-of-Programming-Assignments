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
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  while (currNode != nullptr) 
  {
    if (currNode->getjrnycode() < jrnyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->getjrnycode() > jrnyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }
  currNode=new TreeNode(jrnyCode,price); //making node
  currNode->parent=parentOfCurrNode;    //giving the parent to it
  if (parentOfCurrNode==nullptr)
  {
    root=currNode;  //if parent is nullptr then it is root
    return true;
  }
  else if (currNode->getjrnycode() <=parentOfCurrNode->getjrnycode())
  {
    parentOfCurrNode->left=currNode;//left child
    return true;
  }
  else
  {
    parentOfCurrNode->right=currNode;   //rigth child
    return true;
  }
  return false;
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
  TreeNode *sample=this->root;        //checking from root
  if (sample==nullptr)        //nothing is added
      return -1;
  while(sample!=nullptr && jrnyCode!=sample->getjrnycode())  //checking for equal price or it will go to nullptr
  {
      if (jrnyCode > sample->getjrnycode())
          sample=sample->right;
      else
          sample=sample->left;
  }
  if (sample==nullptr)        //if nullptr return false
      return -1;
  return sample->getprice();  
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



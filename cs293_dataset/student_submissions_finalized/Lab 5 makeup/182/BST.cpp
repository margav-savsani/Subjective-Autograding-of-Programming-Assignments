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
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr ;
  struct TreeNode *n;
  n=new TreeNode(jrnyCode,price);
  bool inserted=false;
  if(currNode==nullptr){
    root =n;
    return true;
  }
  while (currNode != nullptr) {
   // if (currNode->getJourneyCode() < jrnyCode)
    if(BSTLessThan(currNode,n)) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
      
    }
    else if (BSTLessThan(n,currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
  }
  // jrnyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  if(BSTLessThan(n,parentOfCurrNode))
    {
        updateBSTParentChild(n,parentOfCurrNode,false);
        inserted=true;
    }
  if(BSTLessThan(parentOfCurrNode,n))
    {
        updateBSTParentChild(n,parentOfCurrNode,true);
        inserted=true;
    }
  if(!inserted) return false;
  while(n!=root){
      n->setheight();
      n=n->parent;
    }
  root->setheight();
  

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
  struct TreeNode *currNode = root,*parentOfCurrNode = nullptr ;
  struct TreeNode *n;
  int price=2;
  n=new TreeNode(jrnyCode,price);
  if(currNode==nullptr) return -1;
  while (currNode != nullptr) {
    if(BSTLessThan(currNode,n)) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
      
    }
    else if(BSTLessThan(n,currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }  
    if(!(BSTLessThan(parentOfCurrNode,n)) && !(BSTLessThan(n,parentOfCurrNode))) 
    {return 1;}
  }
  return -1;
}
bool BST::remove(int jrnyCode)
{
  return true;
}



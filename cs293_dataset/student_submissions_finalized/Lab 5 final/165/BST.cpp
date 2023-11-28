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
  

  if(find(jrnyCode)!=-1){//if journey code already exists return false
    return false;
  }
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.
  TreeNode* insertnode = new TreeNode(jrnyCode,price);
  TreeNode* temp = root;
  TreeNode* prev = nullptr;
  bool isLeftChild;
  while(temp!=nullptr ){
    prev = temp;//so that parent of temp is always stored in prev
    if(BSTLessThan(insertnode , temp)){//go left if node to be inserted is less than current node temp
      temp = temp->left;
      isLeftChild = true;
    }
    else{                             //go right if node to be inserted is more than current node temp
      temp = temp->right;
      isLeftChild = false;
    }
  }

  //root case
  if(prev == nullptr){
    
    root = insertnode;
    updateBSTParentChild(insertnode,nullptr,isLeftChild);
  }
  else{
    temp = insertnode;
    updateBSTParentChild(insertnode,prev,isLeftChild);
    // REMEMBER to update the heights of appropriate nodes in the tree
    // after an insertion.
    temp = temp->parent;
    while(temp!=nullptr){//this is condition for root's parent where this loop must stop
      if(temp->left == nullptr && temp->right!=nullptr){
        temp->height = 1 + temp->right->height;
      }
      else if(temp->right == nullptr && temp->left!= nullptr){
        temp->height = 1 + temp->left->height;
      }
      else{//two children case
        temp->height = 1 + max(temp->left->height,temp->right->height);
      }
      temp = temp->parent;//update height of all ancestors of our inserted node
    }
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


  TreeNode* findnode = new TreeNode(jrnyCode,0);
  TreeNode* temp = root;
  while(temp!=nullptr ){
    if(findnode->getJourneyCode()== temp->getJourneyCode())
      return temp->getprice();
    if(BSTLessThan(findnode , temp)){// if node to be found is less than currentnode go left
      temp = temp->left;
    }
    else{//else go right
      temp = temp->right;
    }
    
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



//Assuming that the journey codes entered aren't unique
#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

void heightAdd(int &h, TreeNode* curr){
  if (curr==nullptr){
    return;
  }
  else if(curr->height<*h+1){
    curr->height=*h+1;
    heightAdd(curr->height, curr->parent);
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

  //Checks whether there is tree or not
  //If not, creates the entry at the root
  if(root==nullptr){
    root=new TreeNode(jrnyCode, price);
    root->parent=nullptr;
    return true;
  } 
  TreeNode *curr=root;
  TreeNode *newN=new TreeNode(JourneyCode, price);
  //while loop to find the location of insertion
  while(true){
    if(BSTLessThan(newN,curr)){
      if(curr->left==nullptr){
        curr->left=newN;
        curr->left->parent=curr;
        heightAdd(curr->height, curr->parent);
        return true;
      }
      curr=curr->left;
    }
    else if(BSTLessThan(curr,newN)){
      if(curr->right==nullptr){
        curr->right=newN;
        curr->right->parent=curr;
        heightAdd(curr->height, curr->parent);
        return true;
      }
      curr=curr->right;
    }
    else 
      return false;
  }
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
  
  TreeNode *curr=root;
  //whike loop to find the entry with the given price
  //If such a entry is found, the journey codes are compared
  TreeNode* newN= new TreeNode(jrnyCode,0);
  while(curr!=nullptr){
    if(!BSTLessThan(curr,newN) && !BSTLessThan(newN,curr)){
      return curr->price;
    }
    else if(BSTLessThan(newN,curr))
      curr=curr->left;
    else
      curr=curr->right;
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



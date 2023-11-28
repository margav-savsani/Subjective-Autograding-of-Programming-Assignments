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

    TreeNode* x = root; //for checking
    TreeNode* y = NULL; //for pointing to the parent
    TreeNode* node = new TreeNode(jrnyCode, price);

    if(root == NULL){
        root = node;
        return true;
    }

    while(x != NULL){
        // cout<<"x not null";
        y = x;
        // if(x->price == price && x->JourneyCode == JourneyCode){
        //     return false;
        // }
        if( x > node ){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    
    node->parent = y;

    if(y == NULL){
      return false;
    }


    if( y  > node ){
        y->left = node;
    }
    else{
        y->right = node;
    }
    
    return true;

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
 
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

   TreeNode* temp = root; 
   TreeNode* dummy = new TreeNode( jrnyCode, 0); //price arbitrary since comparision is on jc

    while(temp != NULL){
        if(temp->price == price && temp->JourneyCode==JourneyCode){
            return true;
        }
        if(temp->price > price){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    
    return false; 

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



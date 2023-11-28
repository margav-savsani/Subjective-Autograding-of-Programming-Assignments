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

bool BST::insert(int JourneyCode, int price)
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

  TreeNode* newnode = new TreeNode(JourneyCode,price);
        TreeNode *y = NULL;
        TreeNode *x = root;
        bool left;
        if(find(JourneyCode) == 1){
            return false;
        }
        while(x != NULL){
            y = x;
            if(BSTLessThan(newnode,x)){
                x = x->left;
                left = true;
            }
            else{
                x = x->right;
                left = false;
            }
            }
        updateBSTParentChild(newnode, y , left);
        x=newnode;
        while (y != nullptr)
        {
            if (y->height < 1 + x->height)
            {
                y->height = 1 + x->height;
            }
            x = y;
            y = y->parent;
        }
        // if(y == NULL){
        //     root = newnode;
        // }
        // else{
        //     if (BSTLessThan(newnode,y))
        //     {
        //         updateBSTParentChild(newnode, y,true);
        //     }
        //     else{
        //         updateBSTParentChild(newnode, y,false);
        //     }
        // } 
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int JourneyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
    TreeNode *x;
    x = root;
    TreeNode* newnode = new TreeNode(JourneyCode,1);
    if(x == NULL){
        return -1;
    }
    if(!(BSTLessThan(x,newnode) || BSTLessThan(newnode,x))){
        return 1;
    }
    else{
        if(BSTLessThan(newnode,x)){
            x = x->left;
            BST* leftTree = new BST(x);
            return leftTree->find(JourneyCode);
        }
        else{
            x = x->right;
            BST* rightTree = new BST(x);
            return rightTree->find(JourneyCode);
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



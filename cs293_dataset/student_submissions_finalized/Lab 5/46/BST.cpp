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
  TreeNode *x,*y,*z;
        x = root;
        y = NULL;
        z = new TreeNode(JourneyCode,price);
        if(find(JourneyCode,price)) return false;
        if(x==NULL) {
            root = z;
            root->parent = NULL;
            return true;
        }
        while(x != NULL) {
            y = x;
            if(BSTLessThan(z,x)) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        z->parent = y;
        if(BSTLessThan(z,y)) {
                 y->left = z;
                 return true; 
        }
        else {
                y->right = z;
                return true;
        }
        return false;

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

TreeNode* BST::find_tree(TreeNode* x,int JourneyCode) {
        TreeNode *tmp=new TreeNode(0,JourneyCode);
        if(x == NULL) {
            return NULL;
        }
        if((!(BSTLessThan(tmp,x))) && (!(BSTLessThan(x,tmp)))) {
            return x;
        }
        if(BSTLessThan(tmp,x)) {
            return find_tree(x->left,JourneyCode);
        }
        else {
            return find_tree(x->right,JourneyCode);
        }
        return NULL;
}

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

    if(find_tree(root,JourneyCode)==NULL) return false;
    return true;

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
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



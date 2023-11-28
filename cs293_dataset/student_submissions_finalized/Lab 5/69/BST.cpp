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

bool BST :: ins(TreeNode *p, int jc, int pc){
	TreeNode *j = new TreeNode(jc, pc);
    if(p==NULL){
        TreeNode *i = new TreeNode(jc, pc);
        root = i;
        return true;
    }
    else{
        if (jc == p->JourneyCode){
                return false;
        }
        if (j < p){
        	if(p->left == NULL){
                TreeNode *value = new TreeNode(jc, pc); 
                p->left = value;
                return true;  
            }
            return  ins(p->left, jc, pc);
            
        }
        else{
            if (p->right == NULL){
                TreeNode *val = new TreeNode(jc, pc);
                p->right = val;
                return true;
            }
            return ins(p->right, jc, pc);
        }
    }
}

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
  TreeNode *i = root;
    return ins(i,jrnyCode,price);
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST


bool BST :: findfunc(TreeNode *p, int jc) {
    if(jc == p->JourneyCode){
            return true;
    }
    if(j < p){
        if(p->left == NULL){
            return false;
        }
        return findfunc(p->left, jc);
    }
    else{
        if(p->right == NULL){
            return false;
        }
        return findfunc(p->right, jc);
    }
    return false;
}

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
  TreeNode *f = root;
  if(findfunc(f, jrnyCode)) return -1;
  return 0;
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



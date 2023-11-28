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
{ TreeNode *trai = new TreeNode(jrnyCode,price);
  if (root == nullptr){
    TreeNode *tr;
    tr = new TreeNode(0,0);
    tr->insj(jrnyCode);
    tr->insp(price);
    tr->left=nullptr;
    tr->right=nullptr;
    tr->parent=nullptr;
    root = tr;
    return true;
  }
  else {
    if (find(jrnyCode)) return false;
    else{
      TreeNode *curr;
      curr=root;
      while(true){ // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if price is greater
        if(!BSTLessThan(trai,curr)){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
              TreeNode *tre;
              tre= new TreeNode(0,0);
                tre->insj(jrnyCode);
                tre->insp(price);
                tre->parent=curr;
                curr->right=tre;
                break;
            }
        }
        else{
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                TreeNode *tre;
                tre = new TreeNode(0,0);
                tre->insj(jrnyCode);
                tre->insp(price);
                tre->parent=curr;
                curr->left=tre;
                break;
            }
        }
    }

  return true;
  }
}
}

// Returns the price on finding an element in the BST that matches
// journey code. Retur otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode){
  TreeNode *traile = new TreeNode(jrnyCode,0);
  int bruh=0;
  TreeNode *trump;
  TreeNode *trumpy;
  trump=root;
  while(bruh == 0 && trump!=nullptr){
    if(trump->getjrny() == jrnyCode){
      bruh=1;
      trumpy = trump;
    }
    else if(!BSTLessThan(trump,traile)){
      trump=trump->left;
    }
    else if(BSTLessThan(trump,traile)){
      trump=trump->right;
    }
  }
  if(bruh==0){
    return -1;
  }
  else return trumpy->getpric();
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



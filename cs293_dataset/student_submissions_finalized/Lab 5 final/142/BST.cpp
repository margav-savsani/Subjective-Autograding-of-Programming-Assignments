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
  TreeNode *x;
  if(root == NULL){
        root = new TreeNode(jrnyCode,price);
        return true;
    }
    // Checking if similar node already exists
    if(find(jrnyCode))return false;
    TreeNode *curr = root;
    while(true){
        curr->height++; // incrementing Size of subtree which is rooted at this node

        // Moving to the right, if price is greater
        if(price > curr->get_price()){
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new TreeNode(jrnyCode,price);
                break;
                
            }
        }else{
            // moving to left if its smaller
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new TreeNode(jrnyCode,price);
                curr->left->parent = curr;
                break;
                
            }
        }
    }
  //  this->printBST("",false);
    return true;
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST
bool BST::findjc(TreeNode* currNode,TreeNode* x){
  if(!BSTLessThan(x,currNode) && !BSTLessThan(x,currNode))
    return true;
  if(currNode==nullptr)
    return false;
  else if(BSTLessThan(x,currNode)){
    findjc(x,currNode->left);
  }
  else 
    findjc(x,currNode->right);
  return false;
}
int BST::find(int jrnyCode)
{
  // Implement find in BST
  TreeNode* x = new TreeNode(jrnyCode,0);
  TreeNode* currNode;
  currNode = this->root;
  return findjc(currNode,x);
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

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



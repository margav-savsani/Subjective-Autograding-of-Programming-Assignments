#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif
#include <cmath>

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
    TreeNode*t=new TreeNode(jrnyCode,0);

  if(root == NULL){
        root = new TreeNode(jrnyCode,price);
        return true;
    }
    // Checking if similar node already exists
    if(find(jrnyCode)==1)return false;
    TreeNode *curr = root;
    while(true){
        // Moving to the right, if price is greater
        if(BSTLessThan(curr,t)){
             totalComparisonCost += perComparisonCost;
            if(curr->right!=NULL){
                curr = curr->right;
            }else{
                curr->right = new TreeNode(jrnyCode,price);
                break;
                
            }
        }else{
            // moving to left if its smaller
             totalComparisonCost += perComparisonCost;
            if(curr->left!=NULL){
                curr = curr->left;
            }else{
                curr->left = new TreeNode(jrnyCode,price);
                break;
                
            }
        }
    }
  //  this->printBST("",false);
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
      TreeNode*t=new TreeNode(jrnyCode,0);
  if(root==NULL)return -1;
    TreeNode* curr = root;
    while(true){
      bool b= (BSTLessThan(curr,t) || BSTLessThan(t,curr));
        if(!b){
            if(!b){
                totalComparisonCost += 2*perComparisonCost;
                return curr->getprice();
            }else return -1;
        } else if(BSTLessThan(t,curr)){
            totalComparisonCost += 2*perComparisonCost;
            if(curr->left==NULL){
                return -1;
            }else{
                curr = curr->left;
            }
        }else{
             totalComparisonCost += 2*perComparisonCost;
            if(curr->right==NULL){
                return -1;
            }else{
                curr = curr->right;
            }
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



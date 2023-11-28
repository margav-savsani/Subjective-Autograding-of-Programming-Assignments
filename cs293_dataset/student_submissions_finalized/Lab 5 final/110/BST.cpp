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
TreeNode* BST:: insertelement(TreeNode* root,int JourneyCode,int price,TreeNode* element){     // defining new function for using recursion
    
    if(root == NULL){
        root = element;
        root->height =0;
        return root;
    }
    else if(BSTLessThan(root,element)){
        root->right = insertelement(root->right,JourneyCode,price,element);
        root->right->parent= root;
        if(root->left!=NULL){  
          if(root->right->height>root->left->height) root->height=1+root->right->height;
        }
        else root->height=1+root->right->height;
    }
    else{
        root->left = insertelement(root->left,JourneyCode,price,element);
        root->left->parent = root;
        if(root->right!=NULL){  
          if(root->left->height>root->right->height) root->height=1+root->left->height;
        }
        else root->height=1+root->left->height;
    }
     return root;
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
  if (find(jrnyCode)!= -1) return false;
  TreeNode* i = new TreeNode(jrnyCode,price);
  root = insertelement(root,jrnyCode,price,i);
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
  TreeNode* search = new TreeNode(jrnyCode,44);
  TreeNode* tr = new TreeNode(0,0);
  tr = root;
  while(tr!=NULL){
    if(!(BSTLessThan(tr,search) || BSTLessThan(search,tr))) return 1;
    else if(BSTLessThan(tr,search)) tr=tr->right;
    else tr = tr->left;
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



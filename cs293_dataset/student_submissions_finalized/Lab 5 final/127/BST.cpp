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

  TreeNode* temp_new=new TreeNode(jrnyCode, price);
  TreeNode* new_node;
  
  TreeNode* search_node=root;
  if(search_node==nullptr){
      root=new TreeNode(jrnyCode, price);
      return true;
  }
  while(true) {
    if(search_node->JourneyCode==jrnyCode) return false;
    if(BSTLessThan(temp_new, search_node)) {
        if(search_node->left==nullptr) {
            new_node = new TreeNode(jrnyCode, price);
            new_node->parent=search_node;
            search_node->left=new_node;
            search_node=search_node->left;
            break;
        }
        else {
            search_node=search_node->left;
        }
    }
    else {
        if(search_node->right==nullptr) {
            new_node = new TreeNode(jrnyCode, price);
            new_node->parent=search_node;
            search_node->right=new_node;
            search_node=search_node->right;
            break;
        }
        else {
            search_node=search_node->right;
        }
    }
  }

  // Implement insertion in BST

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

int BST::find(int jrnyCode)
{

  TreeNode* temp_new_node=new TreeNode(jrnyCode, 0);
  TreeNode* search_node=root;

    while(true) {
        if(search_node->JourneyCode==jrnyCode) {
            return 1;
        }
        else if(BSTLessThan(temp_new_node, search_node)) {
            if(search_node->left==nullptr) return -1;
            else search_node=search_node->left;
        }
        else {
            if(search_node->right==nullptr) return -1;
            else search_node=search_node->right;
        }
  }

  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

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



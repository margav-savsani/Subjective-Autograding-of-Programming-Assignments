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

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
    bool left = true;
    TreeNode* prnt = nullptr;
    TreeNode* pos_ins = root;
    TreeNode* a = new TreeNode(jrnyCode,price);
    a->left = nullptr;
    a->right = nullptr;
    a->height = 0;
    if (root == nullptr){
        this->root = a;
        return true;
    }
    while (pos_ins != nullptr) {
        if (BSTLessThan(a, pos_ins)){
            prnt=pos_ins;
            pos_ins->height+=1;
            pos_ins=pos_ins->left;
            left=true;
        }
        else if (BSTLessThan(pos_ins, a)){
            prnt=pos_ins;
            pos_ins->height+=1;
            pos_ins=pos_ins->right;
            left=false;
        }
        else return false;
    }
    pos_ins = a;
    pos_ins->parent = prnt;
    if (left) prnt->left = pos_ins;
    else prnt->right = pos_ins;
  
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

  TreeNode n = TreeNode(jrnyCode,0);
  TreeNode* find_node = &n;
  TreeNode* pos_ins = root;
  if (root == nullptr) return false;
  while (pos_ins != nullptr){
      if (BSTLessThan(find_node, pos_ins)) pos_ins = pos_ins->left;
      else if (BSTLessThan (pos_ins, find_node)) pos_ins = pos_ins->right;
      else return 1;
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



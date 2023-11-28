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
    TreeNode* insertNode = new TreeNode(jrnyCode, price);
  if(root != NULL){
    insertHelper(insertNode, root); // call helper function
  }else{
    insertNode->height = 0;
    root = insertNode;
  }

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}

void BST::insertHelper(TreeNode* insertNode, TreeNode* cnode){
  if(cnode == NULL)
    return;

  if(BSTLessThan(insertNode, cnode)){ // if insertNode belongs to left subtree
    if(cnode->left == NULL){
      cnode->left = insertNode;
      updateBSTParentChild(insertNode, cnode, true);
      insertNode->height = 0;
      return;
    }
    insertHelper(insertNode, cnode->left);
  } else{
    if(cnode->right == NULL){ // if insertNode belongs to right subtree
      cnode->right = insertNode;
      updateBSTParentChild(insertNode, cnode, false);
      insertNode->height = 0;
      return;
    }
    insertHelper(insertNode, cnode->right);
  }

  cnode->height = 1 + max((cnode->left == NULL ? -1 : cnode->left->height), (cnode->right == NULL ? -1: cnode->right->height)); // update height
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

  TreeNode* foundNode = findHelper(jrnyCode, root); // call helper function

  if(foundNode != NULL)
    return 1;
  else
    return -1;

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  return -1;
}

TreeNode* BST::findHelper(int jrnyCode, TreeNode* cnode){
  if(cnode == NULL)
    return NULL;

  TreeNode* compNode = new TreeNode(jrnyCode, -1);
  if(BSTLessThan(compNode, cnode)){ // if compNode belongs to left subtreee
    return findHelper(jrnyCode, cnode->left);
  } else if(BSTLessThan(cnode, compNode)){ // if compNode belongs to right subtree
    return findHelper(jrnyCode, cnode->right);
  } else{
    return cnode; // cnode is the required node
  }
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



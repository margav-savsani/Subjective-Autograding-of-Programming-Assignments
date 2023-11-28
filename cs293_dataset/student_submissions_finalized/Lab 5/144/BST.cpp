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

void updateHeight(TreeNode* node_ptr){
  int maxLeft, maxRight;
  if(node_ptr->left == nullptr){
    maxLeft = -1;
  }

  else{
    maxLeft = node_ptr->left-> height;
  }

  if(node_ptr->right == nullptr){
    maxRight = -1;
  }

  else{
    maxRight = node_ptr->right-> height;
  }

  node_ptr->height = 1 + std::max(maxLeft, maxRight);
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
  TreeNode *temp = new TreeNode(jrnyCode, price);

  if (root == nullptr)
  {
    root = temp;
    root->parent = nullptr;
    return true;
  }

  TreeNode *next_ptr;
  TreeNode *parent_to_add = root;

  if (BSTLessThan(temp, root))
  {
    next_ptr = root->left;
  }

  else
    next_ptr = root->right;

  while (next_ptr != nullptr)
  {
    parent_to_add = next_ptr;

    if (BSTLessThan(temp, parent_to_add))
    {
      next_ptr = parent_to_add->left;
    }

    else
      next_ptr = parent_to_add->right;
  }

  if (BSTLessThan(temp, parent_to_add))
  {
    updateBSTParentChild(temp, parent_to_add, true);
  }

  else
  {
    updateBSTParentChild(temp, parent_to_add, false);
  }

  TreeNode* parent = temp->parent;

  while(parent != nullptr){
    updateHeight(parent);
    parent = parent->parent;
  }
  
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

  TreeNode* current_ptr = root;
  TreeNode temp(jrnyCode, 1);

  while(current_ptr != nullptr){
    if(!(BSTLessThan(&temp, current_ptr))){
      if(!(BSTLessThan(current_ptr, &temp))){
        return current_ptr->getPrice();
      }

      else{
        current_ptr = current_ptr->right;
      }
    }

    else{
      current_ptr = current_ptr->left;
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

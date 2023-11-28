#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


int BST::height(TreeNode *n) {
if(n == nullptr)
  return -1;
return n->height;
}

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
  TreeNode* z = new TreeNode(jrnyCode, price);
    TreeNode* y = nullptr, *x = root;
    while(x != nullptr){
        y = x;
        if (BSTLessThan(z, x))
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;

    if(y == nullptr){
        root = new TreeNode(z->getJrnyCode(), z->getPrice());
        // root = z;
        // root->price = z->price;
        delete [] z;
        return true;
    }
    else if(y->getJrnyCode() == z->getJrnyCode())
        return false;
    else if(BSTLessThan(z, y)){
        y->left = z;
        TreeNode* temp = y;
        while(temp != nullptr){
          temp->height = 1 + max(height(y->left), height(y->right));
          temp = temp->parent;
        }
        return true;
    }
    else{
        y->right = z;
        return true;
    }

  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  // return true;
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

  TreeNode* x = root;
  TreeNode* z = new TreeNode(jrnyCode, x->getPrice());
    while(x != nullptr && x->getJrnyCode() != z->getJrnyCode()){
        if(BSTLessThan(z, x))
            x = x->left;
        else
            x = x->right;
    }
    if(x != nullptr){
        return true;
    }
    else
        return false;
  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  // return -1;
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



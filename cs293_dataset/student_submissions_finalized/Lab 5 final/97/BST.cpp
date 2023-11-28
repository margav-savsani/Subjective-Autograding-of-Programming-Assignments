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
      delete z;
  }
  else if(!(BSTLessThan(y, z) || BSTLessThan(z, y)))
      return false;
  else if(BSTLessThan(z, y))
      updateBSTParentChild(z, y, true);
  else
      updateBSTParentChild(z, y, false);

  while(y != nullptr){
        y->height = 1 + max(height(y->left), height(y->right));
        y = y->parent;
  }
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
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  TreeNode* x = root;
  TreeNode* z = new TreeNode(jrnyCode, jrnyCode);
    while(x != nullptr && (BSTLessThan(x, z) || BSTLessThan(z, x))){
        if(BSTLessThan(z, x))
            x = x->left;
        else
            x = x->right;
    }
    if(x != nullptr){
        return x->getPrice();
    }
    else
        return -1;
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
   TreeNode* x = root;
   TreeNode* z = new TreeNode(jrnyCode, jrnyCode);
    //finds where the node to be deleted is in the tree
    while(x != nullptr && (BSTLessThan(x, z) || BSTLessThan(z, x))){
        if(BSTLessThan(z, x))
            x = x->left;
        else
            x = x->right;
    }

    // if node not found, reutrns false
    if(x == nullptr || (BSTLessThan(x, z) || BSTLessThan(z, x)))
        return false;

    //if node is a child, simply remove the pointer to it from its parent, and delete the child
    if(x->left == nullptr && x->right == nullptr){
        if(x->parent == nullptr){
            root = nullptr;
            return true;
        }
        else{
            if(x->parent->left != nullptr){
                if(!(BSTLessThan(x, x->parent->left) || BSTLessThan(x->parent->left, x)))
                    x->parent->left = nullptr;
                else
                    x->parent->right = nullptr;
            }
            else
                x->parent->right = nullptr;
        }
    }
    // if the node has two children
    else if(x->left != nullptr && x->right != nullptr){
        TreeNode* y = getMaximum(x->left);
        int tempJourneyCode = y->getJrnyCode();
        int tempPrice = y->getPrice();
        remove(tempJourneyCode);
        x->set(tempJourneyCode, tempPrice);
    }
    // if the node has only a left child
    else if(x->left != nullptr){
        if(x->parent == nullptr){
            root = x->left;
            root->parent = nullptr;
        }
        else{
            x->left->parent = x->parent;
            if(x->parent->left != nullptr){
                if(!(BSTLessThan(x, x->parent->left) || BSTLessThan(x->parent->left, x)))
                    // x->parent->left = x->left;
                    updateBSTParentChild(x->left, x->parent, true);
                else
                    // x->parent->right = x->left;
                    updateBSTParentChild(x->left, x->parent, false);   
            }
            else
                // x->parent->right = x->left;
                updateBSTParentChild(x->left, x->parent, false);
        }
        x->left = nullptr;
        x->right = nullptr;
        x->parent = nullptr;
    }
    // if the node has only a right child
    else if(x->right !=nullptr){
        if(x->parent == nullptr){
            root = x->right;
            root->parent = nullptr;
        }
        else{
            x->right->parent = x->parent;
            if(x->parent->left != nullptr){
                if(!(BSTLessThan(x, x->parent->left) || BSTLessThan(x->parent->left, x))){
                    // x->parent->left = x->right;
                    updateBSTParentChild(x->right, x->parent, true);
                }
                else
                    // x->parent->right = x->right;
                     updateBSTParentChild(x->right, x->parent, false);
            }
            else{
                // x->parent->right = x->right;
                updateBSTParentChild(x->right, x->parent, false);
            }
            x->left =nullptr;
            x->right = nullptr;
            x->parent = nullptr;
        }
    }
  return true;
}

// finds maximum in the BST
TreeNode* BST::getMaximum(TreeNode* y){
    while (y->right != NULL)
        y = y->right;
    return y;
}

#ifndef BST_H
#include "BST.h"
#include <bits/stdc++.h>
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

    TreeNode *foo = new TreeNode(jrnyCode, 0);
    TreeNode *tmp = root;
    TreeNode *parent = nullptr;
    bool dir;       // 'dir' gives the direction of traversing which is used in line 50
    while (tmp != nullptr){
        if (BSTLessThan(foo, tmp)){
            parent = tmp;
            tmp = tmp->left;
            dir = true;
        }
        else if (BSTLessThan(tmp, foo)){
            parent = tmp;
            tmp = tmp->right;
            dir = false;
        }
        else{
            return false;
        }
    }
    if (parent != nullptr){ // the 'non-root' case
        if (dir){
            parent->left = new TreeNode(jrnyCode, price, nullptr, nullptr, parent, 0);
            tmp = parent->left;
        }
        else{
            parent->right = new TreeNode(jrnyCode, price, nullptr, nullptr, parent, 0);
            tmp = parent->right;
        }
    }
    else{ // the 'root' case
        root = new TreeNode(jrnyCode, price, nullptr, nullptr, nullptr, 0);
        return true;
    }

    // updation of heights
    while (tmp != root){
        parent = tmp->parent;
        if (parent->left == nullptr || parent->right == nullptr){
            parent->height = tmp->height + 1;
        }
        else{
            parent->height = 1 + max(parent->left->height, parent->right->height);
        }
        tmp = parent;
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

    TreeNode *foo = new TreeNode(jrnyCode, 0);
    TreeNode *tmp = root;
    while (tmp != nullptr){
        if (BSTLessThan(tmp, foo)){
            tmp = tmp->right;
        }
        else if (BSTLessThan(foo, tmp)){
            tmp = tmp->left;
        }
        else{
            return tmp->price;
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



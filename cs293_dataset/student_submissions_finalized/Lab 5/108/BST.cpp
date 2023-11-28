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

bool BST::insert(int jrnyCode, int price) {
    // Implement insertion in BST

    // You MUST use only BSTLessThan to compare two journey codes. You
    // can create a new node containing the journey code to be inserted
    // and invoke BSTLessThan on the current node in the tree that you
    // are inspecting and the new node to do your comparison.

    // REMEMBER to update the heights of appropriate nodes in the tree
    // after an insertion.
    
    if (find(jrnyCode)) return false;

    // Create the new node
    TreeNode* new_node = new TreeNode { jrnyCode, price };
    new_node->parent = nullptr;

    // Inserting at the root
    if (!root) {
        root = new_node;
        return true;
    }

    // Insert at the right place
    TreeNode* cur { root };
    while (true) {
        if (price > cur->price) {
            if (cur->right) cur = cur->right;
            else {
                cur->right = new_node;
                new_node->parent = cur;
                return true;
            }
        } else {
            if (cur->left) cur = cur->left;
            else {
                cur->left = new_node;
                new_node->parent = cur;
                return true;
            }
        }
    }
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::find(int jrnyCode) {
    // Implement find in BST

    // You MUST use only BSTLessThan to compare two journey codes. You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke BSTLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    TreeNode dummy {jrnyCode, 0};
    TreeNode* cur { root };
    while (true) {
        if (!cur) return false;

        if (cur->JourneyCode == jrnyCode) return true;

        if (BSTLessThan(cur, &dummy)) cur = cur->right;
        else cur = cur->left;
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

bool BST::remove(int jrnyCode) {
    // Implement deletion in BST
    
    // You MUST use only BSTLessThan to compare two journey codes. You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke BSTLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    // REMEMBER to update the height of appropriate nodes in the tree
    // after a successful deletion.
    
    // We use "return true" below to enable compilation. Change this as you
    // see fit.

    return true;
}
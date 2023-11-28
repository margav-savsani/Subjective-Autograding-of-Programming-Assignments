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

bool BST::insert(int JourneyCode, int price) {
    // Check if the tree is empty.
    if (!root){
        root = new TreeNode(JourneyCode, price, nullptr);
        return true;
    }
    TreeNode *curr = root;

    // binary search loop. Search for where to put it.
    while (true){

        // invariant: curr is never null.

        if (curr->JourneyCode == JourneyCode)
            return false; // this journey code is already in the tree - we do not add another entry for the same journey.
        
        if (price < curr->price){
            if (curr->left) 
                curr = curr->left; // search in the left subtree of curr.
            else{
                curr->left = new TreeNode(JourneyCode, price, curr); // place it if left subtree does not exist. This insert preserves the bst property.
                break;
            }
        }
        else {
            if (curr->right) 
                curr = curr->right; // search in the right subtree of curr
            else{
                curr->right = new TreeNode(JourneyCode, price, curr); // place it if right subtree does not exist
                break;
            }
        }
    }
    // The above loop is bound to terminate since depth of the tree left to check is bounded below by 0 and is strictly decreasing.

    // update heights
    while(curr){
        curr->height = 1 + max((curr->left) ? curr->left->height: 0, (curr->right) ? curr->right->height: 0);
        curr = curr->parent;
    }
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two nodes in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int JourneyCode){
    const TreeNode *loc = getnode(JourneyCode);
    return (loc) ? loc->price: -1;
}

const TreeNode *BST::getnode(int JourneyCode){
    // You MUST use only BSTLessThan to compare two journey codes.

    // Not required, it's taken care of
    // // Check if the tree is empty.
    // if (!root)
    //     return nullptr; // the journey cannot possibly be here in the tree.
    
    TreeNode *curr = root;
    const TreeNode tmp(JourneyCode, 0); // set arbit price.

    // binary search loop to search for the JourneyCode.
    while (true){

        if (!curr) return nullptr;
        // invariant: curr is never null.

        if (*curr == tmp) return curr;

        if (BSTLessThan(curr, &tmp)) 
            curr = curr->left; // search in the left subtree of curr.
        else
            curr = curr->right; // search in the right subtree of curr.
    }
    // The above loop is bound to terminate since depth of the tree left to check is bounded below by 0 and is strictly decreasing. And we return from inside the loop as well - since we do return but no `break`.
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

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
bool BST::remove(int JourneyCode)
{

    if (!root)
        return false; // cannot delete non-existent node.
    
    const TreeNode *loc = getnode(JourneyCode);
    if (!loc)
        return false; // cannot delete non-existent node.

    
}



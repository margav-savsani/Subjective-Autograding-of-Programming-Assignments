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
        TreeNode *present = root; // This will be updated and used in the loop
        
        // Make a new Node so that we can use <
        TreeNode *newNode = new TreeNode(jrnyCode, price);
        if(present == nullptr){
            // Tree was empty earlier, just insert it at root
            root = newNode;
            newNode = root;
            root->height = 0; // Set the height of root to 0
            return true;
        }
        while(true){
            if(present->JourneyCode == jrnyCode){
                // Duplicate
                return false;
            }
            if (BSTLessThan(newNode, present)){
                if (present->left == nullptr){
                    // Found a place to insert, present->left
                    present->left = newNode; // Make a new node with null left and right and parent = present
                    newNode = present->left;
                    newNode->parent = present;
                    break;
                }
                else{
                    // Keep traversing
                    present = present->left;
                    
                }
            }
            else{
                if (present->right == nullptr){
                    // Insert at present->right 
                    present->right = newNode; // Make a new node with null left and right and parent = present
                    newNode = present->right;
                    newNode->parent = present;

                    break;
                }
                else{
                    present = present->right ;
                    
                }
            }
        }


    // We are only inserting at the leaves. So we only need to find the hieght of the present node

    while(present != nullptr){
      if(present->left == nullptr && present->right == nullptr){
        present->height = 0;
      }
      else if(present->left == nullptr){
        present->height = present->right->height + 1;
      }
      else if(present->right == nullptr){
        present->height = present->left->height + 1;
      }
      else{
       present->height = std::max(present->left->height + 1,present->right->height + 1) ;
      }
      present = present->parent;
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
          TreeNode *present = root;
        // From the root, keep iterating according to the binary tree specification: if the price is <= price of present go in the left subtree else right
        // Equal value prices are sent in the left subtree

        TreeNode *newNode = new TreeNode(jrnyCode, -1); // Create a dummy node so that we can do comparisons
        while(present != nullptr){
            if(present->JourneyCode == jrnyCode){
                    return 1;
                    // Entry found
            }
            if(BSTLessThan(newNode, present)){
                present = present->left;
            }
            else {
                present = present->right;
            }
        }
        return false; 
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



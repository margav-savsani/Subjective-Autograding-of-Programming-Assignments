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
void BST::height(TreeNode *node)
{
  int h = 0;
  while(node != NULL)
  {                      // here we are updating the height according to the addintion of the node and also checkinh the when the node the height would increase or or it would remain sam after ading the node.
    int lHeight = 0;
    if (node->left != nullptr) lHeight = node->left->height;
    int rHeight = 0;
    if (node->right != nullptr) rHeight = node->right->height;
    int maxHeight = max(lHeight,rHeight);
    h = maxHeight + 1;
    node->height = h;
    node = node -> parent;
  }
}

bool BST::insert(int jrnyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
    if (root==nullptr) {
        root = new TreeNode(jrnyCode,price);
        root->height = 1;
        return true;
     }
    if(find(jrnyCode)){// here we are inserting the elements in the tree acc to their values 
        return false;
    }
    TreeNode * x = root; 
    TreeNode * y = NULL;
    TreeNode * z = new TreeNode(jrnyCode,price);
    while( x != nullptr){
        y = x;
        if(BSTLessThan(z,x)){					// movinfg toward left of the tree
            x = x -> left; 
        }
        else{
            x = x -> right; 					// moving towards right of the tree
        }
    }
    if ( y == nullptr){
        root = z;
    }
    else if (BSTLessThan(y,z)) {
        updateBSTParentChild(z,y,false);        
    }
    else{
        updateBSTParentChild(z,y,true);
    }
    z->height = 1;
    height(y);
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
  TreeNode * x = root;
  TreeNode *n = new TreeNode(jrnyCode,0);
    while(x != nullptr){
        if(x -> getJourneyCode() == jrnyCode) {return x->getPrice();}
        else{
            if(BSTLessThan(n,x)){  // checking with predefined conditions that weater to find at the left or at the right 
                x = x -> left ;
            }
            else{
                x = x -> right; 
            }
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



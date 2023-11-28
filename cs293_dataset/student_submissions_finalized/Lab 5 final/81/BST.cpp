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
    TreeNode* new_node;
    new_node=new TreeNode(jrnyCode,price);
// Create a new node to insert
    TreeNode* x;TreeNode* y;
    x=root;
    y=nullptr;
    int i_height=0;
    while(x!=nullptr){
// Search for its place in BST
        y=x;
        if(BSTLessThan(new_node,x)) x=x->left;
        else x=x->right;
        i_height++;
    }
    x=root;
    while(i_height!=0){
  x->height=max(i_height,x->height);
  i_height--;
  if(BSTLessThan(new_node,x)) x=x->left;
        else x=x->right;
    }
// put the node in its position
    if(y==nullptr){root=new_node;}
    else if(BSTLessThan(new_node,y)) updateBSTParentChild(new_node,y,true);
    else updateBSTParentChild(new_node,y,false);
    // update the height
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
  // Implement find in BST
TreeNode* x;
TreeNode* new_node;
new_node=new TreeNode(jrnyCode,0);
    x=root;
    while(x!=nullptr){
        if(BSTLessThan(new_node,x)) x=x->left;
        else if(BSTLessThan(x,new_node)) x=x->right;
        else break;
    }
    if(x==nullptr) return -1;
    else return 1;
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



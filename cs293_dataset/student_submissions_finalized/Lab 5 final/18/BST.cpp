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
  if(root!=nullptr) {
    if(find(jrnyCode) != (-1)) return false;
    TreeNode *z= new TreeNode(jrnyCode, price);
    TreeNode *x,*y;
    y = nullptr;
    x = root;
    while(x!=nullptr){
        y=x;
        if(BSTLessThan(z, x)) {x=x->left;}
        else {x=x->right;}
    }
    z->parent=y;
    if(y==nullptr) root=z;
    else{
      bool isLeftChild=false;
      if(BSTLessThan(z,y)) isLeftChild=true;
      updateBSTParentChild(z, y, isLeftChild);
      while(y!=nullptr){
        if(BSTLessThan(z,y)) y->height_left++; //height_left is the height of the left subtree, which increases if the node is added in the left subtree of the parent
        else y->height_right++; //height_right is the height of the right subtree, which increases if the node is added in the right subtree of the parent
        y->height=max(y->height_left,y->height_right); //the height of a node is the maximum of the height of the left subtree and the height of the right subtree
        z = y;
        y = y->parent;
      }
      
    }


    return true;
  }
  TreeNode *x = new TreeNode(jrnyCode, price);
  root=x;
  return true;
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
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
  TreeNode *y = root;
  TreeNode *z = new TreeNode(jrnyCode, 10); //arbitrary price
    while(y!=nullptr && z->get_JourneyCode()!=y->get_JourneyCode()){
        if(BSTLessThan(z,y)) {
            y=y->left;
        }
        else y=y->right;
    }
  if(y!=nullptr) return y->get_price();
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



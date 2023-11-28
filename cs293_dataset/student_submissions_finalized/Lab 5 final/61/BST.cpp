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
{ // Implement insertion in BST
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.
  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  // We use "return true" below to enable compilation.  Change this as you
  // see fit. 
    TreeNode * New = new TreeNode(jrnyCode,price);
    //New->parent = nullptr;
    TreeNode * y = nullptr;
    TreeNode * x = this->root;
    while(x != nullptr){
        y = x;
        if(BSTLessThan(New,x)){
            x=x->left;
        }
        else if(BSTLessThan(x,New)){
            x=x->right;
        }
        else{break;}
    }
    if(x==nullptr){
    if( y == nullptr){
        this->root = New;
    }
    else if(BSTLessThan(New,y)){
        updateBSTParentChild(New,y,true);
    }
    else if(BSTLessThan(y,New)){
        updateBSTParentChild(New,y,false);
    }
    while(y != nullptr){
        if((y->right != nullptr)&&(y->left != nullptr)){
            y->height = max(y->left->height,y->right->height)+1;
            }
        else if(y->right == nullptr){
            y->height = y->left->height + 1;
        }
        else if(y->left == nullptr){
            y->height = y->right->height + 1;
        }
        y = y->parent;
    }
    return true;
    }
    return false;
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
    TreeNode * New = new TreeNode(jrnyCode,0);
    if(this->root == nullptr){  
        return -1;
    }
    TreeNode* x = this->root;
    while((x!= nullptr)){
        if(BSTLessThan(New,x)){x=x->left;}
        else if(BSTLessThan(x,New)){x=x->right;}
        else {return 0;}
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
{ // Implement deletion in BST
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



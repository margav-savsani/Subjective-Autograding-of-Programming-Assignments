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
{ TreeNode * n= new TreeNode(jrnyCode,price);//defining new trenode to compare
    //New->parent = nullptr;
    TreeNode * y = NULL;//to find the find the parent of node to be instructed
    TreeNode * x = root;
    while(x != NULL){
        y = x;
        if(BSTLessThan(n,x)){x=x->left;}
        else if(BSTLessThan(x,n)){x=x->right;}
        else{break;}}
    if(x==NULL){
    if( y == NULL){root = n;}
    else if(BSTLessThan(n,y)){updateBSTParentChild(n,y,true);}
    else if(BSTLessThan(y,n)){updateBSTParentChild(n,y,false);}
    while(y != NULL){
        if((y->right != NULL)&&(y->left != NULL)){y->height = max(y->left->height,y->right->height)+1;}//inserting nodes accordingly and
        else if(y->right == NULL){y->height = y->left->height + 1;}                                    //changing the heights of the nodes in the tree
        else if(y->left == NULL){y->height = y->right->height + 1;}
        y = y->parent;}
    return 1;}
    return 0;
  // Implement insertion in BST

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
{TreeNode * New = new TreeNode(jrnyCode,0);
    if(root == NULL){  // if root is empty then it will return -1
        return -1;}
    TreeNode* x =root;
    while((x!= NULL)){
        if(BSTLessThan(New,x)){x=x->left;}//finding if the value to be compared is less than or greater than value of the current node
        else if(BSTLessThan(x,New)){x=x->right;}//if value is greater than of the current node
        else {return 0;}
    }
    return -1;
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



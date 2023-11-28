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
    // if(find(jrnyCode)!=-1){
    //     return false;
    // }
    TreeNode* tra;
    TreeNode* par;
    TreeNode* nw;
    TreeNode d(jrnyCode,price);
    nw=new TreeNode(jrnyCode, price);       //creating a new treenode
    tra=root;
    par=NULL;
    while (tra != NULL){
        par=tra;
        if(BSTLessThan(&d,tra)){
            tra = tra->left;
        }
        else if(BSTLessThan(tra,&d)){
            tra = tra->right;
        }
        else{
            return false;                 //returns false if that treenode is found
        }
    }
    tra=nw;
    tra->parent=par;
    if(par==NULL){
        root=tra;
        return true;
    }
    
    updateBSTParentChild(tra,par,BSTLessThan(tra,par));

    while(tra!=root){                   //updating heights
      if((par->left==NULL || par->right==NULL)){
        par->height=1+tra->height;
      }
      else{
        int a1=tra->height;
        int b1;
        if(par->left==tra){
            b1=par->right->height;
        }
        else{
            b1=par->left->height;
        }
        
        if(a1<b1) par->height=b1+1;
        else par->height=a1+1;
      } 
      tra=par;
      par=par->parent;
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
  TreeNode* tra;
  TreeNode d(jrnyCode, 5);
  tra=root;
    while (tra != NULL){
        if(BSTLessThan(&d,tra)){
            tra = tra->left;
        }
        else if(BSTLessThan(tra, &d)){
            tra = tra->right;
        }
        else{
            return tra->getprice();         //returns price of treenode with given journey code if found
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

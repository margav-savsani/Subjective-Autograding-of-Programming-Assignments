#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


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
    TreeNode *z;
    z = new TreeNode(jrnyCode,price);
    if(find(jrnyCode)==price)
      return false;
    else{
      TreeNode *y = NULL;
      TreeNode *x = root;
      while(x!=NULL){
        y=x;
        if(BSTLessThan(z,x))
          x = x->left;
        else
          x  = x->right;
      }
      z->parent = y;
      if(y==NULL)
        root = z;
      else {
        if(BSTLessThan(z,y)){
          y->left = z;
          TreeNode *T=y->left;
          if(y->right==NULL){
            while(T->parent!=NULL && (T->parent)->height<T->height+1){
              (T->parent)->height=T->height+1;
              T=T->parent;
            }
          }
        }
        else{
          y->right = z;
          TreeNode *T=y->right;
          if(y->left==NULL){
            while(T->parent!=NULL && (T->parent)->height<T->height+1){
              (T->parent)->height=T->height+1;
              T=T->parent;
            }
          }
        }
      }
      return true; 
    }
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
  TreeNode *x = root;
  TreeNode *z;
  z = new TreeNode(jrnyCode,1);

  while(x!=NULL){
    if(BSTLessThan(z,x)){

      if(x->left!=NULL)
        x = x->left;
      else
        break;
    }
    else if(BSTLessThan(x,z)){

      if(x->right!=NULL)
        x = x->right;
      else
        break;
    }
    else
       return x->getprice();
      
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



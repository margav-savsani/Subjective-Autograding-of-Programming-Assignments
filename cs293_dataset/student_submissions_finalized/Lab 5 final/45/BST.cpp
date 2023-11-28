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

  /* solution-1st check if root is null,if it is,then isert node.
            -now take x=root,check if T(node to insert) is less or more than x,
            -if it is less,do x=x->left,and continue this till u get x->left / x-right is null.
            -now insert a node
            for heights-
                -first take y=inserted node and set its heigt to 0.
                now do a while loop,y=y->parent and y->height=1+max(left->height,right->height)
                if y->parent=null, means y=root, now break.
  */
  TreeNode* T=new TreeNode(jrnyCode,price);
  TreeNode* inserted;
  if(find(jrnyCode)==0){ return false;}

  else{
    if(root==nullptr){
      root=T;
      inserted=root;
    }
    else{
      TreeNode* x=root;
      while(true){
        if(BSTLessThan(x,T)){
          if(x->right==nullptr){
            x->right=T;
            x->right->parent=x;
            inserted=x->right;
            break;
          }
          else{
            x=x->right;
          }
        }
        else if(BSTLessThan(T,x)){
          if(x->left==nullptr){
            x->left=T;
            x->left->parent=x;
            inserted=x->left;
            break;
          }
          else{
            x=x->left;
          }
        }
      }
    }
  }

  TreeNode* y=inserted;
  y->height=0;
  y=y->parent;
  while(y!=nullptr){
    if(y->left==nullptr and y->right==nullptr){y->height=0;}
    else if(y->left!=nullptr and y->right==nullptr){y->height=1+y->left->height;}
    else if(y->left==nullptr and y->right!=nullptr){y->height=1+y->right->height;}
    else if(y->left!=nullptr and y->right!=nullptr)
    {
      y->height=1+max(y->left->height,y->right->height);
    }
    y=y->parent;
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

  TreeNode* x=root;
  TreeNode* y=new TreeNode(jrnyCode,1);
  while(x!=NULL and (BSTLessThan(x,y) or BSTLessThan(y,x))){
      if(BSTLessThan(y,x)){
          x=x->left;
      }
      else{
          x=x->right;
      }
  }
  if(x!=NULL and !(BSTLessThan(x,y) or BSTLessThan(y,x))){
      return 0;
  }
  else{return -1;}
  
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



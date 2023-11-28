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
int heightofNode(TreeNode *A){
  if(A == NULL){return 0;}
  else if(A->left == NULL  && A->right == NULL){return 0;}
  else{
    return 1+max(heightofNode(A->left),heightofNode(A->right));
  }
}

bool BST::insert(int jrnyCode, int price){
    bool leftinsert = false;
    bool rightinsert = false;
    TreeNode *x = root;
    TreeNode *y = NULL;
    TreeNode *z = new TreeNode(jrnyCode,price);
    if(root == NULL){
      root = z;
      return true;
    }
      while(x != NULL){
        y = x;
        if(BSTLessThan(x,z)){
            x = x->right;
        }
        else if(BSTLessThan(z,x)){
          x = x->left;
        }
        else{
          return false;
        }
      }
        z->parent = y;
        if(y == NULL){
          root = z;
        }
        else if(BSTLessThan(z,y)){
          updateBSTParentChild(z,y,true);
        }
        else{
          updateBSTParentChild(z,y,false);
        }
        while(z != NULL){
          z->height = heightofNode(z);
          z = z->parent;
        }
  return true;
}
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
 

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  if(root == NULL){
    return -1;
  }
  TreeNode *x;
  TreeNode *y;
  x = root;
  y = new TreeNode(jrnyCode,0);
  while(x != NULL){
    if(BSTLessThan(x,y)){
      x = x->right;
    }
    else if(BSTLessThan(y,x)){
      x = x->left;
    }
    else{
      int a;
      a = x->Price();
      return a;
    }
  }
  return -1;
}
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.


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


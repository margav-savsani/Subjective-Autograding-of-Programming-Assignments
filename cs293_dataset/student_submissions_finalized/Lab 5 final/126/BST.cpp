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
    int length=0;    
    TreeNode *ins=new TreeNode(jrnyCode, price);
    ins->left=nullptr;
    ins->right=nullptr;
    TreeNode *y=nullptr; 
    TreeNode *x=root;
    while(x!=nullptr){
        y=x;
        if(BSTLessThan(ins, x)){
            x->height++;//updating height before going to the next node
            x=x->left;
        }  
        else{
            x->height++;
            x=x->right;
        }
    }
    ins->parent=y;
    if(y==nullptr){
        root=ins;
    }
    //instead of the following 4 lines, x=ins should work
    else if(BSTLessThan(ins,y))
        y->left=ins;
    else
        y->right=ins;
    return true;
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

int BST::find(int jrnyCode1)
{
  TreeNode *y=new TreeNode(jrnyCode1,0);
  TreeNode *x=root;
    while(x!=nullptr){
        if((BSTLessThan(x,y)==false)&&((BSTLessThan(y,x))==false)){
            return x->showPrice();
        }
        else if((BSTLessThan(y,x))){
            x=x->left;
        }
        else{
            x=x->right;
        }
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



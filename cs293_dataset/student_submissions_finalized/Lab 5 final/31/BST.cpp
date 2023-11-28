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
  TreeNode* node = new TreeNode(jrnyCode,price);
    TreeNode *y, *x;
    y=NULL;
    x=root;
    while(x!=NULL){
        y=x;
        if(BSTLessThan(node, x)){
            x=x->left;
        }
        else x=x->right;
    }

    if(y==NULL){
        root=node;
    }
    else if(BSTLessThan(node,y)){
        updateBSTParentChild(node,y,true);
    }
    else updateBSTParentChild(node,y,false);

    //update height of all node in the path of inserted node to root
    updateHeightAlongPath(node);

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

bool BST::updateHeightAlongPath(TreeNode* node){
    TreeNode *y, *x;
    y=NULL;
    x=node;
    bool k=false;
    while(x!=NULL){     //iteratively updates height of nodes from given 'node' to root
        y=x;
        x=x->parent;
        if(y->left==NULL && y->right==NULL){
            y->height=0;
        }
        else if(y->left==NULL){
            y->height=(y->right)->height + 1;
        }
        else if(y->right==NULL){
            y->height=(y->left)->height + 1;
        }
        else if((y->right)->height>=(y->left)->height){
            y->height=(y->right)->height + 1; 
        }
        else if((y->left)->height>(y->right)->height){
            y->height=(y->left)->height + 1;
        }
    }
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST
int BST::find(int jrnyCode)
{
  // Implement find in BST
    TreeNode *node = new TreeNode(jrnyCode,0);
    TreeNode *x=root;
    while(x!=NULL && jrnyCode!=x->getJrnyCode()){
        if(BSTLessThan(node,x)){
            x=x->left;
        }
        else x=x->right;
    } 

    if(x==NULL){
        return -1;
    }
    else {
      return x->getprice();
    }

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  //return -1;
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



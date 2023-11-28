#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif
bool BST::insert(int jrnyCode, int price){
  TreeNode * x=root;
  TreeNode * y=nullptr;
  TreeNode * z=new TreeNode(jrnyCode,price);
  if(root==nullptr){root=z;z->height=1; return true;}
    while(x!=nullptr){
      y=x;
      if(BSTLessThan(z,x)){x=x->left;}
      else {x=x->right;}
    }
    TreeNode * K=y;
    z->parent=y;
    if(y==nullptr){
        root=z;
    }
    else if(BSTLessThan(z,y)){
      y->left=z;
    }
    else{
      y->right=z;
    }
    while(z->parent!=nullptr && z->parent->height < z->height +1 ){
          z->parent->height=z->height+1;
          z=z->parent;
    }
    return true;
  }


int BST::find(int jrnyCode){
  
  TreeNode * z=new TreeNode(jrnyCode,0);
  TreeNode * s;
    s=root;
    while(s!=NULL){
        if(BSTLessThan(z,s)){
          s=s->left;
        }
        else if(BSTLessThan(s,z)){
          s=s->right;
        }
        else{
            return s->getprice();
        }
    }
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
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



#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include<algorithm>
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
  TreeNode* newnode;
  newnode = new TreeNode(jrnyCode,price);
  TreeNode* y=NULL;
  TreeNode* x=root;
  while(x!=NULL){
    y=x;
    if(BSTLessThan(newnode,x)){
      x=x->left;
    }
    else{x=x->right;}
  }
  if(y==NULL){root=newnode;}
  else if(BSTLessThan(newnode,y)){
    updateBSTParentChild(newnode,y,true);
  }
  else {
    updateBSTParentChild(newnode,y,false);
  }
  TreeNode* node=newnode->parent;
  while(node!=NULL){
    if(node->left==NULL&&node->right!=NULL){node->height=1+node->right->height;}
    else if (node->right==NULL&&node->left!=NULL){node->height=1+node->left->height;}
    else {node->height=1+max(node->left->height,node->right->height);}
    node=node->parent;
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
  TreeNode* newnode;
  newnode=new TreeNode(jrnyCode,71);
  TreeNode* node=root;
  while(node!=NULL){
    if(BSTLessThan(newnode,node)){node=node->left;}
    else if(BSTLessThan(node,newnode)){node=node->right;}
    else{return 1;}
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


  bool found=false;
  TreeNode *node=root;
  TreeNode *temp;temp=new TreeNode(jrnyCode,31);
   // TreeNode *temproot=root;
  while(node!=NULL){
    if(BSTLessThan(node,temp)) node=node->right;
    else if(BSTLessThan(temp,node)) node=node->left;
    else {found=true;break;}
  }
  delete temp;
  if(!found){return false;}
  TreeNode *y,*x,*z;
  if(node->left==NULL || node->right==NULL)
  {
    y=node;
  }
  else{
      y=treePred(node);
  }
  z=y->parent;
  if(y->left!=NULL){
      x=y->left;
  }
  else{
      x=y->right;
  }
  if(x!=NULL){
      x->parent=y->parent;
  }
  if(y->parent==NULL){
      root=x;
  }
  else if(y==y->parent->left){
      y->parent->left=x;
  }
  else{
      y->parent->right=x;
  }
  if (y!=node){
      node->updateValues(y->getJrnyCode(),y->getPrice());
  }
  return true;
  while(z!=NULL){
    if(z->left==NULL&&z->right!=NULL){z->height=1+z->right->height;}
    else if (z->right==NULL&&z->left!=NULL){z->height=1+z->left->height;}
    else {z->height=1+max(z->left->height,z->right->height);}
    z=z->parent;
  }
}


TreeNode* BST::treePred(TreeNode *node){
    TreeNode *pred=node->left;
    while(pred->right!=NULL){
        pred=pred->right;
    }
    return pred;
}

#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

bool BST::insert(int jrnyCode, int price)
{
    if(root==NULL){
      root = new TreeNode(jrnyCode,price);                    
      return true;
    } 
    TreeNode *x=new TreeNode(jrnyCode,price);
    TreeNode *y=NULL;
    TreeNode *r=root,*a,*c;
    int b;

    while(r!=NULL){
      if(BSTEqualTo(r,x))return false;
      else if(BSTLessThan(x,r)){
        y=r;
        b=1;
        r=r->left;
      }
      else{
        y=r;
        b=2;
        r=r->right;
      }
    }
  if(b==1) updateBSTParentChild(x,y,true);
  else if(b==2) updateBSTParentChild(x,y,false);
  x->height=0;
  while(x->parent!=NULL){
      a=x;
      x=x->parent;
      if(x->left!=NULL && x->right!=NULL){
        c=x->left;
        if(c==a)c=x->right;
        if(a->height<=c->height)break;
        else x->height++;
      } 
      else x->height++;
  }
  return true;
}

int BST::find(int jrnyCode)
{
  TreeNode *x=new TreeNode(jrnyCode,0);
  TreeNode *r=root;
    if(r==NULL)return false;
    while(r!=NULL){
        if(BSTEqualTo(r,x)) return r->getprice();
        else if(BSTLessThan(x,r)){
            r=r->left;   
        }
        else{
            r=r->right;
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

TreeNode* successor(TreeNode* r){
    r=r->right;
    while(r->left!=NULL){
        r=r->left;
    }
    return r; 
} 

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
  TreeNode *x=new TreeNode(jrnyCode,0);
  TreeNode *r=root,*y=NULL;int b=0;
  if(r==NULL)return false; 
  while(r!=NULL){
    if(BSTEqualTo(r,x))break;
    else if(BSTLessThan(x,r)){
      b=1;
      y=r;
      r=r->left;   
    }
    else{
      b=2;
      y=r;
      r=r->right;
    }
  } 
  if(r==NULL)return false;

  if(r->left==NULL && r->right==NULL){
    if(b==0)root=NULL;
    if(b==1) updateBSTParentChild(NULL,y,left);
    else if(b==2) updateBSTParentChild(NULL,y,right);
    return true;
  }
  if(r->left==NULL && r->right!=NULL){
    if(b==0)root=r->right;updateBSTParentChild(root,NULL,true);
    if(b==1) updateBSTParentChild(r->right,y,true);       
    else if(b==2) updateBSTParentChild(r->right,y,false);
    return true;
  }
  if(r->left!=NULL && r->right==NULL){
    if(b==0)root=r->left;updateBSTParentChild(root,NULL,true);
    if(b==1) updateBSTParentChild(r->left,y,true);       
    else if(b==2) updateBSTParentChild(r->left,y,false);
    return true;
  }
  if(r->left!=NULL && r->right!=NULL){
    TreeNode *l=successor(r);
    remove(l->getjourneycode());
    if(b==0){
      root=l;
      updateBSTParentChild(r->left,root,true);
      updateBSTParentChild(r->right,root,false);
      return true;
    }
    updateBSTParentChild(r->left,l,true);
    updateBSTParentChild(r->right,l,false);
    if(b==1)updateBSTParentChild(l,y,true);
    else if(b==2)updateBSTParentChild(l,y,false);
    return true;
  }
  return false;
}

//dont forget to implement height functionality here


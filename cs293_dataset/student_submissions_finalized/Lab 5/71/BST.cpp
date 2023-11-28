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
  if(find(jrnyCode)!=-1){
    return false;
  }
  TreeNode *to_be_insert=new TreeNode(jrnyCode,price);
  if(root==nullptr){
    root=to_be_insert;
  }
  else{
    TreeNode *cur=root;
    bool done=false;
    while(!done){
      bool left=BSTLessThan(to_be_insert,cur);
      if(left){
        if(cur->left==nullptr){
          updateBSTParentChild(to_be_insert,cur,left);
          done=true;
        }
        else cur=cur->left;
      }
      else{
        if(cur->right==nullptr){
          updateBSTParentChild(to_be_insert,cur,!left);
          done=true;
        }
        else cur=cur->right;
      }
    }
    cur=to_be_insert->parent;
    while(cur!=nullptr){
      if(cur->left!=nullptr && cur->right!=nullptr){
        cur->height=1+max(cur->left->height,cur->right->height);
        }
      else if(cur->left==nullptr && cur->right!=nullptr){
        cur->height=1+cur->right->height;
      }
      else{
        cur->height=1+cur->left->height;
      }
      cur=cur->parent;
    }
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
  TreeNode *to_find=new TreeNode(jrnyCode,0);

  if(root==nullptr) return -1;

  bool found=false;
  TreeNode *cur=root;
  while(!found){
    bool side=BSTLessThan(to_find,cur);
    if(!side){
      TreeNode *temp=new TreeNode(jrnyCode-1,0);
      if(BSTLessThan(temp,cur)) found=true;
      else{
        if(cur->right!=nullptr) cur=cur->right;
        else return -1;
      }
    }
    else{
      if(cur->left!=nullptr) cur=cur->left;
      else return -1;
    }
  }
  return jrnyCode;
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



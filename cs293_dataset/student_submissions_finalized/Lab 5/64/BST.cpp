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
  TreeNode* node_insert = new TreeNode(jrnyCode, price);
  if(find(jrnyCode!=-1)){
    return false;
  }else{
      TreeNode* y = nullptr;
      TreeNode* x = root;
      while(x!=nullptr){
        y=x;
        if(BSTLessThan(node_insert,x)){
          x->height+=1;
          x=x->left;
        }else if(!(BSTLessThan(node_insert,x))){
          x->height+=1;
          x=x->right;
        }else{
          return false;
        }
      }
      if(y==nullptr){
        root=node_insert;
        root->height=1;
      }else if(BSTLessThan(node_insert, y)){
        y->height+=1;
        y->left=node_insert;
        return true;
      }else if(!(BSTLessThan(node_insert, y))){
        y->height+=1;
        y->right=node_insert;
        return true;
      }else{
        return false;
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
  TreeNode* x = new TreeNode(jrnyCode, -1);
  while(root!=NULL && root->JourneyCode != jrnyCode){
    if(BSTLessThan(root, x)){
      root=root->right;
    }else{
      root=root->left;
    }
  }
  if(root==nullptr){
    return -1;
  }else if(root->JourneyCode==jrnyCode){
    return root->price;
  }else{
    return -1;
  }

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



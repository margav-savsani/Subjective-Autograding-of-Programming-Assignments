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
void BST::updateNodes(TreeNode* node,bool IsInsert){
  TreeNode* curr;
  if (IsInsert){  
    curr = node;  
    while( curr!= nullptr){
      if (curr->left != nullptr && curr->right != nullptr ) 
        curr->height = (curr->right->height > curr->left->height) ? curr->right->height + 1 : curr->left->height + 1;
      else if (curr->left == nullptr)  curr->height = curr->right->height + 1;
      else if (curr->right == nullptr)  curr->height = curr->left->height + 1;
      curr = curr -> parent;
    }
  }
  
}

bool BST::deleteNode(TreeNode* node){
  TreeNode* parent = node->parent;
  if (node->left == nullptr && node->right == nullptr){
    if (BSTLessThan(node,parent)) parent->left =  nullptr;
    else parent->right= nullptr;
    node = nullptr;
  }
  else if (node->left==nullptr){
    if (BSTLessThan(node,parent)) parent->left =  node->right;
    else parent->right= node->right;
    node->right->parent = parent;
    node = nullptr;
  }
  else if (node->right==nullptr){
    if (BSTLessThan(node,parent)) parent->left =  node->left;
    else parent->right= node->left;
    node->left->parent = parent;
    node = nullptr;
  }
  else{
    
  }
}

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
  TreeNode* newnode = new TreeNode(jrnyCode,price);
  TreeNode* child = root;
  TreeNode* parent = nullptr;
  while (child != nullptr ){
    if (BSTLessThan(child,newnode)) {
      parent = child ;
      child =child->right;
    }
    else {
      parent = child;
      child = child ->left;
    }
  }
  if (child == nullptr){
    if (BSTLessThan(parent,newnode)) parent->right=newnode;
    else parent->left=newnode;
    newnode->parent=parent;
    updateNodes(parent,true);
    return true;
  }

  return false;
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
  TreeNode *node = new TreeNode(jrnyCode,-1);
  TreeNode* child = root;
  TreeNode* parent = nullptr;
  while (child != nullptr){
    if (BSTLessThan(child,node)){
      parent =  child;
      child = child ->right;
    }
    else if (BSTLessThan(node,child)){
      parent = child ;
      child = child ->left;
    }
    else {
      return -1;
    }
  }
  return 0;
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
  TreeNode *node = new TreeNode(jrnyCode,-1);
  TreeNode* child = root;
  TreeNode* parent = nullptr;
  while (child != nullptr){
    if (BSTLessThan(child,node)){
      parent =  child;
      child = child ->right;
    }
    else if (BSTLessThan(node,child)){
      parent = child ;
      child = child ->left;
    }
    else {
      deleteNode(child);
      return true;
    }
  }
  return false;
}



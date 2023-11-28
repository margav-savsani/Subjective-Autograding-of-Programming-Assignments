#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

//Returns true on successful insertion, false otherwise
bool BST::insert(int jrnyCode, int price)
{
  //Exceptional case if BST is empty
  if (root==nullptr){
    root = new TreeNode(jrnyCode,price);
    root->height = 1;
    return true;
  }

  //Initialize variables to run the search loop to insert
  TreeNode *node = new TreeNode(jrnyCode,price);
  TreeNode *y = root;
  TreeNode *x = root;
  bool leftChild = false;
  while(x!=nullptr){
    y = x;
    if (BSTLessThan(node,x)){
      leftChild=true;
      x=x->left;
    }
    else if (BSTLessThan(x,node)){
      leftChild=false;
      x=x->right;
    }
    else{
      return false;
    }
  }
  //Insert the node as child of y
  updateBSTParentChild(node, y, leftChild);
  //Update the heights
  updateHeight(node);
  return true;
}

//Small function to updateheights of all ancestors of leaf
bool BST::updateHeight(TreeNode* leaf){
  TreeNode *head = leaf;
  while(head!=nullptr){
    int left, right;
    if(head->left!=nullptr){
      left = head->left->height;
    }
    else{
      left = 0;
    }

    if ( head->right!=nullptr){
      right = head->right->height;
    }
    else{
      right = 0;
    }

    if(left>right){
      head->height=1+left;
    }
    else{
      head->height=1+right;
    }
    head = head->parent;
  }
  return true;
}

//Returns price if found, -1 otherwise
int BST::find(int jrnyCode)
{
  if (root==nullptr){
    return -1;
  }
  TreeNode *temp = new TreeNode(jrnyCode,0);
  TreeNode*x = root;
  while(x!=nullptr){
    if ( BSTLessThan(temp,x) ){
      x = x->left;
    }
    else if (BSTLessThan(x,temp)) {
      x = x->right;
    }
    else{
      return x->get_price();
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



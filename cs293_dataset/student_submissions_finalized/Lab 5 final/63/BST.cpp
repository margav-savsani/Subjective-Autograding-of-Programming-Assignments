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
  TreeNode* comp = new TreeNode(jrnyCode, price);
  TreeNode * A = root;
  if (root == nullptr){
    root = new TreeNode(jrnyCode, price);
    return 1;
  }
  while (true){
    if (!BSTLessThan(A, comp) && !BSTLessThan(comp, A)){ // values in the node should be unique
      delete comp;
      return 0;
    }
    else if (BSTLessThan(A, comp)){
      if (A->right != nullptr){
        A = A->right;
        continue;
      }
      TreeNode * B = new TreeNode(jrnyCode, price);      
      updateBSTParentChild(B, A, false);
      A = A->right;
      break;
    }
    else if (BSTLessThan(comp, A)){
      if (A->left != nullptr){
        A = A->left;
        continue;
      }
      TreeNode * B = new TreeNode(jrnyCode, price);
      updateBSTParentChild(B, A, true);
      A = A->left;
      break;
    }
  }
  delete comp;
  while(A->parent != nullptr){
    A = A->parent;
    int hl = getheight(A, -1);
    int h = getheight(A, 0);
    int hr = getheight(A, 1);
    if (hr > hl){
      A->height = hr+1;
    }
    else {
      A->height = hl+1;
    }
  }
  return 1;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  TreeNode *A = root, *comp = new TreeNode(jrnyCode, 0);
  
  while (true){
    if (!(BSTLessThan(comp, A)) && !(BSTLessThan(A, comp))){
      return A->get_price();
    }
    else if (BSTLessThan(comp, A)){
      if (A->left == nullptr){
        return -1;
      }
      A = A->left;
      continue;
    }
    else if (BSTLessThan(A, comp)){
      if (A->right == nullptr){
        return -1;
      }
      A = A->right;
      continue;
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
  bool isleft = 0;
  TreeNode *A = root;
  TreeNode *comp = new TreeNode(jrnyCode, 0);
  while(true){
     if (!(BSTLessThan(comp, A)) && !(BSTLessThan(A, comp))){
      break;
    }
    else if (BSTLessThan(comp, A)){
      if (A->left == nullptr){
        return 0;
      }
      A = A->left;
      isleft = 1;
      continue;
    }
    else if (BSTLessThan(A, comp)){
      if (A->right == nullptr){
        return 0;
      }
      A = A->right;
      isleft = 0;
      continue;
    }
  }
  delete comp;
  // cout << A->get_code() << endl;
  TreeNode *B = A;
  TreeNode *C = nullptr;
  if (A->left == nullptr){
    while (B->right != nullptr){
      B = B->right;
    }
    if (B->left != nullptr){
      updateBSTParentChild(B->left, B->parent, false);
      C = B->left;
    }
    else { 
      // cout << "hi " << B->parent->get_code() << endl;
      updateBSTParentChild(nullptr, B->parent, true);
      // cout << "hi1 " << B->parent->left << endl;
      C = B->parent;
    }
  }
  else {
    while (B->left != nullptr){
      B = B->left;
      // cout << B << endl;
    }
    if (B->right != nullptr){
      updateBSTParentChild(B->left, B->parent, true);
      C = B->right;
    }
    else if (B->parent != nullptr){
      updateBSTParentChild(nullptr, B->parent, true);
      C = B->parent;
    }
  }
  //cout << C->left->get_code() << endl;
  // cout << B->get_code() << endl;
  // cout << A->get_code() << " " << B->get_code() << " " << C->get_code() << endl;
  // if (C->left != nullptr || C->right != nullptr){
    
  // }
  if (A == root){
    root = B;
    updateBSTParentChild(B, nullptr, true);
    updateBSTParentChild(A->left, B, true);
    updateBSTParentChild(A->right, B, false);
  }
  else if (A == B){
    updateBSTParentChild(nullptr, A->parent, isleft);
  }
  else if (A != B){
    updateBSTParentChild(B, A->parent, isleft);
    updateBSTParentChild(A->left, B, true);
    updateBSTParentChild(A->right, B, false);
    B->height = A->height;
  }
  delete A;
  A = C;
  //cout << C->left->get_code() << endl;
  if (A == nullptr){
    root = nullptr;
    return 1;
  }
  else if (A->parent == nullptr){
    int h = getheight(A, 0);
    int hl = getheight(A,-1);
    int hr = getheight(A, 1);
    A->height = hl+1;
    if (hr >hl){
      A->height = hr+1;
    }
  }
  while(A->parent != nullptr){    // keep updating height and find the imbalance
    A = A->parent;
    int hl = getheight(A, -1);
    int h = getheight(A, 0);
    int hr = getheight(A, 1);
    if (hr > hl){
      A->height = hr+1;
    }
    else {
      A->height = hl+1;
    }
  }
  return true;
}



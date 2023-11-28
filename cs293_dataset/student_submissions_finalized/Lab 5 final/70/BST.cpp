#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

//updates the height of the tree from the given node till the root
void BST::updateHeight(TreeNode* node){
  TreeNode* newtempc = NULL;
  TreeNode* newtempn = node;
  while(newtempn!=nullptr){
    newtempc = newtempn;
    if(newtempc->left==nullptr && newtempc->right==nullptr){  //node to be updated is a leaf
      newtempc->height = 1;
    }
    else if(newtempc->left==nullptr && newtempc->right!=nullptr){   //node to be updated has only right child
      newtempc->height = newtempc->right->height + 1;
    }
    else if(newtempc->left!=nullptr && newtempc->right==nullptr){   //node to be updated has only left child
      newtempc->height = newtempc->left->height + 1;
    }
    else{   //node to be updated has both left and right child
      newtempc->height = max(newtempc->left->height, newtempc->right->height) + 1;
    }
    newtempn = newtempn->parent;
  }
}


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
  TreeNode* node2b = new TreeNode(jrnyCode, price);
  TreeNode* tempp = NULL;
  TreeNode* tempn = root;
  while(tempn != nullptr){
    tempp = tempn;
    if (BSTLessThan(node2b, tempn)){
      tempn = tempn->left;
    }
    else{
      tempn = tempn->right;
    }
  }
  node2b->parent = tempp;
  if(tempp == nullptr){
    root = node2b;
  }
  else if(BSTLessThan(node2b, tempp)){
    tempp->left = node2b;
  }
  else{
    tempp->right = node2b;
  }
  //Height update
  updateHeight(node2b);
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
  TreeNode* tempn = root;
  TreeNode* disposable = new TreeNode(jrnyCode, 0);
  while(tempn!=nullptr){
    if(BSTLessThan(disposable, tempn)){
      tempn = tempn->left;
    }
    else if(BSTLessThan(tempn, disposable)){
      tempn = tempn->right;
    }
    else break;
  }
  if(tempn == nullptr) return -1;
  return tempn->getPrice();
}
//Finds the successor of the given node and returns it
TreeNode* BST::successor(TreeNode* node){
    if(find(node->getJourneyCode())==-1) return NULL;
    if(node->right!=nullptr){
        node = node->right;
        while(node->left!=nullptr){
            node = node->left;
        }
        return node;
    }
    TreeNode* temp;
    temp = node->parent;
    while(temp!=nullptr && node==temp->right){
        node = temp;
        temp = temp->parent;
    }
    return temp;
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
  if(find(jrnyCode)==-1) return false;
  TreeNode* tempn = root;
  TreeNode* disposable = new TreeNode(jrnyCode, 0);
  while(tempn!=nullptr){
    if(BSTLessThan(disposable, tempn)){
      tempn = tempn->left;
    }
    else if(BSTLessThan(tempn, disposable)){
      tempn = tempn->right;
    }
    else break;
  }
  TreeNode* node = new TreeNode(0,0);
  TreeNode* x = new TreeNode(0,0);
  if(tempn->left==nullptr || tempn->right==nullptr){
      node = tempn;
  }
  else{
      node = successor(tempn);
  }
  if(node->left!=nullptr){
      x = node->left;
  }
  else{
      x = node->right;
  }
  if(x!=nullptr){
      x->parent = node->parent;
  }
  if(node->parent==nullptr){
      root = x;
  }
  else if(node == node->parent->left){
      node->parent->left = x;
  }
  else{
      node->parent->right = x;
  }
  if(node!=tempn){
      tempn->setPrice(node->getPrice());
      tempn->setJourneyCode(node->getJourneyCode());
  }
  if(x!=nullptr){
    updateHeight(x);
  }
  else{
    updateHeight(node->parent);
  }
  return true;
}



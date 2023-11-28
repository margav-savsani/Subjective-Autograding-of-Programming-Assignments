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
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;

  TreeNode *insertion_node = new TreeNode(jrnyCode, price);
  insertion_node->parent=nullptr;
  insertion_node->height=0;
  //cout << "nodes initalized" << endl;
  while (currNode != nullptr) {
    //cout << "in while loop"<< endl;
    if (*currNode < *insertion_node) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (*insertion_node < *currNode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      currNode->height -= 1;
      return false;
    }
  }
  if(parentOfCurrNode==nullptr){
    root=insertion_node;
    root->height = 0;
    //cout << "root assigned" << endl;
    return true;
  }
  insertion_node->parent=parentOfCurrNode;
  if(*parentOfCurrNode<*insertion_node){
    parentOfCurrNode->right=insertion_node;
  }
  else{
    parentOfCurrNode->left=insertion_node;
  }
  while(parentOfCurrNode!=nullptr){
    if(parentOfCurrNode->left==nullptr){
      parentOfCurrNode->height= parentOfCurrNode->right->height + 1;
    }
    else if(parentOfCurrNode->right==nullptr){
      parentOfCurrNode->height = parentOfCurrNode->left->height + 1;
    }
    else{
      parentOfCurrNode->height = max(parentOfCurrNode->right->height, parentOfCurrNode->left->height) + 1;
    }
    parentOfCurrNode = parentOfCurrNode->parent;
  }

  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{  
  TreeNode *find_node = new TreeNode(jrnyCode, 0);
  TreeNode *curr_node = root;
  if(curr_node==nullptr){
    return -1;
  }
  //cout << "here" << endl;
  while (*curr_node<*find_node || *find_node<*curr_node){
    //cout << "bah" << endl;
    if(*curr_node<*find_node){
      curr_node=curr_node->right;
    }
    else if(*find_node<*curr_node){
      curr_node=curr_node->left;
    }

    if(curr_node==nullptr){
      return -1;
    }

  }
  //cout << "about to return" << endl;
  return curr_node->height;

  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
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



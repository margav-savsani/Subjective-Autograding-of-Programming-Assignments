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
        
      TreeNode *currNode = root;
      TreeNode *parentNode = nullptr;

      TreeNode *insert ;
      insert = new TreeNode(jrnyCode,price);
    
    int i = -1;

      while(currNode != nullptr){
        if(BSTLessThan(insert,currNode)){
            // Increasing height when the node to be inserted traverses through the curent node.
          currNode->parent = parentNode;
          parentNode = currNode;
          currNode = currNode->left;
            i = 1;
        }
        else if(BSTLessThan(currNode,insert)){
          parentNode = currNode;
          currNode = currNode->right;
            i = 0;
        }
        else return false;
      }
    
    
    
    
    if(i == 1){
        parentNode->left = new TreeNode(jrnyCode,price);
        parentNode->left->parent = parentNode;
        i = -1;
    }
    
    else if(i == 0){
        parentNode->right = new TreeNode(jrnyCode,price);
        parentNode->right->parent = parentNode;
        i = -1;
    }
    
    else{
        root = new TreeNode(jrnyCode,price);
    }

    // if(currNode != nullptr){
    //   currNode->parent = parentNode;
    // }
    
    TreeNode *z = nullptr;
    if(parentNode != nullptr){
      parentNode->height = 1+max(getHeight(parentNode->left),getHeight(parentNode->right)); //y
      z = parentNode->parent;
        if(z != nullptr){
          z->height = 1+max(getHeight(z->left),getHeight(z->right));
        }
    }
    
    while(z != nullptr){
      currNode = parentNode;
      parentNode = z;
      z = parentNode->parent;
      if(z != nullptr){   // increasing the height while travelling backward.
        z->height = 1+max(getHeight(z->left),getHeight(z->right));
      }
    }
  
    
    
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
    
  TreeNode *currNode = root;
  TreeNode *parentNode = nullptr;

  TreeNode *insert;
  insert = new TreeNode(jrnyCode,-1);

  int i = -1;

  while(currNode != nullptr){
    if(currNode->jrnyC() == jrnyCode){
      return currNode->prc();
    }
    else if(BSTLessThan(insert,currNode)){
      parentNode = currNode;
      currNode = currNode->left;
      i = 1;
    }
    else if(BSTLessThan(currNode,insert)){
      parentNode = currNode;
      currNode = currNode->right;
      i = 0;
    }
    else return -1;
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



#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif


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
  TreeNode* SearchNode = new TreeNode(jrnyCode,0);
  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.

	if(root==NULL) return -1;
	
	if(BSTLessThan(SearchNode,root)){
    BST T1(root->left,perComparisonCost,perParentChildUpdateCost);
    return T1.find(jrnyCode);
	}
  else if(BSTLessThan(root,SearchNode)){
    BST T2(root->right,perComparisonCost,perParentChildUpdateCost);
    return T2.find(jrnyCode);
  }
  else{
    return root->getPrice(); //How to extract price? Its inaccessible.
  }
}


//This function update shortestPathLength and LongestPathLength
//by iterating from given TreeNode all the way to the root
//by updating all the nodes along the way.
//We use the recursive definition but iterative implementation
void BST::updateHeights(TreeNode* parentOfCurrNode){
  while(parentOfCurrNode!=nullptr){
      int heightL, heightR;
      if(parentOfCurrNode->right == nullptr){
        heightR = 1;
      } 
      else{
        heightR = 1 + parentOfCurrNode->right->height;
      }
      if(parentOfCurrNode->left == nullptr){
        heightL = 1;
      } 
      else{
        heightL = 1 + parentOfCurrNode->left->height;
      }

      parentOfCurrNode->height = max(heightL,heightR);
      parentOfCurrNode = parentOfCurrNode->parent;
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
  TreeNode* SearchNode = new TreeNode(jrnyCode,price);
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
    
  while (currNode != nullptr) {
    if (BSTLessThan(currNode, SearchNode)){
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (BSTLessThan(SearchNode, currNode)){
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }

  if(parentOfCurrNode == nullptr){
    root = new TreeNode(jrnyCode,price);
  }
  else{
    if(BSTLessThan(parentOfCurrNode, SearchNode)){
      parentOfCurrNode->right = new TreeNode(jrnyCode, price);
      parentOfCurrNode->right->parent = parentOfCurrNode;
    }
    else{
      parentOfCurrNode->left = new TreeNode(jrnyCode, price);
      parentOfCurrNode->left->parent = parentOfCurrNode;
    }

    //update the entire path upto root
    updateHeights(parentOfCurrNode);    
  }
  return true;
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



#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// Also keeping in mind that no two nodes can have the same
// journey code
int BST::find(int jrnyCode){

  // Creating a new node named "SearchNode" containing the journey code
  // to be searched along with price set to some value(say 0), as the price
  // doesn't affect our code, as comparing journeycodes would itself suffice.
  // This is in accordance to the assumption, that no two nodes have the 
  // same journey code.  
  TreeNode* SearchNode = new TreeNode(jrnyCode,0);

  // Current Node is set to root, we start iterative search for the required node
  // by comparing the currNode with the SearchNode in every iteration and accordingly
  // chosing which path to follow down
  TreeNode *currNode = root;
    
  // Exit the looop when currNode is nullptr, this means that currNode travelled all the
  // way from root to a nullptr, which means that it did not find the required node
  while (currNode != nullptr){

    // If JourneyCode of the Current Node is less than required
    // then travel along the right path from the current node.
    if (BSTLessThan(currNode, SearchNode)){
      currNode = currNode->right;
    }
    
    // If JourneyCode of the Current Node is greater than required
    // then travel along the left path from the current node.
    else if (BSTLessThan(SearchNode, currNode)){
      currNode = currNode->left;
    }

    // If both the above conditions fail, that means the journey code
    // of the current node and the required node are the same
    // In that case, this is the node we are searching for, hence return
    // the price of the node
    else {
      return currNode->getPrice();
    }
  }

  // If execution comes out of the loop without returning, that implies
  // required node has not been found, hence return -1.
  return -1;
}


// This function updates the height of the treenode
// by iterating from given TreeNode all the way to the root
// and updating all the nodes along the way.
void BST::updateHeights(TreeNode* parentOfCurrNode){

  // exit the loop when node reaches the nullptr, which means 
  // it has already surpassed the root, and there is no
  // node left to be updated
  while(parentOfCurrNode!=nullptr){
      int heightL, heightR; 
      //heightL and heightR correspond to height of left child and right child respectively.
      if(parentOfCurrNode->right == nullptr){
        //height is zero for a nullpointer as there is nothing
        heightR = 0;
      } 
      else{
        heightR = parentOfCurrNode->right->height;
      }
      if(parentOfCurrNode->left == nullptr){
        //height is zero for a nullpointer as there is nothing
        heightL = 0;
      } 
      else{
        heightL = parentOfCurrNode->left->height;
      }

      //parent of the current node has maximum of heights of children nodes incremented by a 1
      parentOfCurrNode->height = max(heightL,heightR)+1;
      parentOfCurrNode = parentOfCurrNode->parent;
  }
}


// Returns true on successful insertion in BST. Returns false otherwise.
// Also keeping in mind that no two nodes can have the same
// journey code
bool BST::insert(int jrnyCode, int price){

  // Creating a new node named "SearchNode" containing the journey code
  // to be searched along with price set to some value(say 0), as the price
  // doesn't affect our code, as comparing journeycodes would itself suffice.
  // This is in accordance to the assumption, that no two nodes have the 
  // same journey code.  
  TreeNode* SearchNode = new TreeNode(jrnyCode,price);

  // Current Node is set to root, we start iterative search for the required node
  // by comparing the currNode with the SearchNode in every iteration and accordingly
  // chosing which path to follow down.
  // We additionally maintain a parent pointer to the current Node so that 
  // when the currNode becomes NULL, we do know what was the node, that gave
  // rise to the currNode=NULL
  TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  // Exit the looop when currNode is nullptr, this means that currNode travelled all the
  // way from root to a nullptr, which means that it did not find the required node
  while (currNode != nullptr) {

    // If JourneyCode of the Current Node is less than required
    // then travel along the right path from the current node.
    // Also update the parentOfCurrNode
    if (BSTLessThan(currNode, SearchNode)){
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }

    // If JourneyCode of the Current Node is greater than required
    // then travel along the left path from the current node.
    // Also update the parentOfCurrNode
    else if (BSTLessThan(SearchNode, currNode)){
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }

    // If both the above conditions fail, that means the journey code
    // of the current node and the required node are the same
    // In that case, the node we are aiming to insert has already
    // been inserted earlier, so return false.
    else {
      return false;
    }
  }

  // When the while loop ends the moment it begins, that means the tree
  // is empty, hence insert at the root position itself.
  if(parentOfCurrNode == nullptr){
    root = new TreeNode(jrnyCode,price);
  }
  else{
    // If the journeyCode to be inserted is greated than parentOfCurrNode,
    // then insert to its right
    if(BSTLessThan(parentOfCurrNode, SearchNode)){
      updateBSTParentChild(SearchNode,parentOfCurrNode,false);
    }

    // If the journeyCode to be inserted is greated than parentOfCurrNode,
    // then insert to its left
    else{
      updateBSTParentChild(SearchNode,parentOfCurrNode,true);
    }

    //Finally Update all nodes starting from parent of Current Node till the root.
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

bool BST::remove(int jrnyCode){
  TreeNode* SearchNode = new TreeNode(jrnyCode,0);
  TreeNode *currNode = root;
    
  while (currNode != nullptr) {
    if (BSTLessThan(currNode, SearchNode)){
      currNode = currNode->right;
    }
    else if (BSTLessThan(SearchNode, currNode)){
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      break;
    }
  }

  if(currNode == nullptr) return false;

  bool isLeft = false;
  if(currNode!=root){
    if(currNode->parent->left == currNode) isLeft = true;
  }

  if(currNode->right == nullptr && currNode->left == nullptr){
    if(currNode == root){
      root = nullptr;
    }
    else{
      if(currNode->parent->right == currNode) currNode->parent->right = nullptr;
      else currNode->parent->left = nullptr; 
    }
    updateHeights(currNode->parent); //height updation
  }
  else if(currNode->right != nullptr && currNode->left == nullptr){
    updateBSTParentChild(currNode->right,currNode->parent, isLeft);
    updateHeights(currNode->parent);
  }
  else if(currNode->left != nullptr && currNode->right == nullptr){
    updateBSTParentChild(currNode->left, currNode->parent, isLeft);
    updateHeights(currNode->parent);
  }
  else{ //That is when currNode has two children
    TreeNode* succNode = currNode->right;
    while(succNode->left != NULL){
      succNode = succNode->left;
    }

    if(succNode->parent == currNode){
      updateBSTParentChild(currNode->left,succNode,true);
      updateBSTParentChild(succNode,currNode->parent, isLeft);
      updateHeights(succNode);
    }
    else{
      TreeNode* parentOfSuccNode = succNode->parent;
      updateBSTParentChild(succNode->right,succNode->parent, true);
      updateBSTParentChild(currNode->right, succNode, false);
      updateBSTParentChild(currNode->left, succNode, true);
      updateBSTParentChild(succNode, currNode->parent, isLeft);
      updateHeights(parentOfSuccNode);
    }
  }
  return true;
}



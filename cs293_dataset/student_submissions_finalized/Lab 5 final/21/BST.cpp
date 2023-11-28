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
  // currNode and parentOfCurrNode track the position where the new node is to be inserted
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr; 

  TreeNode* new_node = new TreeNode(jrnyCode,price); // new node that is to be inserted

  //base cases : when there is no root just make the new node as root
  if( root == nullptr ){
    root = new_node;
    return true;
  }
  
  //loop untill the tracker reaches NULL pointer
  //basic principle/algorithm of binary insertion is followed
  while (currNode != nullptr) {
    if (BSTLessThan(currNode,new_node)) { 
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (BSTLessThan(new_node,currNode)) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
  }
  //inserting the node
  currNode = new_node; 
  if(BSTLessThan(currNode,parentOfCurrNode)) updateBSTParentChild(currNode,parentOfCurrNode,true); 
  else if(BSTLessThan(parentOfCurrNode,currNode)) updateBSTParentChild(currNode,parentOfCurrNode,false);
  else return false; 
  // now the new node is inserted into the tree as per normal binary insertion


  // updation of height starts down from the inserted node
  while (currNode != nullptr){

    updateHeight(currNode); //height of tracker node is updated
    currNode=currNode->parent;

  }
  return true;
}

//updates the height of a node based on the height of its children nodes
void BST::updateHeight(TreeNode* currNode){
  if(currNode->left==NULL && currNode->right==NULL) {
      currNode->height = 0; 
    }
    else if (currNode->left!=NULL && currNode->right==NULL ){
      currNode->height = currNode->left->height+1;
    }
    else if (currNode->left==NULL && currNode->right!=NULL ){
      currNode->height = currNode->right->height+1;
    }
    else{
      currNode->height = max(currNode->left->height+1,currNode->right->height+1);
    }
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  //algorithm is the exact same as find in normal BST

  TreeNode *search = root; //iterator node
  TreeNode *new_node = new TreeNode(jrnyCode,0); //new node with same journey code for comparison
    while (search != NULL){
        if (BSTLessThan(search,new_node)){
                search = search->right;
        }
        else if (BSTLessThan(new_node,search)){
                search = search->left;
        }
        else{
            return (search->getPrice());
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



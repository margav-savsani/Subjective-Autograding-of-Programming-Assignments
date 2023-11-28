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

/* Implemented */bool BST::insert(int jrnyCode, int price)
{
	TreeNode* to_insert=new TreeNode(jrnyCode,price);
	TreeNode* curr=root;
	bool isLeft;
	while(curr){
		if(BSTLessThan(to_insert,curr)){
			if(curr->left){	
				curr=curr->left;
				continue;
			}
			isLeft=true;
			break;
		}
		else if(BSTLessThan(curr,to_insert)){
			if(curr->right){
				curr=curr->right;
				continue;
			}
			isLeft=false;
			break;
		}
		return false; // Already present
	}
	updateBSTParentChild(to_insert,curr,isLeft);
	//Insertion Done
	// Balancing test and height update starts
	TreeNode* currNode=to_insert;
	if(root==NULL){
		root=to_insert;
		return true;
	}
	while(currNode){
		int lh=-1,rh=-1;
		if(currNode->left)	lh=currNode->left->height;
		if(currNode->right)	rh=currNode->right->height;
		currNode->height=max(lh,rh)+1;
		currNode=currNode->parent;
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
  // Implement find in BST

	TreeNode* to_find=new TreeNode(jrnyCode,0);
	TreeNode* curr=root;
	while(curr){ // Ensures that curr is not NULL inside the loop
		if(BSTLessThan(to_find,curr)){
			curr=curr->left;
			continue;
		}
		if(BSTLessThan(curr,to_find)){
			curr=curr->right;
			continue;
		}
		return curr->getPrice(); // It is neither less, nor more, therefore, it is the required node.
	}
	return -1;


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



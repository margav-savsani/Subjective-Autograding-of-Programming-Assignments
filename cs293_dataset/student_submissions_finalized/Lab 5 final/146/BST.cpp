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
	TreeNode* elem;
	elem = new TreeNode(jrnyCode, price); //We create an element to store given data
	//First we check if tree is empty in which case we add root with parent pointing to NULL
	if(root == NULL){
		root = elem;
		root->parent = NULL;
		root->left = NULL;
		root->right = NULL;
		root->height = 1;
		return true;
	}
	TreeNode *currNode = root;
	
	while (true) {
		
		if (BSTLessThan(elem, currNode)) {
			if (currNode->left == NULL){
				currNode->left = elem;
				currNode->left->parent=currNode;
				currNode = currNode->left; 
				currNode->height = 1;
				break;
			}
			currNode = currNode->left;
		}
		else if (BSTLessThan(currNode,elem)) {
			if (currNode->right == NULL){
				currNode->right = elem;
				currNode->right->parent = currNode;
				currNode = currNode->right; 
				currNode->height = 1;
				break;
			}
			currNode = currNode->right;
		}
		else { // currNode = elem
			return false;
		}
	}  
	while(currNode->parent!=NULL){
		if(currNode->parent->height >= currNode->height+1) break;
		currNode->parent->height = currNode->height+1;
		currNode = currNode->parent;
	}
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

	// You MUST use only BSTLessThan to compare two journey codes.  You
	// can create a new node containing the journey code to be searched
	// (along with some arbitrary price) and invoke BSTLessThan on the
	// current node in the tree that you are inspecting and the new node
	// to do your comparison.
	TreeNode* elem ;
	elem = new TreeNode{jrnyCode,0} ;
	TreeNode* currNode = root;
	while(currNode!=NULL){
		if(BSTLessThan(elem,currNode)) currNode = currNode->left;
		else if(BSTLessThan(currNode,elem)) currNode = currNode->right;
		else {
			return true;
		} 
	}
	
	return false;

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

bool BST::remove(int jrnyCode){

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

	TreeNode* currNode = root;
	TreeNode* elem ;
	elem = new TreeNode{jrnyCode,0} ;
	while(currNode!=NULL){
		if(BSTLessThan(elem,currNode)) currNode = currNode->left;
		else if(BSTLessThan(currNode,elem)) currNode = currNode->right;
		else {
			if(currNode->left == NULL){
				if(currNode->parent==NULL){
					root = currNode->right;
					root->parent = NULL;
				}
				else if(currNode->parent->right == currNode){
					currNode->parent->right = currNode->right;
					if(currNode->right!=NULL) currNode->right->parent = currNode->parent;
				}
				else if(currNode->parent->left == currNode){
					currNode->parent->left = currNode->right;
					if(currNode->right!=NULL) currNode->right->parent = currNode->parent;
				}
			}
			else{
				if(currNode->left->right==NULL){
					currNode->left->right=currNode->right;
					currNode->left->parent = currNode->parent;
					if(currNode->right!=NULL) currNode->right->parent = currNode->left;

					if(currNode->parent==NULL){
					root = currNode->left;
					root->parent = NULL;
					}
					else if(currNode->parent->right == currNode){
					currNode->parent->right = currNode->left;
					}
					else if(currNode->parent->left == currNode){
					currNode->parent->left = currNode->left;
					}
				}
				else{
					TreeNode* pred = currNode->left; //we find the predecessor
					while(pred->right!= NULL) {pred = pred->right;}

					pred->right = currNode->right;
					if(currNode->right != NULL) currNode->right->parent = pred;

					currNode->left->parent = currNode->parent;

					if(currNode->parent==NULL){
					root = currNode->left;
					root->parent = NULL;
					}
					else if(currNode->parent->left == currNode){
					currNode->parent->left = currNode->left;
					}
					else if(currNode->parent->right == currNode){
					currNode->parent->right = currNode->left;
					}
				}
				return true;
			}
		}
	}
	return false;
}



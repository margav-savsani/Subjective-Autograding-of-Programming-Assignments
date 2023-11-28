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

TreeNode* insert2(TreeNode* root, int JourneyCode, int price){


	TreeNode *x;
	x = new TreeNode(JourneyCode, price);
	
	if( root == NULL){
	
		TreeNode* n= new TreeNode(JourneyCode,price);
		root = n;
		return root;
	}
	
	if( root < x ){
	
		root->right = insert2(root->right, JourneyCode, price);

	}
	else if( x < root ){
	
		root->left = insert2(root->left, JourneyCode, price);
	}
	
	return root;
}

bool BST::insert(int jrnyCode, int price)
{



  bool found = find(jrnyCode);
	if(found) return false;
	root = insert2(root, jrnyCode, price);
	return true;
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool find2( TreeNode* root, int JourneyCode){

	TreeNode *x;
	x = new TreeNode(JourneyCode, 0);

	if( root == NULL){
	
		return false;
	}

	if(root < x && x < root ){
		
			return true;
	}
	
	else if(root < x ){
	
		return find2(root->right, JourneyCode);
	}
	
	else if(x < root  ){
	
		return find2(root->left, JourneyCode);
	}
	return false;
	
}

int BST::find(int jrnyCode)
{


	return find2(root, jrnyCode);


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
TreeNode* min2(TreeNode* root){

	if( root == NULL) return NULL;

	if ( root->left == NULL) return root;
	else return min2(root->left);
}



TreeNode* remove2(TreeNode* root, int JourneyCode){


	TreeNode *x;
	x = new TreeNode(JourneyCode, 0);
	if( root== NULL){
	
		return NULL;
	}

	if( root < x){
	
		root->right = remove2(root->right, JourneyCode);
	}
	else if( x < root ){
	
		root->left = remove2(root->left, JourneyCode);
	}
	else {
	
		if( root->left == NULL && root->right == NULL){
		
			root = NULL;
		}
		else if(  root->left == NULL){
		
			root = root->right;
		}
		else if( root->right == NULL ){
		
			root = root->left;

		}
		else {
		
			struct TreeNode* a = min2(root->right);
			root->make(a);
			root->right = remove2(root->right, a->Journeyreturn());
		}
	}
	
	return root;
}


bool BST::remove(int jrnyCode)
{

bool found = find2(root, jrnyCode);
	
	if(!found){
	
		return false;
		
	}
	else{
	
		remove2(root, jrnyCode);
	}
	return true;
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

}



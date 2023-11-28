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
	try {
		if ( root == nullptr ){
		root = new TreeNode( jrnyCode, price );
		throw 1;
	}
	else {
	TreeNode *z, *x, *y, *p;
	x=root;
	y=nullptr;
	z=new TreeNode(jrnyCode, price);
	while (x != nullptr){
		y = x;
		if( BSTLessThan(z, x) ){
			x=x->left;
		}
		else if ( BSTLessThan(x, z) ){
			x=x->right;
		}
	}
	
	if (BSTLessThan(z, y)){
		y->left=z;
		z->parent=y;
		p=y;
		while(p != root){
			p->height=height(p)-1;
			p=p->parent;
		}
		root->height=height(root)-1;
		throw 1;
	}
	if (BSTLessThan(y, z)){
		y->right=z;
		z->parent=y;
		p=y;
		while(p != root){
			p->height=height(p)-1;
			p=p->parent;
		}
		root->height=height(root)-1;
		throw 1;
	}
	}
	}
	catch (int) {
		return true;
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
  return false;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST
int BST::height(TreeNode *x){
	if (x==nullptr) return 0;
	else {
		int l = height(x->left);
		int r = height(x->right);
		return max(l,r)+1;
	}
}

int BST::find(int jrnyCode)
{
	TreeNode *z, *x;
	x = root;
	z = new TreeNode(jrnyCode, 6);
	while(x != nullptr){
		if (BSTLessThan(z,x)){
			x=x->left;
		}
		else if (BSTLessThan(x,z)){
			x=x->right;
		}
		else return 1;   
	} 
	return -1;


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



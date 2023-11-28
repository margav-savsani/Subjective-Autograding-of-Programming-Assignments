#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

TreeNode * f;

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
	if(find(jrnyCode)!=-1) return false;
	TreeNode * z = new TreeNode(jrnyCode,price);
	TreeNode * y = nullptr;
	TreeNode * x = root;
	while(x!=nullptr){
		y = x;
		if(BSTLessThan(x,z)) x = x->right;
		else x = x->left;
	}
	z->parent = y;
	if( y == nullptr){ root = z; return true; }
	else if(BSTLessThan(y,z)){
             y->right=z;
             TreeNode *p=y->right;
             if(y->left==NULL){
                while(p->parent!=NULL && (p->parent)->height < p->height + 1){   
                   (p->parent)->height=p->height+1;
                   p=p->parent;
                }
             }
            }
        else{
            y->left=z;
            TreeNode *p=y->left;
             if(y->right==NULL){
                while(p->parent!=NULL && (p->parent)->height < p->height + 1){
                   (p->parent)->height=p->height+1;
                   p=p->parent;
                }
             }
        }
	return true;
  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
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
	TreeNode * z = new TreeNode(jrnyCode,99);
	TreeNode * x = root;
	while( x!=nullptr ){
		if(jrnyCode==x->get_jrnyCode()){ f = x; return x->get_price();}
		else if(BSTLessThan(z,x)) x = x->left;
		else x = x->right;
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



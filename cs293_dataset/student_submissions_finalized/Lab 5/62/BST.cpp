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
bool BST::insert(int JourneyCode, int price)
{
	// Implement insertion in BST
	if (root==NULL){ //insert to empty BST
		root = new TreeNode(JourneyCode, price);
		return true;
	}
	TreeNode to_ins(JourneyCode,price);
	TreeNode* current=root;
	while(current!=NULL){//travel down the tree
		if (BSTLessThan(&to_ins,current)){
			if (current->left==NULL){ // if reached an empty spot, insert here
					current->left=new TreeNode(JourneyCode, price, current);
					break ;
			}
			current=current->left; //otherwise keep moving
		}
		else { 
			if (current->right==NULL){ // if reached an empty spot, insert here
					current->right=new TreeNode(JourneyCode, price, current);
					break;
			}
			current=current->right; //otherwise keep moving
		}
	}  
	if (current==NULL) return false; // a weird scenario
	current->updateHeights();	
	return true;

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
int BST::find(int JourneyCode)
{
	TreeNode to_find(JourneyCode,-1);
	TreeNode* current=root;
	while(current!=nullptr){  //travelling down the tree      
		if (BSTLessThan(&to_find,current)){ // to_find < current
				current=current->left;
		}
		else if(BSTLessThan(current,&to_find)){
				current=current->right;
		} //equals
		else return (current->getPrice());
	}    
	return (-1); //did not find match
}

bool TreeNode::updateHeights(){
	TreeNode* current=this;
    for(;current!=NULL;current=current->parent){
		int to_set;
        if (current->left==NULL&&current->right==NULL){ //leaf
            to_set=0;
        }
        //only one child
        else if (current->left==NULL){
            to_set=(1+ current->right->height);
        }
        else if (current->right==NULL){
            to_set= 1+ current->left->height;
        }
        //both children present
        else {
            to_set = 1+max(current->right->height,current->left->height);
        }
		if (to_set == current->height) return true;
		current->height = to_set;
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

bool BST::remove(int JourneyCode)
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



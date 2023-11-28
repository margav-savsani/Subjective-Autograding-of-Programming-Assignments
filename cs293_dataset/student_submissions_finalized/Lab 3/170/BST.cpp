#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){ root=nullptr; }
BST::BST(TreeNode *root){ this->root=&root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
	if(find(JourneyCode, price){
		TreeNode * p=found(JourneyCode, price);
		p->JourneyCode=JourneyCode;
		p->price=price;
		return true;
	}
	return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
	if(found(JourneyCode, price)==nullptr)return false;
	else return true;
}

TreeNode* BST::found(int JourneyCode, int price) {
	while(root->price!=price){
		if(price < root->price) root=root->left;
		else root=root->right;
	}
	return root;
}

	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
	if(find(JourneyCode, price){
		TreeNode * p=found(JourneyCode, price);
		p->JourneyCode=0;
		p->price=0;
		return true;
	}
	return false; 
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
	if(typeOfTraversal==0){
		if(root==null)return;
		else root=root->left;
	}
	return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
	while(root->left!=NULL){
        	root->left=root;
	}
    	return root->price;
	return 0; 
}

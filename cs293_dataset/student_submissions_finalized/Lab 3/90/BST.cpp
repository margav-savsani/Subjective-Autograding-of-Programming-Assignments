#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// ALl Under Assumption that two Journey Codes won't be the same
// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
	root = NULL;	
}
BST::BST(TreeNode *root){ 
	this->root = root;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
	if(root==NULL) return false;
	if(root->price==price){
		if(root->JourneyCode==JourneyCode) return true;
		BST T2(root->right);
		return T2.find(JourneyCode, price);
	}
	if(root->price<price){
		BST T2(root->right);
		return T2.find(JourneyCode, price);
	}
	BST T1(root->left);
	return T1.find(JourneyCode, price);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 

	if(find(JourneyCode, price)) return false;
	
	//looping once again!
	TreeNode* curr = root;
	TreeNode* curr_parent = NULL;
	while(curr!=NULL){
		curr_parent = curr;
		if(curr->price<=price) curr = curr->right;
		else curr = curr->left;
	}
	if(curr_parent == NULL) root = new TreeNode(JourneyCode, price);
	else{
		if(curr_parent->price <= price){
			curr_parent->right = new TreeNode(JourneyCode, price);
			curr_parent->right->parent = curr_parent;
		}
		else{
			curr_parent->left = new TreeNode(JourneyCode, price);
			curr_parent->left->parent = curr_parent;
		}
	}
	return true;

}

// Returns the price of the cheapest journey
int BST::getMinimum(){
	int min_price = root->price;
	if(root->left == NULL) return min_price;
	BST T1(root->left);
	return T1.getMinimum();
}


// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
	if(!find(JourneyCode, price)) return false;
	
	if(root->JourneyCode==JourneyCode && root->price==price){
		root = NULL;	
		return true;	
	}
	else{
		TreeNode* curr = root;
		TreeNode* curr_parent = NULL;
		while(!(curr->price==price && curr->JourneyCode==JourneyCode)){
			if(curr->price==price){
				if(curr->JourneyCode==JourneyCode){
					break;
				}
				else{
					curr_parent = curr;
					curr = curr->right;
				}
			}
			else if(curr->price<price){
				curr_parent = curr;
				curr = curr->right;
			}
			else{
				curr_parent = curr;
				curr = curr->left;
			}
		}
		
		if(curr->right == NULL && curr->left == NULL){
			if(curr_parent->price<=price) curr_parent->right = NULL;
			else curr_parent->left = NULL;
		}
		else if(curr->right == NULL || curr->left == NULL){
			if(curr->left!=NULL){
				if(curr_parent->price<=price) curr_parent->right = curr->left;
				else curr_parent->left=curr->left;
			}
			else{
				if(curr_parent->price<=price) curr_parent->right = curr->right;
				else curr_parent->left=curr->right;
			}
		}
		else{
			TreeNode* succ = curr->right;
			TreeNode* succ_parent = curr;
			while(succ->left!=NULL){
				succ_parent = succ;
				succ = succ->left;
			}
			if(succ->right!=NULL){
				succ->right->parent = succ->parent;
				if(succ_parent==curr) succ_parent->right = succ->right;
				else succ_parent->left = succ->right;
			}	
			remove(succ->JourneyCode, succ->price);
			curr->JourneyCode = succ->JourneyCode;
			curr->price = succ->price;
		}
	}
	return true;						
}
	


void BST::preorder(){
	if(root==NULL) return;
	cout << root->JourneyCode << endl;
	BST T1(root->left);
	BST T2(root->right);
	T1.preorder();
	T2.preorder();
	return;
}

void BST::postorder(){
	if(root==NULL) return;
	BST T1(root->left);
	BST T2(root->right);
	T1.postorder();
	T2.postorder();
	cout << root->JourneyCode << endl;
	return;
}

void BST::inorder(){
	if(root==NULL) return;
	BST T1(root->left);
	BST T2(root->right);
	T1.inorder();
	cout << root->JourneyCode << endl;
	T2.inorder();
	return;
}



// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST::traverse(int typeOfTraversal) {
	switch(typeOfTraversal){
		case 0: preorder();
			break;
		case 1: postorder();
			break;
		case 2: inorder();
	}
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {return 0; }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { return; }
	
// While loading a tree from a file written by customStore, we
// can have one of two modes of loading.  We could either ask
// for the entire tree to be loaded or only the left subtree of
// the root (if it exists) to be loaded.  The loadMode flag
// takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// that are #defined in BST.cpp.
// If loadMode is LOAD_FULL_BST, customLoad should load the
// entire BST that was stored in filename using customStore.
// If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// only the left subtree of the root of the BST that was
// stored in filename using customStore.
// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded.  So, for example, if the
// left sub-tree of the root is small compared to the right
// sub-tree, customLoad's time and space complexity should
// be small even though the entire BST may be very large.
 
void BST::customLoad (int flag, string filename) { return; }


// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}


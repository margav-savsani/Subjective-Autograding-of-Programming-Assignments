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


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
	root=NULL;
}
BST::BST(TreeNode *root){
	this->root=root;
}
// Returns the node with minimum price in the tree after node
TreeNode* BST::getMinimum(TreeNode* node){
	if(node->left==NULL)	return node;
	return getMinimum(node->left);// Recursion
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){
	TreeNode* curr=root;
	while(curr){
		if(curr->JourneyCode==JourneyCode && curr->price==price)	return false; // if curr is same as to be inserted
		if(price<=curr->price && curr->left){//if insertion is to be done on left
			curr=curr->left;
			continue;
		}
		if(price>curr->price && curr->right){// if insertion is to be done on right
			curr=curr->right;
			continue;
		}
		// if node to be inserted is child of node
		if(price>curr->price){
			curr->right=new TreeNode(JourneyCode,price,NULL,NULL,curr);
			return true;
		}
		curr->left=new TreeNode(JourneyCode,price,NULL,NULL,curr);
		return true;
	}
	// arrives here if tree is empty.
	root=new TreeNode(JourneyCode,price,NULL,NULL,NULL);
	return true;
}

TreeNode* BST::search_node(int price){ // Search for the first node with price as value
	TreeNode* curr=root;
	while(curr){
		if(curr->price==price){
			return curr;
		}
		if(price<curr->price){
			curr=curr->left;
			continue;
		}
		if(price>curr->price){
			curr=curr->right;
			continue;
		}
	}
	return curr;
}
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
	TreeNode* curr=search_node(price);
	while(curr){
		if(curr->JourneyCode==JourneyCode)	return true;
		if(curr->price!=price)	return false;
		curr=curr->left;
	}
	return false;
}
	
void BST::removeNode(TreeNode* node){
	TreeNode* curr=node;
	TreeNode* par=node->parent;
	if(!node->right){
		if(!node->left){
			TreeNode* par=node->parent;
			if(par->right == node){
				par->right=NULL;
				delete curr;
				return;
			}
			par->left=NULL;
			delete node;
			return;
		}
		// *node=*(node->left);
		TreeNode* to_remove=node->left;
		node->JourneyCode=node->left->JourneyCode;
		node->price=node->left->price;
		node->right=node->left->right;
		node->left=node->left->left;
		delete to_remove;
		return;
	}
	if(!node->right->left){
		// *node=*(node->right);
		TreeNode* to_remove=node->right;
		node->JourneyCode=node->right->JourneyCode;
		node->price=node->right->price;
		node->right=node->right->right;
		delete to_remove;
		return;
	}
	TreeNode* replacement=getMinimum(node->right);
	replacement->parent->left=replacement->right;
	node->JourneyCode=replacement->JourneyCode;
	node->price=replacement->price;
	return;
}
			



// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { //Incomplete
	if(root==NULL)	return false;
	if(root->JourneyCode==JourneyCode && root->price==price){
		if(root->left==NULL && root->right==NULL){
			root=NULL;
			return true;
		}
	}
	TreeNode* curr=search_node(price);
	while(curr){
		if(curr->JourneyCode==JourneyCode && price==curr->price){
			removeNode(curr);
			return true;
		}
		if(curr->price!=price)	return false;
		if(curr->left)	curr=curr->left;
	}
	return false;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
	if(root==NULL)	return;
	TreeNode* curr=root;
	if(typeOfTraversal==PRE_ORDER){
		cout<<curr->JourneyCode<<endl;
	}
	root=curr->left;
	traverse(typeOfTraversal);
	if(typeOfTraversal==IN_ORDER){
		cout<<curr->JourneyCode<<endl;
	}
	root=curr->right;
	traverse(typeOfTraversal);
	if(typeOfTraversal==POST_ORDER){
		cout<<curr->JourneyCode<<endl;
	}
	root=curr;
	return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
	return getMinimum(root)->price;
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


// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

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

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

BST::BST(){root=nullptr;};
BST::BST(TreeNode *root){this->root==root;};


bool BST::insertelement(int JourneyCode, int price, TreeNode *root){
	if(find(JourneyCode, price) == true) return false;
	else if(price<=root->price && root->left==nullptr){
		root->left->JourneyCode=JourneyCode;
		root->left->price=price;
		return true;
	}
	else if(price>=root->price && root->right==nullptr){
		root->right->JourneyCode=JourneyCode;
		root->right->price=price;
		return true;
	}
	else if(price<=root->price && root->left!=nullptr){insertelement(JourneyCode, price, root->left); return true;}
	else if(price>=root->price && root->right!=nullptr){insertelement(JourneyCode, price, root->right); return true;}
}
// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {return insertelement(JourneyCode, price, root);}

//new function that also gives the same outcome as find(journeycode, price) but this also have input value of root, 
//which is used for recursion.
bool BST::findjourney(int JourneyCode, int price, TreeNode *root) {
	if(root==nullptr) return false;
	else if(JourneyCode==root->JourneyCode && price==root->price) return true;
	else if(root->left == nullptr && root->right != nullptr) return findjourney(JourneyCode, price, root->right);
	else if(root->right == nullptr && root->left != nullptr) return findjourney(JourneyCode, price, root->left);
	else if(root->left != nullptr && root->right != nullptr){
		return(findjourney(JourneyCode, price, root->right)||findjourney(JourneyCode, price, root->left));
	}
	else return false; 
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){return findjourney(JourneyCode, price, root);};

	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
	if(find(JourneyCode, price)!=true) return false;
}

void visit(TreeNode *t){cout<<t->JourneyCode<<endl;}

void BST::traversal(int typeOfTraversal, TreeNode *root) {
	if(root==nullptr) return;
	else if(typeOfTraversal==0){
		visit(root);
		if(root->left!=nullptr) traversal(0, root->left);
		if(root->right!=nullptr) traversal(0, root->right);
	}
	else if(typeOfTraversal==1){
		if(root->left==nullptr && root->right==nullptr) visit(root);
		if(root->left!=nullptr) traversal(1, root->left);
		if(root->right!=nullptr) traversal(1, root->right);
	}
	else if(typeOfTraversal==2){
		if(root->left!=nullptr) traversal(2, root->left);
		visit(root);
		if(root->right!=nullptr) traversal(2, root->right);
	}
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {traversal(typeOfTraversal, root);}

int BST::getmin(TreeNode *root){//new function which also gets the min value of tree, 
                                //but this has an input value to be used for recursion.
	if(root==nullptr) return 0;
	else if(root->right==nullptr) return root->price;
	else if(root->right!=nullptr) return getmin(root->right);
}
// Returns the price of the cheapest journey
int BST::getMinimum() {return getmin(root);}

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

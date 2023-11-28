#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

TreeNode * f;

BST::BST(){ ; }
BST::BST(TreeNode *root){ this->root=root; }

TreeNode* BST:: successor(TreeNode * r) {
	if(r->right != nullptr){
		TreeNode * t = r->right;
		while(t->left!=nullptr){
        		t=t->left;
		}
    		return t;
    	}
	TreeNode * y = r->parent;
	while ( y!=nullptr && r==y->right ){
		r = y;
		y = y->parent;
	}
	return y;
}

void BST:: pre_order(TreeNode * r) {
	if(r == nullptr) return;
	else {
		cout<< r->JourneyCode << endl;
		pre_order(r->left);
		pre_order(r->right);
	}
}

void BST:: post_order(TreeNode * r) {
	if(r == nullptr) return;
	else {
		post_order(r->left);
		post_order(r->right);
		cout<< r->JourneyCode << endl;
	}
}

void BST:: in_order(TreeNode * r) {
	if(r== nullptr) return;
	else {
		post_order(r->left);
		cout<< r->JourneyCode << endl;
		post_order(r->right);
	}
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
	if(find(JourneyCode,price)) return false;
	TreeNode * z = new TreeNode(JourneyCode,price);
	TreeNode * y = nullptr;
	TreeNode * x = root;
	while(x!=nullptr){
		y = x;
		if( x->price <= price) x = x->right;
		else x = x->left;
	}
	z->parent = y;
	if( y == nullptr) root = z;
	else if( y->price <= price) y->right = z;
		else y->left = z;
	return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
	TreeNode * x = root;
	while( x!=nullptr ){
		if( price==x->price ){
			if(JourneyCode==x->JourneyCode){ f = x; return true;}
			else{   x=x->right;
				continue;
			}
		}
		else if(price < x->price) x = x->left;
		else x = x->right;
	}
	return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
	TreeNode * x;
	TreeNode * y;
	if(!find(JourneyCode, price)) return false;
	else{  
		if (f->left == nullptr || f->right == nullptr) y = f;
			else y = successor(f);
		if (y->left != nullptr) x = y->left;
			else x = y->right;
		if (x != nullptr) x->parent = y->parent;
		if(y->parent == nullptr) root = x;
		else if ( y == y->parent->left) y->parent->left = x;
			else y->parent->right = x;
		if( y != f ) {
			f->price = y->price;
			f->JourneyCode = y->JourneyCode;
		}
		return true;
	}
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
	if(typeOfTraversal==0) pre_order(root);	
	else if(typeOfTraversal==1) post_order(root);
		else if(typeOfTraversal==2) in_order(root);
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
	while(root->left!=NULL){
        	root=root->left;
	}
    	return root->price; 
}

// Part II

int BST:: Count(TreeNode *root, int low, int high)
{
    if (!root) return 0;
    if (root->price == high && root->price == low)
        return 1;
    if (root->price <= high && root->price >= low)
         return (1 + Count(root->left, low, high) + Count(root->right, low, high));
    else if (root->price < low)
         return Count(root->right, low, high);
    else return Count(root->left, low, high);
}

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
	return Count(root, lowerPriceBound, upperPriceBound);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
	ifstream outfile;
	//infile.open(filename);
	return;
}
	
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
        root = root->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "└──" );

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
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


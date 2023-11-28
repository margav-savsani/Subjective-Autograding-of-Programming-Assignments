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
	struct TreeNode* node = new struct TreeNode();
	node = NULL;
	root = node; 	
}


BST::BST(TreeNode *root){
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
	this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
	
	// Make a new TreeNode with given journeycode and price
	struct TreeNode* node = new struct TreeNode(JourneyCode, price);
	
	if( root == NULL )
	{
		root = node;
		return true;
	}	
	
	struct TreeNode* temp = root , *parent = NULL;
	
	// Searching if given journey already exist in the BST
	while(temp != NULL)
	{
		if(temp->JourneyCode == JourneyCode)
		{	
			return false;
		}
		else if(price <= temp->price)
		{
			parent = temp;
			temp = temp->left;
		}
		else {
			parent = temp;
			temp = temp->right;
		}		
	}
	
	
	// journey not found, so enter it in BST
	node->parent = parent;
	if(parent->left == NULL && price < parent->price)
	{
		parent->left = node;		
	}
	else
	{
		parent->right = node;	
	}
	
	return true;

}



// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 

	if( root == NULL ) return false;
	
	struct TreeNode *temp = root;
	
	while(temp != NULL)
	{
		if(temp->JourneyCode == JourneyCode) return true;
		if(price <= temp->price ) temp = temp->left;
		else temp = temp->right;
	}
	
	return false;
}


struct TreeNode* BST::successor(struct TreeNode* node){

	if(node == NULL) return NULL;
	
	// If right subtree exists
	if(node->right != NULL)
	{
		node = node->right;
		
		while(node->left != NULL) node = node->left;
		return node;
	}
	// Else search in upper trees and stop when parent->left == node
	else
	{
		struct TreeNode* parent = node->parent;

		// If node was the largest element in the BST, then no successor
		if(parent == NULL ) return NULL;

		while(parent != NULL && parent->left != node)
		{
			  node = parent;
			  parent = node->parent;
		}
		return parent;
	}

}



	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {

	if(root == NULL) return root;
	
	struct TreeNode *node = root, *parent = NULL;
	
	// Finding if Journey code is present in the BST
	bool found = false;
	while(node != NULL)
	{
		if(node->price == price && node->JourneyCode == JourneyCode) {
			found = true;
			break;
		}
		else if(price <= node->price) {
			parent = node;
			node = node->left;
		}	
		else {
			parent = node;
			node = node->right;
		}	
	}
	
	// If not present return false;
	if(!found) return false;
	
	// Now node is present in BST, so 3 cases arise
	
	// 1 ==> If node has no child, then make parent point to null
	if(node->left == NULL && node->right == NULL)
	{
		// If node to be deleted is not root node, then simple make parent point to null
		if(parent != NULL)
		{
			if(parent->left == node) parent->left = NULL;
			else parent->right = NULL;
			delete node;
		}
		// else node to be deleted is root node
		else
		{
			root = NULL;
		}
		return true;

	}
	// 2==> If only 1 child
	else if(node->left == NULL || node->right == NULL)
	{
		// If node to be deleted is not the root node, then simply change relevant links 	
		if(parent != NULL)
		{
			// If only right child
			if(node->left ==  NULL)
			{
				if(parent->left == node)
				{
					parent->left = node->right;
					parent->left->parent = parent;
					delete node;
				}
				else
				{
					parent->right = node->right;
					parent->right->parent = parent;
					delete node;
				}		
			}
			// If only left child
			else
			{
				if(parent->left == node)
				{
					parent->left = node->left;
					parent->left->parent = parent;
					delete node;
				}
				else
				{
					parent->right = node->left;
					parent->right->parent = parent;
					delete node;
				}
			}
		}
		// If node to be deleted is root node, then make root to either left BST or right BST
		else
		{
			if(node->left == NULL)
			{
				root = root->right;
			}
			else
			{
				root = root->left;
			}
		}	
		return true;	
	}
	// 3 ==> If both child are there
	else
	{
		struct TreeNode *temp = node;

		temp = temp->right;

		while(temp->left != NULL) temp = temp->left;
		//Copying data from maximum node
		int t1 = temp->JourneyCode, t2 = temp->price; 
		bool removeSuccessor = remove(temp->JourneyCode , temp->price);	

		node->price = t2;
		node->JourneyCode = t1;
		return true;
	}	

}

void BST::preOrder(struct TreeNode *root){
	
	if(root == NULL) return;
	
	cout << root->JourneyCode << endl;
	preOrder(root->left);
	preOrder(root->right);
}

void BST::postOrder(struct TreeNode *root){
	
	if(root == NULL) return;
	
	postOrder(root->left);
	postOrder(root->right);
	cout << root->JourneyCode << endl;
}


void BST::inOrder(struct TreeNode *root){
	
	if(root == NULL) return;
	
	inOrder(root->left);
	cout << root->JourneyCode << endl;
	inOrder(root->right);
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line
void BST::traverse(int typeOfTraversal) {

	if(typeOfTraversal == 0)
	{
		preOrder(root);
	}
	else if(typeOfTraversal == 1)
	{
		postOrder(root);
	}
	else if(typeOfTraversal == 2)
	{
		inOrder(root);
	}
}


// Returns the price of the cheapest journey
int BST::getMinimum() {

	struct TreeNode* temp = root;
	
	while(temp->left != NULL) temp = temp->left;
	return temp->price;

}







// Part II

void BST::inOrderTraversal(struct TreeNode* root){

	if(root == NULL) return;

	inOrderTraversal(root->left);
	inOrderVector.push_back(root->price);
	inOrderTraversal(root->right);
}

int BST::binarySearchMin(vector<int> v , int key){

	int low = 0, high = v.size()-1;
	int minIndex = 0;
	while(low  <= high){

		int mid = low + (high-low)/2;
		if(v[mid] == key) {
			minIndex = mid;
			high = mid - 1;
		}
		else if(key < v[mid]) high = mid - 1;
		else low = mid + 1;
	}

	return minIndex;
}

int BST::binarySearchMax(vector<int> v , int key){

	int low = 0, high = v.size()-1;
	int maxIndex = v.size()-1;
	while(low  <= high){

		int mid = low + (high-low)/2;
		if(v[mid] == key) {
			maxIndex = mid;
			low = mid + 1;
		}
		else if(key < v[mid]) high = mid - 1;
		else low = mid + 1;
	}

	return maxIndex;
}


// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {

	inOrderTraversal(root);

	int min = binarySearchMin(inOrderVector , lowerPriceBound);
	int max = binarySearchMax(inOrderVector , upperPriceBound);

	inOrderVector.clear();

	return max - min + 1;
}

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
 
void BST::customLoad (int flag, string filename) { 

	ifstream input;
	input.open(filename);
	int data;
	while(input>>data)
	{
		
	}




}


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


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
	 root = nullptr;
}
BST::BST(TreeNode *root){
	this->root = root; 
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
	
	
	TreeNode *ptr = root;
	bool done{false};
	
	TreeNode *node;
	node = new TreeNode;
	node->JourneyCode = JourneyCode;
	node->price = price;
	node->left = nullptr;
	node->right = nullptr;
	
	if(root == nullptr){
		root = node;
		node->parent = nullptr;
		return true;
	}
	
	
	else{
		
		while(true){
			
			if(ptr->price >= price){
				if(ptr->left == nullptr){
					node->parent = ptr;
					ptr->left = node;
					node = nullptr;
					break;
				}
				else{
					ptr = ptr->left;
				}
			}
			
			else if(ptr->price < price){
				if(ptr->right == nullptr){
					node->parent = ptr;
					ptr->right = node;
					node = nullptr;
					break;
				}
				else{
					ptr = ptr->right;
				}
			}
		}
		return true;
	}
}

bool BST::find(int JourneyCode, int price){
	
	TreeNode *ptr = myfind(JourneyCode, price);
	if(ptr == nullptr){
		return false;
	}
	else{
		return true;
	}
}

// Return True, if the ticket with given attributes is found, false otherwise
TreeNode* BST::myfind(int JourneyCode, int price) { 
	
	TreeNode *ptr = root;
	if(ptr == nullptr)
		return false;
}


// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 

	return true;
	/*TreeNode* ptr;
	ptr = myfind(JourneyCode, price);
	if(ptr==nullptr){
		return false;
	}	
	else{
		myremove(ptr);
		return true;
	}*/

}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
	if(root == nullptr)
		return;
	TreeNode *ptr=root;
	if(typeOfTraversal == 0){
		traverse0(root);
	}
	
	if(typeOfTraversal == 1){
		traverse1(root);
	}
	
	if(typeOfTraversal == 2){
		traverse2(root);
	}
}

void BST::traverse0(TreeNode *ptr){
	if(ptr == nullptr)
		return;
	cout<< ptr->JourneyCode <<endl;
	traverse0(ptr->left);
	traverse0(ptr->right);
}

void BST::traverse1(TreeNode *ptr){
	if(ptr == nullptr)
		return;
	traverse1(ptr->left);
	cout<< ptr->JourneyCode <<endl;
	traverse1(ptr->right);
}

void BST::traverse2(TreeNode *ptr){
	if(ptr == nullptr)
		return;
	traverse2(ptr->left);
	traverse2(ptr->right);
	cout<< ptr->JourneyCode <<endl;
}	

// Returns the price of the cheapest journey
int BST::getMinimum() {
	TreeNode *ptr = root;
	while(true){
		if(ptr == nullptr)
			return 0;
		if(ptr->left == nullptr)
			return ptr->price;
		else{
			ptr = ptr->left;
		}
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
        result.push_back(root->JourneyCode + "\n");
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


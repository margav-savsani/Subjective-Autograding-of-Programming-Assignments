#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){
 root = NULL;
}
BST::BST(TreeNode *root){
 this->root = root; 
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if (root==NULL) {
    root = new TreeNode(JourneyCode, price);
 	root->parent = NULL;
 	return true;
	}

 //simply checking for root->JourneyCode won't work because a ticket with this 
 //JourneyCode might be on different side of root while new ticket might be on opposite side
 // if (location(JourneyCode)!=nullptr){ 
 // return false;
 // }
 if (root->price >= price){
 if(root->left!=NULL){
 BST left_subtree(root->left);
 return left_subtree.insert(JourneyCode, price);
 }
 else{
 root->left = new TreeNode(JourneyCode, price);
 root->left->parent = root;
 return true;
 }
 }
 if(root->price < price){
 if(root->right!=NULL){
 BST right_subtree(root->right);
 return right_subtree.insert(JourneyCode, price);
 }
 else{
 root->right = new TreeNode(JourneyCode, price);
 root->right->parent = root;
 return true;
 }
 } 
 return false;
}

//return ptr of tree node if given JourneyCode is present, nullptr otherwise
TreeNode* BST::location(int JourneyCode){
 if(root==NULL) return nullptr;
 if(root->JourneyCode == JourneyCode) return root;
 BST left_subtree(root->left), right_subtree(root->right);
 TreeNode* loc = left_subtree.location(JourneyCode);
 if(left_subtree.location(JourneyCode)!=nullptr) return loc;
 else{
 loc = right_subtree.location(JourneyCode);
 return loc;
 }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
 if(root==NULL) return false; 
 if(root->price==price && root->JourneyCode==JourneyCode){
 return true;
 }
 if(root->price < price){
 BST right_subtree(root->right);
 return right_subtree.find(JourneyCode, price); 
 }
 if(root->price>=price){
 BST left_subtree(root->left);
 return left_subtree.find(JourneyCode, price);
 } 
 return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
	//trivial case
	if(root==nullptr) return false;
	//if ticket is on left of root (if there is)
	if(root->price > price) {
		if (root->left==NULL) return false;
		BST left_subtree(root->left);
		return left_subtree.remove(JourneyCode, price);
	}
	//if ticket is on right of root (if there is)
	if(root->price < price){
		if (root->right == nullptr) return false;
		BST right_subtree(root->right);
		return right_subtree.remove(JourneyCode, price);
	}
	if(root->price==price){
	//if ticket has same price but different JourneyCode, it is in the left subtree (convention of insertion)
		if(root->JourneyCode!=JourneyCode){
		if(root->left==nullptr) return false;
		BST left_subtree(root->left);
		return left_subtree.remove(JourneyCode, price);
 		}
		//this means that current node (root) is the ticket
		else{
		//if root is a leaf
			if((root->left==nullptr) && (root->right==nullptr)){
			if(root->parent==nullptr){ //if we are removing the only node in tree
			root = nullptr;
			return true;
 	}
	//if leaf is on left of parent
	if (root->price <= root->parent->price) {
		root->parent->left = nullptr;
		delete root;
		return true;
		}
	//if leaf is on the right of parent
	if (root->price > root->parent->price){
	root->parent->right = nullptr;
	delete root;
	return true;
	}
	}
	//if root has one child
	if(root->left==nullptr){
	//if node is root of tree
	if(root->parent==nullptr){
	root=root->right;
	root->parent=nullptr;
	return true;
	}
	//if node is on left of parent
	if (root->price <= root->parent->price) {
	root->parent->left = root->right;
	root->right->parent=root->parent;
	delete root;
	return true;
	}
	//if node is on the right of parent
	if (root->price > root->parent->price){
	root->parent->right = root->right;
	root->right->parent=root->parent;
	delete root;
	return true;
	}
	}
	if(root->right==nullptr){
	//if node is root of tree
	if(root->parent==nullptr){
	root=root->left;
	root->parent=nullptr;
	return true;
	}
	//if node is on left of parent
	if (root->price <= root->parent->price) {
	root->parent->left = root->left;
	root->left->parent=root->parent;
	delete root;
	return true;
	}
	//if node is on the right of parent
	if (root->price > root->parent->price){
	root->parent->right = root->left;
	root->left->parent=root->parent;
	delete root;
	return true;
	}
	}
	
	//if root has 2 children
	//locating node in left with highest price
	TreeNode* pred = root->left;
	while(pred->right!=nullptr){
	pred=pred->right;
	}
	//pred is left child of node
	if(pred==root->left){
	//parent of pred
	root->right->parent=pred;
	//updating child of parent
	if (root->parent!=nullptr){
	//root is left child of parent
	if (root->price <= root->parent->price){
	root->parent->left=pred;
	}
	//root is right child of parent
	if (root->price > root->parent->price){
	root->parent->right=pred;
	}
	}
	//parent of right child
	root->right->parent=pred;
	return true; 
	}

	// //if node is root of tree
	// if (root->parent==nullptr);
	// root->right->parent=pred;
	// root->left->parent=pred;

	//now, pred is for sure rightmost point of left subtree
	pred->parent->right=pred->left;
	if(pred->left!=nullptr) pred->left->parent=pred->parent;
	//if root has no parent
	if(root->parent==nullptr){
	if(root->right!=nullptr) root->right->parent=pred;
	root->left->parent=pred;
	pred->right=root->right;
	pred->left=root->left;
	pred->parent=nullptr;
	delete root;
	return true;
	}
	//root is in left of parent
	if(root->price <= root->parent->price){
	root->parent->left = pred;
	root->left->parent = pred;
	if(root->right!=nullptr) root->right->parent = pred;
	pred->right=root->right;
	pred->left=root->left;
	pred->parent=root->parent;
	}
	//root right of parent
	if(root->price > root->parent->price){
	root->parent->right = pred;
	root->left->parent = pred;
	if(root->right!=nullptr) root->right->parent = pred;
	pred->right=root->right;
	pred->left=root->left;
	pred->parent=root->parent;
	}
	delete root;
	return true;
	}
	}
	return true;
	}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
 //preorder traversal
 if (typeOfTraversal==PRE_ORDER){
 if(root==nullptr) return;
 else{
 cout<<root->JourneyCode<<endl;
 BST left_subtree(root->left);
 left_subtree.traverse(typeOfTraversal);
 BST right_subtree(root->right);
 right_subtree.traverse(typeOfTraversal);
 }
 }
 //post order
 if (typeOfTraversal==POST_ORDER){
 if(root==nullptr) return;
 else{
 BST left_subtree(root->left);
 left_subtree.traverse(typeOfTraversal);
 BST right_subtree(root->right);
 right_subtree.traverse(typeOfTraversal);
 cout<<root->JourneyCode<<endl; 
 }
 }
 //in order
 if (typeOfTraversal==IN_ORDER){
 if(root==nullptr) return;
 else{
 BST left_subtree(root->left);
 left_subtree.traverse(typeOfTraversal);
 cout<<root->JourneyCode<<endl;
 BST right_subtree(root->right);
 right_subtree.traverse(typeOfTraversal); 
 }
 } 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
 if(root==nullptr) return 0;
 if(root->left==nullptr) return root->price;
 BST left_subtree(root->left);
 return left_subtree.getMinimum();
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
 int count=0;
 if(root==nullptr){
 return count;
 }
 else if(root->price<=upperPriceBound && root->price>=lowerPriceBound){
 count++;
 if(root->right!=nullptr){
 BST right_tree(root->right);
 count+=right_tree.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
 } 
 
 if(root->left!=nullptr){
 BST left_tree(root->left);
 count+=left_tree.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
 }
 }
 else if(root->price<lowerPriceBound && root->right!=nullptr){
 BST right_tree(root->right);
 count+=right_tree.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
 }
 else if(root->price>upperPriceBound && root->left!=nullptr){
 BST left_tree(root->left);
 count+=left_tree.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
 }

 return count; 
}

// Store the current tree in a file called filename. You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements. You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    ofstream book;
    book.open(filename);
    storeHelper(book);
    return; 
}

void BST::storeHelper(ofstream &book){
	if(root==nullptr) return;
    else{
    book<<root->JourneyCode<<" "<<root->price<<" ";
	if(root->left!=nullptr){
		BST left_subtree(root->left);
		left_subtree.storeHelper(book);
	}
	if(root->right!=nullptr){
		BST right_subtree(root->right);
		right_subtree.storeHelper(book);
		}
	}

	return;
}

// While loading a tree from a file written by customStore, we
// can have one of two modes of loading. We could either ask
// for the entire tree to be loaded or only the left subtree of
// the root (if it exists) to be loaded. The loadMode flag
// takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// that are #defined in BST.cpp.
// If loadMode is LOAD_FULL_BST, customLoad should load the
// entire BST that was stored in filename using customStore.
// If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// only the left subtree of the root of the BST that was
// stored in filename using customStore.
// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded. So, for example, if the
// left sub-tree of the root is small compared to the right
// sub-tree, customLoad's time and space complexity should
// be small even though the entire BST may be very large.
 
void BST::customLoad (int flag, string filename) { 
    ifstream book;
    book.open(filename);
    unsigned int nextJourney, nextprice;
    while(!book.eof()){
		book>>nextJourney>>nextprice;
		if(book.eof()) break;
        insert(nextJourney,nextprice);
    }
	if(flag==LOAD_LEFT_SUBTREE) root=root->left;
    return; 
}


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
 printBST( prefix + (isLeft ? "│ " : " "), true);
 root = curr->right;
 printBST( prefix + (isLeft ? "│ " : " "), false);
 root = curr;
 }
}

void BST::getBST(const string& prefix, bool isLeft=false)
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
 getBST( prefix + (isLeft ? "│ " : " "), true);
 root = curr->right;
 getBST( prefix + (isLeft ? "│ " : " "), false);
 root = curr;
 }
}

void BST::clearResult(){
 result.clear();
}

vector<string> BST::getResult(){
 return result;
}

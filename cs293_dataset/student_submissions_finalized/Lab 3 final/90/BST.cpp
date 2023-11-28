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

// Assumpion:  Two Journey Codes can't be the same. But two different journey code, may have the same price.

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS
BST::BST(){
	root = NULL;	
}

BST::BST(TreeNode *root){ 
	this->root = root;
}

// Return True, if the ticket with given attributes is found, false otherwise
//Recursive Implementation
bool BST::find(int JourneyCode, int price) { 

	//If root is null, then it is an empty tree, simply return false.
	if(root==NULL) return false;
	
	//If the price is the same as the reqd price, then compare the 
	//Journey Codes, if they are same, then return true.
	//else check for the pair only at the right subtree of the root
	if(root->price==price){
		if(root->JourneyCode==JourneyCode) return true;
		BST T2(root->right);
		return T2.find(JourneyCode, price);
	}
	
	//If the root's price is less than the reqd price, then search only
	// in the right subtree.
	if(root->price<price){
		BST T2(root->right);
		return T2.find(JourneyCode, price);
	}
	
	// If the root's price is greater than the reqd price, then search only
	// in the left subtree.
	BST T1(root->left);
	return T1.find(JourneyCode, price);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 

	if(find(JourneyCode, price)) return false;
	
	//Iteratively finding the required node, and in the process
	//also the parent of the reqd node.
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
//This just keeps moving to the left until you find a node
//with no left child.This node is the minimum we require
int BST::getMinimum(){
	int min_price = root->price;
	if(root->left == NULL) return min_price;
	BST T1(root->left);
	return T1.getMinimum();
}


// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
	//When the required Node doesn't exists
	if(!find(JourneyCode, price)) return false;
	
	//When the root itself is the required node
	if(root->JourneyCode==JourneyCode && root->price==price){
		root = NULL;	
		return true;	
	}
	else{
		//Iteratively finding the required node and its parent.
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
		
		//If the current node is a leaf, that is it has no children
		//Then simply delete the element
		if(curr->right == NULL && curr->left == NULL){
			if(curr_parent->price<=price) curr_parent->right = NULL;
			else curr_parent->left = NULL;
		}
		
		//If the current node has only one child
		//That is one of the sides(right or left) is a NULL
		//Then link the node's parent and child, thereby removing the node
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
		
		//If the current Node has two children.
		//That means both the sides, right and left are not empty.
		//Firstly, delete the successor node of the current node using
		//either one of the previous two cases, depending on the case.
		//Then replace the current node with journey code and price values
		//as that of the succesor.
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
	

//Recursively printing the preorder traversal
void BST::preorder(){
	if(root==NULL) return;
	cout << root->JourneyCode << endl ;
	BST T1(root->left);
	BST T2(root->right);
	T1.preorder();
	T2.preorder();
	return;
}

//Recursively printing the postorder traversal
void BST::postorder(){
	if(root==NULL) return;
	BST T1(root->left);
	BST T2(root->right);
	T1.postorder();
	T2.postorder();
	cout << root->JourneyCode << endl;
	return;
}

//Recursively printing the inorder traversal
void BST::inorder(){
	if(root==NULL) return;
	BST T1(root->left);
	BST T2(root->right);
	T1.inorder();
	cout << root->JourneyCode << endl ;
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
			cout << endl;
			break;
		case 1: postorder();
			cout << endl;
			break;
		case 2: inorder();
			cout << endl;
	}
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {

	//When the root is NULL, return 0
	if(root==NULL) return 0;
	
	//When the root price lies in between the lowerBound and upperBound
	//with upper price bound inclusive, in accordance to our insertion
	//assumption that elements to the right of a node are either'
	//greater than or equal to it, and those to the left are strictly smaller.
	//then recursively count journeys on left and right
	// and return the sum of counts on left and right plus 1
	if(lowerPriceBound < root->price && upperPriceBound >= root->price){
		BST T1(root->left);
		BST T2(root->right);
		int count1 = T1.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
		int count2 = T2.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
		return 1 + count1 + count2;
	}
	
	//When the root price is equal to the lowerBound, then search only right.
	//Again in accordance to our insertion assumption.
	//Return the counts obtained from right subtree plus 1
	else if(lowerPriceBound == root->price){
		BST T1(root->right);
		return 1 + T1.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
	}
	
	//When root price is less than the lower bound, then directly return the 
	// count of the right subtree.
	else if(lowerPriceBound > root->price){
		BST T1(root->right);
		return T1.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
	}
	
	//When the root price is greater than the upper bound, then directly return the
	// count of the left subtree. 
	else{
		BST T2(root->left);
		return T2.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
	}	
}

// You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
//==========================//
//We store it the same way as the preorder, with some modifications.
//Store each node as two values Journey Code and Price.
//NULL nodes are stored as "n n". 
void recursiveStore(TreeNode* root, string &s) {
	if (root == NULL){
		s += "n n ";
		return;
	}
	s += to_string(root->JourneyCode) + " " + to_string(root->price) + " ";
	recursiveStore(root->left, s);
	recursiveStore(root->right, s);
}


//Given the root, this function calls a recursive encoder, that means
//it stores the entire BST in the form of a string. This storing
// is done in such a way that retrieving information out of it is 
// easier and is of less time complexity. The length of the string 
// is of O(n), matching the problem specifications.
string BST::encode(TreeNode* root) {
	string s;
	recursiveStore(root, s);
	return s;
}

// Storing the current tree in a file called filename.  
void BST::customStore(string filename) { 
	ofstream outfile;
	outfile.open(filename);
	outfile << encode(root);
	outfile.close();
}

// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded.  So, for example, if the
// left sub-tree of the root is small compared to the right
// sub-tree, customLoad's time and space complexity should
// be small even though the entire BST may be very large.
//=============================//
// We extract the data from a queue, pop out the first two places
// We then recursively load for the left subtree, we stop when we encounter 
// Sufficient Nulls to end the left subtree.
// We then recursively load the right subtree.
TreeNode* recursiveLoad(queue<string> &q){
	string front_JC = q.front();
	q.pop();
	string front_P = q.front();
	q.pop();
	if (front_JC == "n" and front_P == "n") return NULL;
	TreeNode* root = new TreeNode(stoi(front_JC),stoi(front_P));
	root->left = recursiveLoad(q);
	root->right = recursiveLoad(q);
	return root;
}
 
// Given a compact string which was encoded by the earlier function,
// This function decodes/retrieves data with time complexity of O(n).
void BST::decode(string compact_data) {
	istringstream iss(compact_data);
	queue<string> q;
	for (string a; iss >> a;) q.push(a);
	root = recursiveLoad(q);
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
//================================//
//For flag=4, we are interested only in values to the left of 
//root. So we stop reading in values the moment we encounter
//a node with equal to or larger price than our root price.
void BST::customLoad (int flag, string filename){
		ifstream infile;
		infile.open(filename);
		string s="",JC,P;
		infile >> JC >> P;
		s += JC;
		s += " ";
		s += P;
		s += " ";
		int P_start = stoi(P);
		while(infile >> JC >> P){
			if(flag==4 && P != "n"){
				if(stoi(P)>=P_start) break;
			}
			s += JC;
			s += " ";
			s += P;
			s += " ";	
		}
		infile.close();
		if(flag==4) s += "n n ";
		decode(s);	
}

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
        result.push_back(to_string(root->JourneyCode) + "\n");
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

/*
ADD 1 100
ADD 2 250
ADD 3 175
ADD 4 230
ADD 5 150
ADD 6 320
ADD 7 230
ADD 8 160
ADD 9 600
ADD 10 420
ADD 11 219
ADD 12 270
*/


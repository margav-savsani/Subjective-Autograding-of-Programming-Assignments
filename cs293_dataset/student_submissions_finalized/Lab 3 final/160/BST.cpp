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

BST::BST(){root=NULL; }
BST::BST(TreeNode *root){this->root=root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
	if(root==NULL){
		root=new TreeNode(JourneyCode,price,NULL,NULL,NULL);return true;
	}
	else{
		TreeNode *prev=NULL;
		TreeNode *temp=root;
		while(temp!=NULL){
			if(temp->JourneyCode==JourneyCode){
				return false;
			}
			else if(temp->price>=price){
				prev=temp;
				temp=temp->left;
			}
			else if(temp->price<price){
				prev=temp;
				temp=temp->right;
			}
		}
		if (prev->price>price) prev->left =new TreeNode(JourneyCode,price,NULL,NULL,prev);
		else prev->right =new TreeNode(JourneyCode,price,NULL,NULL,prev);
		return true;
	}
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
	if(root==NULL) return false;
	if(root->price==price){
		if(root->JourneyCode==JourneyCode) return true;
	}
	TreeNode *prev=NULL;
	TreeNode *temp=root;
	while(temp!=NULL){
		if(temp->price>=price){
			prev=temp;
			temp=temp->left;
		}
		else if(temp->price<price){
			prev=temp;
			temp=temp->right;
		}
		if((prev->JourneyCode==JourneyCode)&&(prev->price==price)) return true;
	}
	return false;	

}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
	if(find(JourneyCode,price)) {
		root=deleteNode(root,price,JourneyCode);
		return true;}
	return false;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
	if(typeOfTraversal==0){
		printPreorder(root);
	}
	else if(typeOfTraversal==1){
		printPostorder(root);
	}
	else{
		printInorder(root);
	}
	return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
	TreeNode *temp=root;int p;
	while(temp!=NULL){
		p=temp->price;
		temp=temp->left;
	}

	return p;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
	return getCount(root,lowerPriceBound,upperPriceBound); 
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
	storePreorder(root,filename);
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




void BST::customLoad (int flag, string filename) { 

	int* code;
	int* price;
	code = new int[1000];
	price = new int[1000];
	int index = 0;
	ifstream p;
	int i=0;
	p.open(filename);
	p>>code[0];
	p>>price[0];
	while(!p.eof()){

		i++;
		p>>code[i];
		p>>price[i];
	}	

	p.close();	

	if( flag==LOAD_FULL_BST){

		root = construct(code,price, &index, price[0], -1, 9000000, i+1);
	}
	else {

		root->left = construct(code,price, &index, price[0], -1, 9000000, i+1);
	}

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

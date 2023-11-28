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
	root = NULL;
}
BST::BST(TreeNode *r){
	this->root = r;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
	/*TreeNode *z = new TreeNode(JourneyCode, price);
	TreeNode *x = root, *y = NULL;
		while ( x != NULL ){
			y = x;
			if ( x->JourneyCode == JourneyCode && x->price == price) return false;
			if ( price < x->price )
				x = x->left;
			if ( price > x->price )
				x = x->right;
		}
	if ( y != NULL ){
		if ( price < y->price )
		{
			cout << "reaching ..." << endl;
			y->left = z;
			z->parent = y;
		}
		else
		{
			cout << "reaching price > y-price" <<endl;
			y->right = z;
			z->parent = y;
		}
	}
	if ( y == NULL ){
                root = new TreeNode();
                root->JourneyCode = JourneyCode;
                root->price = price;
        }
	return true;
	*/	TreeNode *x = root, *y = NULL;
	while ( x != NULL ){
		y = x;
	if ( x->JourneyCode == JourneyCode && x->price == price) return false;
		if (x->price > price)
			x = x->left;
		if (x->price < price)
        	        x = x->right;
	} 
	if ( y != NULL){
	if ( y->price > price ) {
		(y->left) = new TreeNode();
		(y->left)->JourneyCode = JourneyCode;
		(y->left)->price = price;
		(y->left)->parent = y;
		(y->left)->left = NULL; 
                (y->left)->right = NULL;
        }
	if ( y->price < price) {
		(y->right) = new TreeNode();
		(y->right)->JourneyCode = JourneyCode;
                (y->right)->price = price;
		(y->right)->parent = y;
		(y->right)->left = NULL;
		(y->right)->right = NULL;
	}}
	if ( y == NULL ){
		root = new TreeNode();
		root->JourneyCode = JourneyCode;
		root->price = price;
	}
	return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
	if ( root == NULL || root->JourneyCode == JourneyCode ) return true;
	if ( root->price < price ) return find((root->right)->JourneyCode, (root->right)->price);
	if ( root->price > price ) return find((root->left)->JourneyCode, (root->left)->price);
	/*while (x != nullptr){
		if (x->JourneyCode==JourneyCode && x->price==price) return true;
		else {
			if (x->price > price)
				x = x->left;
			else if (root->price < price)
                                x = x->right;
		}
	}*/
	return false;  
}

struct TreeNode* BST::get(int JourneyCode, int price) { 
	TreeNode *x = root;
	while (x != nullptr){
                if (x->JourneyCode==JourneyCode && x->price==price) return root;
                else {
                        if (x->price>price)
                                root = root->left;
                        if (x->price<price)
                                root = root->right;
                }
	}	
        return NULL;   
}


// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
	int s=1;
	if (!find(JourneyCode, price)){
		s=0;
		return false;
	}
	else {
		TreeNode *trm = get(JourneyCode, price);
		if (trm->left==NULL && trm->right==NULL){
			if((trm->parent)->left==trm) ((trm->parent)->left)=NULL;
			if((trm->parent)->right==trm) ((trm->parent)->right)=NULL;
			return true;
		}
		else if (trm->left==NULL || trm->right==NULL){
			if(trm->left=NULL) int s=0;
			else int s=1;
			if(s==0){	
				if((trm->parent)->left==trm) ((trm->parent)->left)=trm->right;
                		if((trm->parent)->right==trm) ((trm->parent)->right)=trm->right;
				return true;
			}
			if(s==1){
                        	if((trm->parent)->left==trm) ((trm->parent)->left)=trm->left;
	                        if((trm->parent)->right==trm) ((trm->parent)->right)=trm->left;
        	        	return true;
			}
		}	
		else {
			TreeNode *scr=trm->right;
			while(scr->left != NULL){
				scr = scr->left;
			}
			(scr->parent)->left=scr->right;
			scr=trm;
			trm=NULL;
			return true;
		}
	}
	return false;
}
	

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
	TreeNode *x = root;
	while ( x != NULL){
	if ( typeOfTraversal == 0 ){
		cout << x->JourneyCode;
		{
			x = x->left;
			traverse(0);
			x = x->parent;
		}
		{
			x = x->right;
			traverse(0);
			x = x->parent;
		}
	}
	if ( typeOfTraversal == 1){
		{
                	x = x->left;
                        traverse(1);
                        x = x->parent;
                }
		{
                        x = x->right;
                        traverse(1);
                        x = x->parent;
                }
		cout << x->JourneyCode;
	}
	if ( typeOfTraversal == 2){
                {   
                        x = x->left;
                        traverse(2);
                        x = x->parent;
                }
		cout << x->JourneyCode;
                {
                        x = x->right;
                        traverse(2);
                        x = x->parent;
                }
        }
	}
	return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
	TreeNode *M = root;
	while (M->left != NULL){
		M = M->left;
	}
	return M->price; 
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


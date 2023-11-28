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

BST::BST(){}

BST::BST(TreeNode *root){

	this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

TreeNode* insert2(TreeNode* root, int JourneyCode, int price){



	if( root == NULL){
	
		TreeNode* n= new TreeNode(JourneyCode,price);
		root = n;
		return root;
	}
	
	if( price > root->price){
	
		root->right = insert2(root->right, JourneyCode, price);

	}
	else if( price < root->price){
	
		root->left = insert2(root->left, JourneyCode, price);
	}
	
	return root;
}
	
	

bool BST::insert(int JourneyCode, int price) { 
	
	
	bool found = find(JourneyCode,price);
	
	if(found) return false;
	
	root = insert2(root, JourneyCode, price);
	
	return true;
}

// Return True, if the ticket with given attributes is found, false otherwise

bool find2( TreeNode* root, int JourneyCode, int price){

	if( root == NULL){
	
		return false;
	}

	if( root->price == price){
		
			return true;
	}
	
	else if( root->price < price){
	
		return find2(root->right, JourneyCode, price);
	}
	
	else if( root->price > price ){
	
		return find2(root->left, JourneyCode, price);
	}
	return false;
	
}

bool BST::find(int JourneyCode, int price) { 

	return find2(root, JourneyCode, price);
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

TreeNode* min2(TreeNode* root){

	if( root == NULL) return NULL;

	if ( root->left == NULL) return root;
	else return min2(root->left);
}

//the remove case into 3 cases
TreeNode* remove2(TreeNode* root, int JourneyCode, int price){

	if( root== NULL){
	
		return NULL;
	}

	if( root->price < price){
	
		root->right = remove2(root->right, JourneyCode, price);
	}
	else if( root->price > price){
	
		root->left = remove2(root->left, JourneyCode, price);
	}
	else {
	
		if( root->left == NULL && root->right == NULL){
		
			root = NULL;
		}
		else if(  root->left == NULL){
		
			root = root->right;
		}
		else if( root->right == NULL ){
		
			root = root->left;

		}
		else {
		
			struct TreeNode* a = min2(root->right);
			
			root->price = a->price;
			root->JourneyCode = a->JourneyCode;
			root->right = remove2(root->right, a->JourneyCode, a->price);
		}
	}
	
	return root;
}
			
			
			
		

bool BST::remove(int JourneyCode, int price) { 

	bool found = find2(root, JourneyCode, price);
	
	if(found == false ){
	
		return false;
		
	}
	else{
	
		root=remove2(root, JourneyCode, price);
	}
	return true;
}

	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void post(TreeNode* root){

	if( root == NULL){
	
		return;
	}
	
	post(root->left);
	
	post(root->right);
	
	cout<<root->JourneyCode<<endl;
}
void pre(TreeNode* root){

	if( root == NULL){
	
		return;
	}
	
	
	
	cout<<root->JourneyCode<<endl;
	pre(root->left);
	pre(root->right);

}

void in(TreeNode* root){

	if( root == NULL){
	
		return;
	}
	

	post(root->left);
	cout<<root->JourneyCode<<endl;
	post(root->right);

}


	
	
	

void BST::traverse(int typeOfTraversal) {

	if( typeOfTraversal == PRE_ORDER){
	
		pre(root);}
		
	else if( typeOfTraversal == POST_ORDER){
	
		post(root);
	}
	else if( typeOfTraversal == IN_ORDER ){
	
		in(root);
	}
	
}

// Returns the price of the cheapest journey
// the minimum price will be on left tree

int BST::getMinimum() {

	TreeNode* min = min2(root);
	 if(min == NULL) return 0;
	 else {
	 
	 	return min->price;
	 }
	return 0;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
//here also convereted into 3 cases 
int countjourneys(  int lower, int upper, TreeNode* root){

	if ( !root ) return 0;
	
	else if ( root->price>upper) return countjourneys(lower, upper, root->left);
	else if ( root->price<lower) return countjourneys(lower, upper, root->right);
	
	return 1+countjourneys(lower, upper, root->right)+countjourneys(lower, upper, root->left);
}

	
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {

	if( getMinimum() > upperPriceBound ) {
	
		return 0;
	}
	
	return countjourneys(lowerPriceBound, upperPriceBound, root);
	
 }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
// stored in pre-order traversal
void store(TreeNode* root, string filename){

	ofstream outfile ;
	outfile.open(filename, std::ios_base::app) ;
	
	if( root == NULL){
	
		return;
	}
	
	outfile<<root->JourneyCode << " ";
	outfile<<root->price<<endl;
	store(root->left, filename);
	
	store(root->right, filename);
	outfile.close();
}
	
void BST::customStore(string filename) { 

	ofstream outfile;
	outfile.open(filename);
	outfile.close();
	store(root, filename);
	
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

TreeNode* constructTreeUtil(int pre1[], int pre2[], int* preIndex, int key,
                        int min, int max, int size)
{
    // Base case
    if (*preIndex >= size)
		return NULL;
 
    TreeNode* root = NULL;
 
   
    if (key > min && key < max) {
       
        root = new TreeNode(pre1[*preIndex],pre2[*preIndex]);
        *preIndex = *preIndex + 1;
 
        if (*preIndex < size) {
           
            root->left = constructTreeUtil(pre1,pre2, preIndex,
                                           pre2[*preIndex],
                                           min, key, size);
        }
        if (*preIndex < size) {
    
            root->right = constructTreeUtil(pre1,pre2, preIndex,
                                            pre2[*preIndex],
                                            key, max, size);
        }
    }
 
    return root;
}
 

void BST::customLoad (int flag, string filename) { 
	
	// customStore(filename);
	int* pre1;
	int* pre2;
	pre1 = new int[10000];
	pre2 = new int[10000];
	int preIndex = 0;
	ifstream p1;
	int i=0;
	p1.open(filename);
	p1>>pre1[0];
	p1>>pre2[0];
	while(!p1.eof()){
	
		i++;
		p1>>pre1[i];
		p1>>pre2[i];
	}	
	
	p1.close();	
	
	if( flag==LOAD_FULL_BST){
		
		root = constructTreeUtil(pre1,pre2, &preIndex, pre2[0], -1, 200000, i+1);
	}
	else {
	
		root->left = constructTreeUtil(pre1,pre2, &preIndex, pre2[0], -1, 200000, i+1);
	}
	 
}


// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
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

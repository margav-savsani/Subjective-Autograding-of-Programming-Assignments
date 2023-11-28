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

BST::BST(){ this->root = NULL; }
BST::BST(TreeNode *root){ this->root = root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    TreeNode *y = NULL, *x = root; 

    while(x!=NULL && (x->JourneyCode != JourneyCode || x->price != price)){
        y = x;
        if (price < x->price) x = x->left;
        else x = x->right;
    }
    if (x!=NULL) return false;                              // if already present, return false

    TreeNode *z = new TreeNode(JourneyCode, price);

    z->parent = y;
    
    if (y==NULL) root = z;                                  // starting tree from scratch
    else if (price < y->price) y->left = z;
    else y->right = z;

    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *x = root;

    while (x!=NULL && (x->JourneyCode != JourneyCode || x->price != price)){
        if (price < x->price) x = x->left;
        else x = x->right;
    }

    if (x==NULL) return false;
    else return true; 
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode *main = root;

    while (main!=NULL && (main->JourneyCode != JourneyCode || main->price != price)){
        if (price < main->price) main = main->left;
        else main = main->right;
    }

    if (main==NULL) return false;
    else {
        TreeNode *x, *y;

        if (main->left == NULL || main->right == NULL) y = main;
        else y = successor(main);

        if (y->left != NULL) x = y->left;
        else x = y->right;
        
        if (x != NULL) x->parent = y->parent;
        
        if (y->parent == NULL) root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
        
        if (y != main) main->price = y->price;                                //copy all fileds of y
        return true;
    }
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if (typeOfTraversal == PRE_ORDER) pre_order_traversal(root);
    else if (typeOfTraversal == POST_ORDER) post_order_traversal(root);
    else if (typeOfTraversal == IN_ORDER) in_order_traversal(root);
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if (root == NULL) return INVALID_PRICE;
    TreeNode *x = root->left, *y = root;
    while(x!=NULL) {
        y = x;
        x = x->left;
    }
    return y->price;
}

void BST::pre_order_traversal(TreeNode *v){
    if (v==NULL) return;
    cout << v->JourneyCode << endl;
    pre_order_traversal(v->left);
    pre_order_traversal(v->right);
}

void BST::post_order_traversal(TreeNode *v){
    if (v==NULL) return;
    post_order_traversal(v->left);
    post_order_traversal(v->right);
    cout << v->JourneyCode << endl;
}

void BST::in_order_traversal(TreeNode *v){
    if (v==NULL) return;
    in_order_traversal(v->left);
    cout << v->JourneyCode << endl;
    in_order_traversal(v->right);
}

TreeNode * BST::successor(TreeNode *v){
    TreeNode *y = v->parent, *z = y->right;
    if (v->right != NULL) {
        TreeNode *x = v->right->left, *t=v->right;
        while(x!=NULL) {
            y = x;
            x = x->left;
        }
        return y;
    }
    while(y != NULL && z==y->right){
        z = y;
        y = y->parent;
    }
    return y;
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
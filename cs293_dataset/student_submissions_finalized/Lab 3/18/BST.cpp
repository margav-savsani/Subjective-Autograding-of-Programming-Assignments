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

BST::BST(){root = NULL; }
BST::BST(TreeNode *root){ this->root = root; }


struct TreeNode* BST::search(int JourneyCode, int price){
    /*TreeNode *x=root;
    if(x->price==price) return x;
    if(x->price<price){
        x=x->left;
        BST A(x);
        return A.search(JourneyCode,price);
    }
    else{
        x=x->right;
        BST B(x);
        return B.search(JourneyCode,price);
    }*/
    TreeNode *x = root;
    while(x!=NULL && price!=x->price){
        if(price<x->price) x=x->left;
        else x=x->right;
    }
    return x;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    if(search(JourneyCode,price!=NULL)) return true;
    return false;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
	if(root!=NULL) {
    if(find(JourneyCode, price)) return false;
    TreeNode z(JourneyCode, price);
    TreeNode *x,*y;
    y = NULL;
    x = root;
    while(x!=NULL){
        y=x;
        if(x->price>z.price) x=x->left;
        else x=x->right;
    }
    z.parent=y;
    if(y==NULL) root=&z;
    else if(z.price<y->price) y->left = &z;
    else y->right = &z;
    return true;
    }
    TreeNode x(JourneyCode, price);
    root=&x;
    return true;
}



struct TreeNode* BST::successor(int price){
    TreeNode *x;
    TreeNode *result;
    x=root;
    if(x->right!=NULL){
        x=x->right;
        BST A(x);
        result->price=A.getMinimum();
        return result;
    }
    TreeNode *parent=x->parent;
    while((parent!=NULL)&&(x==parent->right)){
        x=parent;
        parent=parent->parent;
    }
    return parent;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(!find(JourneyCode, price)) return false;
    TreeNode *x=search(JourneyCode,price);
    if((x->left==NULL)&&(x->right==NULL)){
        x=NULL;
    }
    if((x->left==NULL)&&(x->right!=NULL)){
        x->right->parent = x->parent;
    }
    if((x->left!=NULL)&&(x->right==NULL)){
        x->left->parent = x->parent;
    }
    if((x->left!=NULL)&&(x->right!=NULL)){
        TreeNode *succ=successor(price);
        remove(succ->JourneyCode,succ->price);
        x=succ;
    }
    return true; 
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==PRE_ORDER){ //preorder
        TreeNode *x=root;
        if(x==NULL) return;
        cout<<x->JourneyCode<<" ";
        TreeNode *y=x->left;
        BST A(y);
        A.traverse(PRE_ORDER);
        TreeNode *z=x->right;
        BST B(z);
        B.traverse(PRE_ORDER);
    }
    if(typeOfTraversal==(IN_ORDER)){ //inorder
        TreeNode *x=root;
        if(x==NULL) return;
        TreeNode *y=x->left;
        BST A(y);
        A.traverse(IN_ORDER);
        TreeNode *z=x->right;
        BST B(z);
        B.traverse(IN_ORDER);
        cout<<x->JourneyCode<<" ";
    }
    if(typeOfTraversal==(POST_ORDER)){ //postorder
        TreeNode *x=root;
        if(x==NULL) return;
        TreeNode *y=x->left;
        BST A(y);
        A.traverse(POST_ORDER);
        cout<<x->JourneyCode<<" ";
        TreeNode *z=x->right;
        BST B(z);
        B.traverse(POST_ORDER);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x=root;

    while(x->left != NULL){
        x = x->left;
    }
    return x->price;
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


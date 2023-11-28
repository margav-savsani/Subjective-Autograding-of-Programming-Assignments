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
    if(find(JourneyCode,price)) return false;
    TreeNode *newNode = new TreeNode(JourneyCode,price);
    TreeNode *y = nullptr;
    TreeNode *x = root;
    while(x != nullptr){
        y = x;
        if(newNode->price < x->price) x = x->left;
        else x = x->right;
    }
    newNode->parent = y;
    if(y == nullptr) root = newNode;
    else if(newNode->price < y->price) y->left = newNode;
    else y->right = newNode;
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode *x = new TreeNode();
    x = root;
    while(x != nullptr && JourneyCode != x->JourneyCode){       // see if journey code can be same, but pair unique
        if(price < x->price) x = x->left;
        else x = x->right;
    }
    if(x != nullptr) return true; 
    else return false;
}

struct TreeNode *BST::searchNode(int JourneyCode, int price) { 
    TreeNode *x = new TreeNode();
    x = root;
    while(x != nullptr && JourneyCode != x->JourneyCode){       // see if journey code can be same, but pair unique
        if(price < x->price) x = x->left;
        else x = x->right;
    }
    if(x != nullptr) return x; 
    else return nullptr; 
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    if(!find(JourneyCode,price)) return false;
    TreeNode *y = new TreeNode;
    TreeNode *x = new TreeNode;
    TreeNode *deleteNode = searchNode(JourneyCode,price);
    if(deleteNode->left == nullptr || deleteNode->right == nullptr){
        y = deleteNode;
    }
    else y = successor(deleteNode);
    if(y->left != nullptr) x = y->left;
    else x = y->right;
    if(x != nullptr) x->parent = y->parent;
    if(y->parent == nullptr) root = x;
    else if(y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    if(y != deleteNode){
        deleteNode->JourneyCode = y->JourneyCode;
        deleteNode->price = y->price;
    }
    return true;
}


struct TreeNode *BST::successor(TreeNode *v){
    if(v->right != nullptr){
        return minNode(v->right);
    }
    TreeNode *y = v->parent;
    while(y != nullptr && v == y->right){
        v = y;
        y = y->parent;
    }
    return y;
}

struct TreeNode *BST::minNode(TreeNode *v){
    while (v->left != nullptr){
        v = v->left;
    }
    return v; 
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == 0){
        preOrder(root);
    }
    else if(typeOfTraversal == 1){
        postOrder(root);
    }
    else if(typeOfTraversal == 2){
        inOrder(root);
    }
    return; 
}

void BST::preOrder(TreeNode *v){
    if(v == nullptr) return;
    else {
        cout << v->JourneyCode << endl;
        preOrder(v->left);
        preOrder(v->right);
        return;
    }
}

void BST::postOrder(TreeNode *v){
    if(v == nullptr) return;
    else {
        postOrder(v->left);
        postOrder(v->right);
        cout << v->JourneyCode << endl;
        return;
    }
}

void BST::inOrder(TreeNode *v){
    if(v == nullptr) return;
    else {
        inOrder(v->left);
        cout << v->JourneyCode << endl;
        inOrder(v->right);
        return;
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x = root;
    while (x->left != nullptr){
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


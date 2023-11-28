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
BST::BST(TreeNode *root){
    this->root;
    }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    TreeNode* tempp = NULL;
    TreeNode* tempn = root;
    while(tempn != nullptr){
        tempp = tempn;
        if(price == tempn->price && JourneyCode == tempn->JourneyCode){
            return false;
        }
        else if(price < tempn->price){
            tempn = tempn->left;
        }
        else{
            tempn = tempn->right;
        }
    }
    tempn->parent = tempp;
    if(tempp == nullptr){
        root->JourneyCode = JourneyCode;
        root->price = price;
    }
    else if(price < tempp->price){
        tempp->left = tempn;
    }
    else {
        tempp->right = tempn;
    }
    tempn->JourneyCode = JourneyCode;
    tempn->price = price;
    return true;
    }

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode* tempn;
    tempn = root;
    while(tempn!=nullptr && price!=tempn->price){
        if(price < tempn->price){
            tempn = tempn->left;
        }
        else{
            tempn = tempn->right;
        }
    }
    if(tempn->JourneyCode==JourneyCode && tempn->price==price){
        return true;
    }
    return false;
    }

TreeNode* BST::successor(TreeNode* node){
    if(!find(node->JourneyCode, node->price)) return NULL;
    if(node->right!=nullptr){
        node = node->right;
        while(node->left!=nullptr){
            node = node->left;
        }
        return node;
    }
    TreeNode* temp;
    temp = node->parent;
    while(temp!=nullptr && node==temp->right){
        node = temp;
        temp = temp->parent;
    }
    return temp;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    if(!find(JourneyCode, price)) return false;
    TreeNode* tempn;
    tempn = root;
    while(tempn!=nullptr && price!=tempn->price){
        if(price < tempn->price){
            tempn = tempn->left;
        }
        else{
            tempn = tempn->right;
        }
    }
    TreeNode* node;
    if(tempn->left==nullptr || tempn->right==nullptr){
        node = tempn;
    }
    else{
        node = successor(tempn);
    }
    if(node->left!=nullptr){
        tempn = node->left;
    }
    else{
        tempn = node->right;
    }
    if(tempn!=nullptr){
        tempn->parent = node->parent;
    }
    if(node->parent==nullptr){
        root = tempn;
    }
    else if(node == node->parent->left){
        node->parent->left = tempn;
    }
    else{
        node->parent->right = tempn;
    }
    if(node!=tempn){
        tempn->price = node->price;
        tempn->JourneyCode = node->JourneyCode;
    }
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::preorderTraverse(TreeNode* node){
    if(root==nullptr) return;
    else{
        cout<<root->JourneyCode<<endl;
        preorderTraverse(root->left);
        preorderTraverse(root->right);
    }
} 
void BST::postorderTraverse(TreeNode* node){
    if(root==nullptr) return;
    else{
        preorderTraverse(root->left);
        preorderTraverse(root->right);
        cout<<root->JourneyCode<<endl;
    }
} 
void BST::inorderTraverse(TreeNode* node){
    if(root==nullptr) return;
    else{
        preorderTraverse(root->left);
        cout<<root->JourneyCode<<endl;
        preorderTraverse(root->right);
    }
} 

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0){
        preorderTraverse(root);
    }
    else if(typeOfTraversal==1){
        postorderTraverse(root);
    }
    else{
        inorderTraverse(root);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* node;
    node = root;
    if(node==nullptr) return -1;
    while(node->left!=nullptr){
        node = node->left;
    }
    return node->price;
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


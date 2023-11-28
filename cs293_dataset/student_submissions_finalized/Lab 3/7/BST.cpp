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

BST::BST(){;}
BST::BST(TreeNode *root){
    
    this->root = root;
    
}

bool BST::recurse_insert(int JourneyCode, int price, TreeNode *node){   // extra function
    if((node != NULL)&&(node->JourneyCode == JourneyCode)){
        return false;
    }
    
    else if(node == NULL){
        node->JourneyCode = JourneyCode;
        node->price = price;
        return true;
    }
    else if(price<= node->price){   // have kept equal to in left
        return recurse_insert(JourneyCode,price,node->left);
    }
    else if(price> node->price){
        return recurse_insert(JourneyCode,price,node->right);
    }
    
    return false;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    
    
    return this->recurse_insert(JourneyCode,price,this->root);
    
    return false;
    
}



bool BST::recurse_find(int JourneyCode, int price, TreeNode *node){
    if((node != NULL)&&(node->JourneyCode == JourneyCode)&&(node->price == price)){
        return true;
    }
    else if(price<=node->price){  // have kept equal to in left
        return this->recurse_find(JourneyCode,price,node->left);
    }
    else if(price>node->price){
        return this->recurse_find(JourneyCode,price,node->right);
    }
    
    return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    
    return recurse_find(JourneyCode,price,this->root);
    
    return false;
    
}


bool BST::largest(TreeNode *del_node, TreeNode *node){  // extra function removes the required element.
    if((node->right == NULL)&&(node->left == NULL)){
        del_node = node;
        node = NULL;
        return true;
    }
    
    else if((node->right == NULL)&&(node->left != NULL)){
        del_node = node;
        node = node->left;
        return true;
    }
    else return largest(del_node,node->right);
}


bool BST::recurse_remove(int JourneyCode, int price, TreeNode *node){
    if(node == NULL){
        return false;
    }
    else if((node->JourneyCode == JourneyCode)&&(node->price == price)&&(node->left == NULL)&&(node->right == NULL)){   // case 1: when it doesnot have any child
        node = NULL;
        return true;
    }

    else if((node->JourneyCode == JourneyCode)&&(node->price == price)&&(node->left == NULL)&&(node->right != NULL)&&(node->right->right == NULL)&& (node->right->left)){  // when it has exactly one child(right).
        
        node = node->right;
        node->right = NULL;
        return true;
    }
    
    else if((node->JourneyCode == JourneyCode)&&(node->price == price)&&(node->left != NULL)&&(node->right == NULL)&&(node->left->right == NULL)&& (node->left->left)){  // when it has exactly one child(left).
        
        node = node->left;
        node->left = NULL;
        return true;
    }
    
    else if((node->JourneyCode == JourneyCode)&&(node->price == price)){ //using predecessor to delete the JourneyCode by replacin it with predecessor(largest element in the left subtree)
        largest(node,node->left);
        
    }
    
    
    else if(price <= node->price){
        return this->recurse_remove(JourneyCode,price,node->left);
    }
    
    else if(price > node->price){
        return this->recurse_remove(JourneyCode,price,node->right);
    }
    
    return false;
    
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { return false; }




void BST::recurse_traverse_0(TreeNode *node){   // extra function
    cout << node->JourneyCode << endl;
    recurse_traverse_0(node->left);
    recurse_traverse_0(node->right);
}

void BST::recurse_traverse_1(TreeNode *node){
    recurse_traverse_1(node->left);
    recurse_traverse_1(node->right);
    cout << node->JourneyCode << endl;
}

void BST::recurse_traverse_2(TreeNode *node){
    recurse_traverse_2(node->left);
    cout << node->JourneyCode << endl;
    recurse_traverse_2(node->right);
}


	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    
    if(typeOfTraversal == PRE_ORDER){
        this->recurse_traverse_0(this->root);
    }
    else if(typeOfTraversal == POST_ORDER){
        this->recurse_traverse_1(this->root);
    }
    else if(typeOfTraversal == IN_ORDER){
        this->recurse_traverse_2(this->root);
    }
    
}


int BST::recurse_getMinimum(TreeNode *node){
    if(node->left == NULL){
        return node->price;
    }
    else {
        return this->recurse_getMinimum(node->left);
    }
}


// Returns the price of the cheapest journey
int BST::getMinimum() {
    
    return recurse_getMinimum(this->root);
    
    return 0;
    
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


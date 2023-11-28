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
    root = NULL; //empty tree
}
BST::BST(TreeNode *root){
    this->root = root; 
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if(root == NULL){ //inserting into an empty tree
        root = new TreeNode;
        root->JourneyCode = JourneyCode;
        root->price = price;
        return true;
    }
    if(find(JourneyCode, price)) return false; //journey pair exists
    TreeNode *current = root;
    TreeNode *parent = NULL;
    TreeNode *to_insert = new TreeNode(JourneyCode, price); //node to insert
    while(true){
        parent = current;
        //move parent to a child based on price
        if(price < current->price) current = current->left;
        else current = current->right;
        if(current == NULL) break;
        //reached a leaf
    }
    to_insert->parent = parent;
    //put node as left child if its price <
    //in right it >=
    if(price < parent->price) parent->left = to_insert;
    else parent->right = to_insert;
    return true;
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    if(root == NULL) return false;
    TreeNode* current = root;
    while(true){
        if(current->JourneyCode == JourneyCode && current->price == price) return true;
        else{
            if(price < current->price) current = current->left;
            else current = current->right;
        }
        if(current == NULL) return false;
        //reached a leaf, but pair not found
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    if(!find(JourneyCode, price)) return false;
    //pair doesn't exist
    TreeNode *node = root;
    //find the node to be removed
    while(true){
        if(node->JourneyCode == JourneyCode && node->price == price) break;
        else{
            if(price < node->price) node = node->left;
            else node = node->right;
        }
    }
    //is a leaf
    //make appropriate parent's child pointer NULL
    if(node->left == NULL && node->right == NULL){
        if(node == root){
            root = NULL; //empty tree now
            return true;
        }
        if(node->parent->left == node) node->parent->left = NULL;
        else node->parent->right = NULL;
        delete node;
        return true;
    }
    //if only one of the node's subtrees is non-empty, make its parent point to it.
    //if node is root, set the sub-tree's root as root
    if(node->right == NULL){
        if(node == root){
            delete root;
            root = node->left;
            return true;
        }
        if(node->parent->left == node) node->parent->left = node->left;
        else node->parent->right = node->left;
        node->left->parent = node->parent;
        delete node;
        return true;
    }
    if(node->left == NULL){
        if(node == root){
            delete root;
            root = node->right;
            return true;
        }
        if(node->parent->left == node) node->parent->left = node->right;
        else node->parent->right = node->right;
        node->right->parent = node->parent;
        delete node;
        return true;
    }
    //find the successor, (leftmost of right subtree (non-empty))
    TreeNode *succ = node->right;
    while(succ->left != NULL) succ = succ->left;
    //copy the values of the successor
    int price_succ = succ->price;
    int code_succ = succ->JourneyCode;
    //remove the successor node
    //cases based on if it has a parent (of whom it is a left child)
    //or if it is the right child of the node itself
    if(succ->left == NULL && succ->right == NULL){
        if(node->right == succ){
            node->right = NULL;
        }
        else succ->parent->left = NULL;
        delete succ;
    }
    else{
        if(node->right == succ){
            node->right = succ->right;
            succ->right->parent = node;
        }
        else{
            succ->parent->left = succ->right;
            succ->right->parent = succ->parent;
        }
        delete succ;
    }
    //a less efficient way to do it
    //remove(code_succ, price_succ);
    //replace node with the successor
    node->price = price_succ;
    node->JourneyCode = code_succ;
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

//recursive functions for traversal
void pre_ord(TreeNode *root){
    if(root == NULL) return;
    else{
        cout << root->JourneyCode << endl;
        pre_ord(root->left);
        pre_ord(root->right);
    }
}
void post_ord(TreeNode *root){
    if(root == NULL) return;
    else{
        post_ord(root->left);
        post_ord(root->right);
        cout << root->JourneyCode << endl;
    }
}
void in_ord(TreeNode *root){
    if(root == NULL) return;
    else{
        in_ord(root->left);
        cout << root->JourneyCode << endl;
        in_ord(root->right);
    }
}
void BST::traverse(int typeOfTraversal) {
    //call the three appropriately
    if(typeOfTraversal == PRE_ORDER) pre_ord(root);
    else if(typeOfTraversal == POST_ORDER) post_ord(root);
    else if(typeOfTraversal == IN_ORDER) in_ord(root);
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    //move left till leaf not found
    TreeNode *current = root;
    while(current->left != NULL){
        current = current->left;
    }
    return current->price;
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
        cout << root->price << endl;
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


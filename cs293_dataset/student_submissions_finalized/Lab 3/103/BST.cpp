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

BST::BST(){; }
BST::BST(TreeNode *root) : root(root) {; } // use initialiser list to initialise object

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    TreeNode* cparent = NULL; // cparent refers to current parent
    TreeNode* cnode = root; // cnode refers to current node

    while(cnode != NULL){ // as long as cnode is not NULL
        cparent = cnode; // move cparent down to cnode
        if(price < cnode->price) // if price is lower than cnode's price
            cnode = cnode->left; // set cnode to its left child
        else if(price == cnode->price && JourneyCode == cnode->JourneyCode) // if cnode is the required node
            return false; // node already exists in the tree
        else
            cnode = cnode->right; // set cnode to its right child
    }

    // create the new node
    TreeNode* newNode = new TreeNode();
    newNode->parent = cparent;
    newNode->JourneyCode = JourneyCode;
    newNode->price = price;
    if(cparent == NULL) // if cparent is NULL
        root = newNode; // set newNode to be the root
    else if(newNode->price < cparent->price) // if newNode's price is lower than that of cparent
        cparent->left = newNode; // set newNode to be the left child of cparent
    else
        cparent->right = newNode; // set newNode to be the right child of cparent
    
    return true; // insertion successfull
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode* foundNode = findHelper(JourneyCode, price, root); // call required helper function
    if(foundNode != NULL)
        return true;
    else
        return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode* z = findHelper(JourneyCode, price, root); // find the required node
    if(z == NULL){ // if the node is not present in the three
        return false;
    }

    // algorithm adapted from the NPTEL slides of Dr. Naveen Garg
    TreeNode* x;
    TreeNode* y;
    if(z->left == NULL || z->right == NULL)
        y = z;
    else
        y = successor(z);
        
    if(y->left != NULL)
        x = y->left;
    else
        x = y->right;
        
    if(x != NULL)
        x->parent = y->parent;
        
    if(y->parent == NULL)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
        
    if(y != z){
        z->JourneyCode = y->JourneyCode;
        z->price = y->price;
    }

    return true; // deletion successfull
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    traverseHelper(typeOfTraversal, root); // call required helper function
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    // if there is no root node, return -1
    if(root == NULL)
        return -1;
    
    TreeNode* cnode = root;
    while(cnode->left != NULL){ // go to left child as long as left child exists
        cnode = cnode->left;
    }

    return cnode->price; // return price of minimum node
}

// New functions

// Helper function for implementing FIND
TreeNode* BST::findHelper(int JourneyCode, int price, TreeNode* cnode){
    // if the current node is NULL, return NULL
    if(cnode == NULL)
        return NULL;
    
    if(cnode->price == price)     // if the price of the current node matches
        if(cnode->JourneyCode == JourneyCode)
            return cnode;
        else
            return findHelper(JourneyCode, price, cnode->right);
    else if(price < cnode->price) // if the price is lower, go ot left subtree
        return findHelper(JourneyCode, price, cnode->left);
    else // else go to right subtree
        return findHelper(JourneyCode, price, cnode->right);
}

// Helper function for implementing TRAVERSE
void BST::traverseHelper(int typeOfTraversal, TreeNode* cnode){
    // if the current node is NULL, return NULL
    if(cnode == NULL)
        return;

    if(typeOfTraversal == PRE_ORDER){ // preorder traversal
        cout << cnode->JourneyCode << endl; // print journeyCode at node
        traverseHelper(typeOfTraversal, cnode->left); // traverse left subtree
        traverseHelper(typeOfTraversal, cnode->right); // traverse right subtree
    } else if(typeOfTraversal == POST_ORDER){ // postorder traversal
        traverseHelper(typeOfTraversal, cnode->left); // traverse left subtree
        traverseHelper(typeOfTraversal, cnode->right); // traverse right subtree
        cout << cnode->JourneyCode << endl; // print journeyCode at node
    } else if(typeOfTraversal == IN_ORDER){ // inorder traversal
        traverseHelper(typeOfTraversal, cnode->left); // traverse left subtree
        cout << cnode->JourneyCode << endl; // print journeyCode at node
        traverseHelper(typeOfTraversal, cnode->right); // traverse right subtree
    }
}

// Function for finding the successor of a node
TreeNode* BST::successor(TreeNode* node){
    if(node->right != NULL){ // if there is a right subtree
        // find minimum node of right subtree
        TreeNode* cnode = node->right;
        while(cnode->left != NULL){
            cnode = cnode->left;
        }
        return cnode;
    }

    // find lowest common ancestor with left child as common ancestor
    TreeNode* cnode = node;
    TreeNode* cparent = node->parent;
    while(cparent != NULL && cnode == cparent->right){
        cnode = cparent;
        cparent = cnode->parent;
    }
    return cparent;
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

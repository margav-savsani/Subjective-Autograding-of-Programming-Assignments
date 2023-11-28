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
    this -> root = root;
 }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    TreeNode* z = new TreeNode;
    z->JourneyCode = JourneyCode;
    z->price = price; 
    TreeNode* y = NULL, *x = root;
    while(x != NULL){
        y = x;
        if (z->price < x->price)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if(y == NULL){
        root = new TreeNode;
        root->JourneyCode = z->JourneyCode;
        root->price = z->price;
        return true;
    }
    else if(z->price < y->price){
        y->left = z;
        return true;
    }
    else{
        y->right = z;
        return true;
    }
    if(y->JourneyCode == z->JourneyCode)
        return false;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    TreeNode* x = root;
    while(x != NULL && price != x->price){
        if(price < x->price)
            x = x->left;
        else
            x = x->right;
    }
    return (x != NULL ? true : false);
 }
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    TreeNode* x = root;
    while(x != NULL && price != x->price){
        if(price < x->price)
            x = x->left;
        else
            x = x->right;
    }
    if(x == NULL)
        return false;
    if(x->left == NULL && x->right == NULL){
        if(x->parent != NULL){
            if(x->parent->left != NULL){
                if(x->parent->left->JourneyCode == x->JourneyCode)
                    x->parent->left = NULL;
                else
                    x->parent->right = NULL;
            }
            else
                x->parent->right = NULL;
        }
        delete [] x;
    }
    else if(x->left != NULL && x->right != NULL){
        TreeNode* y = getMaximum(x->left);
        int tempJourneyCode = y->JourneyCode;
        int tempPrice = y->price;
        remove(tempJourneyCode, tempPrice);
        x->JourneyCode = tempJourneyCode;
        x->price = tempPrice;
    }
    else if(x->left != NULL){
        if(x->parent != NULL){
            x->left->parent = x->parent;
            if(x->parent->left != NULL){
                if(x->parent->left->JourneyCode == x->JourneyCode)
                    x->parent->left = x->left;
                else
                    x->parent->right = x->left;   
            }
            else
                x->parent->right = x->left;
        }
        else{
            x->left->parent = NULL;
            root = x->left;
        }
        x->parent = NULL;
        x->left = NULL;
        delete [] x;
    }
    else if(x->right != NULL){
        if(x->parent != NULL){
            x->right->parent = x->parent;
            if(x->parent->left != NULL){
                if(x->parent->left->JourneyCode == x->JourneyCode){
                    x->parent->left = x->right;
                }
                else
                    x->parent->right = x->right;
            }
            else{
                x->parent->right = x->right;
            }
        }
        else{
            x->right->parent = NULL;
            root = x->right;
        }
        x->parent = NULL;
        x->right = NULL;
        delete [] x;
    }
    return true;
}

TreeNode* BST::getMaximum(TreeNode* y){
    while (y->right != NULL)
        y = y->right;
    return y;
}
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) { 
    treeTraverse(root, typeOfTraversal);
}

void BST::treeTraverse(TreeNode* node, int typeOfTraversal){
    if(node -> left == NULL && node -> right == NULL)
        external(node, typeOfTraversal);
    else{
        left(node, typeOfTraversal);
        treeTraverse(node->left, typeOfTraversal);
        below(node, typeOfTraversal);
        treeTraverse(node->right, typeOfTraversal);
        right(node, typeOfTraversal);
    }
}

void BST::left(TreeNode* node, int typeOfTraversal){
    if (node == NULL)
        return;
    else{
        if(typeOfTraversal == PRE_ORDER)
            cout << node->JourneyCode << endl;
        return;
    }
}

void BST::right(TreeNode* node, int typeOfTraversal){
    if (node == NULL)
        return;
    else{
        if(typeOfTraversal == POST_ORDER)
            cout << node -> JourneyCode << endl;
        return;
    }
}

void BST::below(TreeNode* node, int typeOfTraversal){
    if (node == NULL)
        return;
    else{
        if(typeOfTraversal == IN_ORDER)
            cout << node -> JourneyCode <<endl;
        return;
    }
}

void BST::external(TreeNode* node, int typeOfTraversal){
    cout << node->JourneyCode << endl;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* x = root;
    if (x == NULL)
        return -1;
    while(x->left != NULL)
        x = x->left;
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

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

BST::BST() {
    root = NULL;
}
BST::BST(TreeNode *root) {
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
    if(find(JourneyCode, price))
        return false;
    TreeNode *new_node, *null_node, *parent;
    new_node = new TreeNode(JourneyCode, price);
    if(root == NULL)
        root = new_node;
    else {
        parent = NULL;
        null_node = root;
        while(null_node != NULL) {
            parent = null_node;
            if(price < null_node->price)
                null_node = null_node->left;
            else
                null_node = null_node->right;
        }
        if(price < parent->price)
            parent->left = new_node;
        else
            parent->right = new_node;

        new_node->parent = parent;
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode* node = root;
    while(node != NULL) {
        if(price == node->price)
            return true;
        else if(price < node->price)
            node = node->left;
        else
            node = node->right;
    }
    return false;
}

TreeNode* BST::find(int JourneyCode, int price, int a) {
    TreeNode* node = root;
    while(node != NULL) {
        if(price == node->price)
            return node;
        else if(price < node->price)
            node = node->left;
        else
            node = node->right;
    }
    return NULL;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool BST::remove(int JourneyCode, int price) {
    TreeNode* node = find(JourneyCode, price, 0);
    if(!find(JourneyCode, price))
        return false;


    if(node->right == NULL && node->left == NULL) {
        if(node == root)
            root = NULL;
        else if(price < node->parent->price)
            node->parent->left = NULL;
        else
            node->parent->right = NULL;
    }
    else if(node->right != NULL) {
        if (node == root) {
            root = node->right;
            return true;
        }
        if(price < node->parent->price)
            node->parent->left = node->right;
        else
            node->parent->right = node->right;
        node->right->parent = node->parent;
    }
    else if(node->left != NULL) {
        if (node == root) {
            root = node->left;
            return true;
        }
        if(price < node->parent->price)
            node->parent->left = node->left;
        else
            node->parent->right = node->left;
        node->right->parent = node->parent;
    }
    else {
        TreeNode* pre = predecessor(node);
        node->price = pre->price;
        node->JourneyCode = pre->JourneyCode;
        if(pre->left == NULL)
            pre = NULL;
        else {
            pre->price = pre->left->price;
            pre->JourneyCode = pre->left->JourneyCode;
            pre->left = NULL;
        }
    }
    return true;
}

TreeNode* BST::successor(TreeNode* node) {
    TreeNode* suc = node;
    suc = suc->right;
    while (suc->left != NULL) 
        suc = suc->left;
    return suc;
}
TreeNode* BST::predecessor(TreeNode* node) {
    TreeNode* pre = node;
    pre = pre->left;
    while (pre->right != NULL) 
        pre = pre->right;
    return pre;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    TreeNode* node = root;
    if(typeOfTraversal == 0)
        preorder(node);
    else if(typeOfTraversal == 1)
        postorder(node);
    else if(typeOfTraversal == 2)
        inorder(node);
    else
        cout <<"ERROR\n";
    return;
}

void BST::inorder(TreeNode* node) {
    if(node == NULL)
        return;
    inorder(node->left);
    cout << node->JourneyCode << endl;
    inorder(node->right);
    return;
}

void BST::postorder(TreeNode* node) {
    if(node == NULL)
        return;
    postorder(node->left);
    postorder(node->right);
    cout << node->JourneyCode << endl;
    return;
}
void BST::preorder(TreeNode* node) {
    if(node == NULL)
        return;
    cout << node->JourneyCode << endl;
    preorder(node->left);
    preorder(node->right);
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode* node = root;
    while(node->left != NULL)
        node = node->left;
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


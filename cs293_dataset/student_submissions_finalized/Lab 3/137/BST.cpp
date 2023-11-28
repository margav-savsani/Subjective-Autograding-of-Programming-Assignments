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
    root = new TreeNode();
}
BST::BST(TreeNode *root){
    /*this->root->JourneyCode = root->JourneyCode;
    this->root->price = root->price;
    this->root->left = root->left;
    this->root->right = root->right;
    this->root->parent = root->parent;*/
    this->root = new TreeNode(root->JourneyCode,root->price,root->left,root->right,root->parent);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) { 
    if(root->JourneyCode == 0 && root->price == 0 && root->left == NULL && root->right == NULL)
    {
        root->JourneyCode = JourneyCode;
        root->price = price;
        return true;
    }
    if(root->price>=price)
    {
        if(root->left == NULL)
        {
            root->left = new TreeNode(JourneyCode, price);
            root->left->parent = root;
            return true;
        }
        else
        {
            BST root2(root->left);
            return root2.insert(JourneyCode, price);
        }
    }
    else if(root->price<price)
    {
        if(root->right == NULL)
        {
            root->right = new TreeNode(JourneyCode, price);
            root->right->parent = root;
            return true;
        }
        else
        {
            BST root2(root->right);
            return root2.insert(JourneyCode, price);
        }
    }
    if(root->JourneyCode == JourneyCode && root->price == price)
    {
        return false;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) { 
    if(root->JourneyCode == JourneyCode && root->price == price)
    {
        return true; 
    }
    else
    {
        if(root->price >= price && root->left != NULL)
        {
            BST root2(root->left);
            return root2.find(JourneyCode, price);
        }
        else if(root->price<price && root->right != NULL)
        {
            BST root2(root->right);
            return root2.find(JourneyCode, price);
        }
    }
    return false; 
}

struct TreeNode* BST::minimum(struct TreeNode* root){
    if(root->left == NULL)
    {
        return root;
    }
    else
    {
        return minimum(root->left);
    }
}

struct TreeNode* BST::succesor(struct TreeNode* root){
    if(root->right == NULL)
    {
        return NULL;
    }
    else
    {
        struct TreeNode *x;
        x = minimum(root->right);
        return x;
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { 
    if(root->JourneyCode == JourneyCode && root->price == price)
    {
        if(root->left == NULL && root->right == NULL)
        {
            root->JourneyCode = 0;
            root->price = 0;
            root->parent = NULL;
        }
        else if(root->left == NULL)
        {
            root->JourneyCode = 0;
            root->price = 0;
            root->right->parent = root->parent;
        }
        else if(root->right = NULL)
        {
            root->JourneyCode = 0;
            root->price = 0;
            root->left->parent = root->parent;
        }
        else
        {
            struct TreeNode *x;
            x = succesor(root);
            x->parent = root->parent;
            x->right = root->right;
            x->left = root->left;
            bool r = remove(x->JourneyCode, x->price);
        }
        root->left = NULL;
        root->left = NULL;
        root->right = NULL;
        return true;
    }
    else
    {
        if(root->price>=price && root->left != NULL)
        {
            BST root2(root->left);
            return root2.find(JourneyCode, price);
        }
        else if(root->price<price && root->right != NULL)
        {
            BST root2(root->right);
            return root2.find(JourneyCode, price);
        }
    }
    return false; 
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal == 0)
    {
        cout<<root->JourneyCode<<" ";
        if(root->left != NULL)
        {
            BST root1(root->left);
            root1.traverse(typeOfTraversal);
        }
        if(root->right != NULL)
        {
            BST root2(root->right);
            root2.traverse(typeOfTraversal);
        }
    }
    else if(typeOfTraversal == 1)
    {
        if(root->left != NULL)
        {
            BST root1(root->left);
            root1.traverse(typeOfTraversal);
        }
        if(root->right != NULL)
        {
            BST root2(root->right);
            root2.traverse(typeOfTraversal);
        }
        cout<<root->JourneyCode<<" ";
    }
    else if(typeOfTraversal == 2)
    {
        if(root->left != NULL)
        {
            BST root1(root->left);
            root1.traverse(typeOfTraversal);
        }
        cout<<root->JourneyCode<<" ";
        if(root->right != NULL)
        {
            BST root2(root->right);
            root2.traverse(typeOfTraversal);
        }
    }
    else if(typeOfTraversal == 3)
    {

    }
    return; 
}

// Returns the price of the cheapest journey
int BST::getMinimum() {
    if(root->left == NULL)
    {
        return root->price;
    }
    else
    {
        BST root2(root->left);
        return root2.getMinimum();
    }
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


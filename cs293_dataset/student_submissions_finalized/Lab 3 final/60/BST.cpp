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

BST::BST()
{
    root = nullptr;
}
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode * ptr = root; 
    TreeNode * ptr2 = new TreeNode;
    ptr2->JourneyCode = JourneyCode;
    ptr2->price = price;
    ptr2->left = nullptr;
    ptr2->right = nullptr;

    while(ptr!=nullptr)
    {
        if(ptr->price == price)
        {
            return false;
        }
        else if(ptr->price > price)
        {
            ptr = ptr->left;
        }
        else if(ptr->price < price)
        {
            ptr = ptr->right;
        }
    }
    ptr = ptr2;
    return true; 
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) 
{ 
    TreeNode * ptr = root;
    if(root==NULL){
        root = ptr;
        return false;
    }
    else if(root->JourneyCode==JourneyCode && root->price==price)
    {
        root = ptr;
        return true;
    }
    else if(ptr->price < price)
    {
        root = root->right;
        find(JourneyCode, price);
    }
    else
    {
        root = root->left;
        find(JourneyCode,price);
    }
    root = ptr;
    return true;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) { return false; }

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void preOrder(struct TreeNode * root )
{
    if(root!=nullptr)
    {
        return;
    }
        cout<<root->price<<endl;
        preOrder(root->left);
        preOrder(root->right);
}
void postOrder(struct TreeNode * root )
{
    if(root!=nullptr)
    {
        return;
    }
        preOrder(root->left);
        preOrder(root->right);
        cout<<root->price<<endl;
}
void inOrder(struct TreeNode * root )
{  
    if(root!=nullptr)
    {
        return;
    }
        preOrder(root->left);
        cout<<root->price<<endl;
        preOrder(root->right);
}

void BST::traverse(int typeOfTraversal) 
{ 
    if(typeOfTraversal==0){
        preOrder(root);
    }
    else if(typeOfTraversal==1){
        postOrder(root);
    }
    else if(typeOfTraversal==2){
        inOrder(root);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum() 
{ 
    struct TreeNode * ptr = root;
    if(root == NULL)
    {
        root = ptr;
        return -1;
    }
    while(root->left!=NULL)
    {
        root = root->left;
    }
    root = ptr;
    return root->price;
}


// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) { return 0; }

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

void BST::customLoad(int flag, string filename) { return; }

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "└──");

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST(prefix + (isLeft ? "│   " : "    "), true);
        root = root->right;
        getBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult()
{
    result.clear();
}

vector<string> BST::getResult()
{
    return result;
}

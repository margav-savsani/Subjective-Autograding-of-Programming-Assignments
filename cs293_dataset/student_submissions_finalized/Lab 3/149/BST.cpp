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
    root = new TreeNode();
    root->parent = nullptr;
}
BST::BST(TreeNode *root)
{
    this->root = root;
}

bool addNode(TreeNode *t, int price, int code)
{
    bool m = false;
    if (t->price == 0)
    {
        cout << 2 << endl;
        t->price = price;
        t->JourneyCode = code;
        return true;
    }
    else if (t->price >= price)
    {
        if (t->JourneyCode == code)
        {
            return false;
        }
        else if (t->left == nullptr)
        {
            t->left = new TreeNode();
            t->left->parent = t;
            t->left->price = price;
            t->left->JourneyCode = code;
            return true;
        }
        else
        {
            return addNode(t->left, price, code);
        }
    }
    else if (t->price < price)
    {
        if (t->JourneyCode == code)
        {
            return false;
        }
        else if (t->right == nullptr)
        {
            t->right = new TreeNode();
            t->right->parent = t;
            t->right->price = price;
            t->right->JourneyCode = code;
            return true;
        }
        else
        {
            return addNode(t->right, price, code);
        }
    }
}

TreeNode *findNode(TreeNode *t, int price, int code)
{
    if (t == nullptr)
    {
        return t;
    }
    else if (t->price == price && t->JourneyCode == code)
    {
        return t;
    }
    else if (t->price >= price)
    {
        return findNode(t->left, price, code);
    }
    else
    {
        return findNode(t->right, price, code);
    }
}

void pre(TreeNode *t)
{
    if (t == nullptr)
        return;
    cout << t->JourneyCode << endl;
    pre(t->left);
    pre(t->right);
}

void post(TreeNode *t)
{
    if (t == nullptr)
        return;
    post(t->left);
    post(t->right);
    cout << t->JourneyCode << endl;
}

void in(TreeNode *t)
{
    if (t == nullptr)
        return;
    post(t->left);
    cout << t->JourneyCode << endl;
    post(t->right);
}

TreeNode *findChild(TreeNode *t)
{
    if (t->left == nullptr)
        return t;
    else
    {
        return findChild(t->left);
    }
}
// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    return addNode(root, price, JourneyCode);
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode *t = findNode(root, price, JourneyCode);
    if (t == nullptr)
        // cout << "3546" << endl;
        return false;
    else
        return true;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *t = findNode(root, price, JourneyCode);
    if (t == nullptr)
        return false;
    else
    {
        if (t->left == nullptr && t->right == nullptr)
        {
            if (t->parent->left == t)
            {
                t->parent->left = nullptr;
            }
            else
                t->parent->right = nullptr;
            return true;
        }
        else if (t->right == nullptr && t->left != nullptr)
        {
            if (t->parent->left == t)
            {
                t->parent->left = t->left;
                t->left->parent = t->parent;
            }
            else
            {
                t->parent->right = t->left;
                t->left->parent = t->parent;
            }
        }
        else if (t->right != nullptr && t->left == nullptr)
        {
            if (t->parent->left == t)
            {
                t->parent->left = t->right;
                t->right->parent = t->parent;
            }
            else
            {
                t->parent->right = t->right;
                t->left->parent = t->parent;
            }
        }
        else
        {
            TreeNode *x = findChild(t->right);
            x->parent->left = nullptr;
            x->parent = t->parent;
            x->left = t->left;
            x->right = t->right;
        }
        return true;
    }
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if (typeOfTraversal == 0)
    {
        pre(root);
    }
    else if (typeOfTraversal == 1)
    {
        post(root);
    }
    else if (typeOfTraversal == 2)
    {
        in(root);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *t = this->root;
    while (t->left != nullptr)
    {
        t = t->left;
    }
    return t->price;
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
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string &prefix, bool isLeft = false)
{
    if (root != nullptr)
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__");

        // print the value of the node
        result.push_back(root->JourneyCode + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
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

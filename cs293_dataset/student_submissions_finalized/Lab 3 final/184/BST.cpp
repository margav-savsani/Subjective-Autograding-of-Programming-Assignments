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
{ // cout<<"1"<<endl;
    root = nullptr;
    // cout<<"1"<<endl;
}
BST::BST(TreeNode *root)
{
    this->root = root;
    this->root->parent = nullptr;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *y = nullptr;
    TreeNode *x = root;
    // We need to create z as a pointer so that the same address is not pointed every time when the function is called.
    TreeNode *z = new TreeNode(JourneyCode, price);

    while (x != nullptr)
    {
        y = x;
        if (z->JourneyCode == x->JourneyCode && z->price == x->price)
        {
            return false;
        }
        if (z->price < x->price)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == nullptr)
    {
        root = z;
    }
    else if (z->price < y->price)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    bool found = false;
    TreeNode *x = root;
    TreeNode *z = new TreeNode(JourneyCode, price);
    while (x != nullptr)
    {
        if (x->price == z->price && x->JourneyCode == z->JourneyCode)
        {
            found = true;
            break;
        }
        else if (z->price < x->price)
        {
            x = x->left;
        }
        else if (z->price > x->price)
        {
            x = x->right;
        }
    }
    return found;
}

// finds the node that has the given attributes.
TreeNode *BST::find_node(int JourneyCode, int price)
{
    bool found = false;
    TreeNode *x = root;
    TreeNode *z = new TreeNode(JourneyCode, price);
    while (x != nullptr)
    {
        if (x->price == z->price && x->JourneyCode == z->JourneyCode)
        {
            found = true;
            break;
        }
        else if (z->price < x->price)
        {
            x = x->left;
        }
        else if (z->price > x->price)
        {
            x = x->right;
        }
    }
    if (found)
        return x;
    else
        return nullptr;
}

// finds the successor of the given node as input.
TreeNode *BST::successor(TreeNode *n)
{
    TreeNode *x = n->right;
    TreeNode *min = nullptr;
    while (x != nullptr)
    {
        min = x;
        x = root->left;
    }

    if (n->right != nullptr)
        return min;

    TreeNode *y = n->parent;
    while (y != nullptr && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *y = nullptr;
    TreeNode *x = nullptr;
    TreeNode *z = find_node(JourneyCode,price);
    if (z != nullptr)
    {
        if (root == nullptr)
            return false;
        else
        {
            if (z->left == nullptr || z->right == nullptr)
                y = z;
            else
                y = successor(z);

            if (y->left != nullptr)
                x = y->left;
            else
                x = y->right;

            if (x != nullptr)
                x->parent = y->parent;

            if (y->parent == nullptr)
                root = x;
            else if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;

            if (y != z)
            {
                z->JourneyCode = y->JourneyCode;
                z->price = y->price;
            }
            return true;
        }
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
        if (root == nullptr)
            return;
        else
            preorder_traversal(root);
    }
    if (typeOfTraversal == 1)
    {
        if (root == nullptr)
            return;
        else
            postorder_traversal(root);
    }
    if (typeOfTraversal == 2)
    {
        if (root == nullptr)
            return;
        else
            inorder_traversal(root);
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *x = root;
    TreeNode *y = nullptr;
    while (x != nullptr)
    {
        y = x;
        x = x->left;
    }
    if (y == nullptr)
        return -1;
    else
        return y->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) { 
    int count=0;
    TreeNode *x = root;
    return count_recursive(x,lowerPriceBound,upperPriceBound);
    }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) { 
    
    return; 
    }

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

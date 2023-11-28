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

BST::BST() { root = NULL; }
BST::BST(TreeNode *root) { this->root = root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *node = root;

    if (node == NULL)
    {
        root = new TreeNode(JourneyCode, price);
        return 1;
    }
    if (root->JourneyCode == JourneyCode)
    {
        return 0;
    }
    if (node != NULL)
    {
        if (price < node->price)
        {
            BST(node->left).insert(JourneyCode, price);
        }
        else if (price > node->price)
        {
            BST(node->right).insert(JourneyCode, price);
        }
        return 1;
    }
    return 0;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode *node = root;
    if (node == NULL)
    {
        return 0;
    }
    if ((price == node->price) and (JourneyCode == node->JourneyCode))
    {
        return 1;
    }
    if (price < node->price)
    {
        return (BST(node->left).find(JourneyCode, price));
    }
    else if (price < node->price)
    {
        return (BST(node->right).find(JourneyCode, price));
    }
    return 0;
}

struct TreeNode *minValueNode(struct TreeNode *root)
{
    struct TreeNode *current = root;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if (find(JourneyCode, price) == 0)
    {
        return 0;
    }
    TreeNode *node = root;

    if (price < node->price)
    {
        BST(node->left).remove(JourneyCode, price);
    }
    else if (price > root->price)
        BST(node->right).remove(JourneyCode, price);

    else
    {
        // node has no child
        if (node->left == NULL and node->right == NULL)
            return NULL;

        // node with only one child or no child
        else if (node->left == NULL)
        {
            struct TreeNode *temp = node->right;
            free(root);
            node->right = temp;
        }
        else if (root->right == NULL)
        {
            struct TreeNode *temp = root->left;
            free(root);
            node->left = temp;
        }

        // node with two children
        struct TreeNode *temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        node->JourneyCode = temp->JourneyCode;
        node->price = temp->price;

        // Delete the inorder successor
        BST(node->right).remove(temp->JourneyCode, temp->price);
    }
    return 1;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void inorder(struct TreeNode *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->JourneyCode << endl;
    inorder(root->right);
}

void preorder(struct TreeNode *root)
{
    if (root == NULL)
        return;
    cout << root->JourneyCode << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct TreeNode *root)
{
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->JourneyCode << " ";
}

void BST::traverse(int typeOfTraversal)
{
    if (typeOfTraversal == 0)
    {
        // PRE_ORDER
        preorder(root);
    }
    if (typeOfTraversal == 1)
    {
        // POST_ORDER
        postorder(root);
    }
    if (typeOfTraversal == 2)
    {
        // IN_ORDER
        inorder(root);
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *node = root;
    while (node->left != NULL and node)
    {
        node = node->left;
    }
    return node->price;
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

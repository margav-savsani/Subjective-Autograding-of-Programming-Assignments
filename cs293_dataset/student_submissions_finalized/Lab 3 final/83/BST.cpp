#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
    root = NULL;
}
BST::BST(TreeNode *r)
{
    root = new TreeNode;
    root->JourneyCode = r->JourneyCode;
    root->parent = r->parent;
    root->price = r->price;
    root->left = r->left;
    root->right = r->right;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if (find(JourneyCode, price)){
       return false;
    }
    else
    {
        TreeNode *a = root;

        if (a == NULL)
        {
            root = new TreeNode(JourneyCode, price,NULL,NULL,NULL);
            return true;
        }
        else
        {
            while (true)
            {
                if (a->price >= price)
                {
                    if (a->left == NULL)
                    {
                        a->left = new TreeNode(JourneyCode, price,NULL,NULL,a);
                        return true;
                    }
                    else
                        a = a->left;
                }
                else if (a->price < price)
                {
                    if (a->right == NULL)
                    {
                        a->right = new TreeNode(JourneyCode, price,NULL,NULL,a);
                        return true;
                    }
                    else
                        a = a->right;
                }
            }
        }
    }
    return false;
}
// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode * T = root;
    while (T!= NULL)
    {
        if(T->JourneyCode == JourneyCode && T->price == price)
        {
            return true;
        }
        if(T->price >= price)
        {
            T = T->left;
        }
        if (T->price < price)
        {
            T = T->right;
        }
        
    }
    return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::removeelem(int JourneyCode, int price, TreeNode *root)
{
    if (root == NULL)
        return false;

    if (root->price > price)
        return removeelem(JourneyCode, price, root->left);
    else if (root->price < price)
        return removeelem(JourneyCode, price, root->right);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            root = NULL;
            return true;
        }
        else if (root->left == NULL)
        {
            TreeNode *a = root->right;
            root = a;
            root->right = NULL;
            return true;
        }
        else if (root->right == NULL)
        {
            TreeNode *a = root->left;
            root = a;
            root->left = NULL;
            return true;
        }
        else
        {
            TreeNode *a = getMInimumVal(root->right);
            root->JourneyCode = getMInimumVal(root->right)->JourneyCode;
            root->price = getMInimumVal(root->right)->price;
            if (a->parent->right == a)
            {
                a->parent->right = a->right;
                if (a->right != NULL)
                {
                    a->right->parent = a->parent;
                }
            }
            else
            {
                a->parent->left = a->right;
                if (a->right != NULL)
                {
                    a->right->parent = a->parent;
                }
            }

            return true;
        }
    }

    return false;
}

TreeNode *BST::getMInimumVal(TreeNode *root)
{
    cout << "inside getmin \n";
    TreeNode *current = root;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

bool BST::remove(int JourneyCode, int price)
{
    cout << "inside remove \n";
    return BST::removeelem(JourneyCode, price, root);
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::preorder(TreeNode *root)
{
    if (root == NULL)
        return;
    else
    {
        cout << root->JourneyCode << endl;
        preorder(root->left);
        preorder(root->right);
        return;
    }
}

void BST::postorder(TreeNode *root)
{
    if (root == NULL)
        return;
    else
    {
        postorder(root->left);
        postorder(root->right);
        cout << root->JourneyCode << endl;
    }
}

void BST::inorder(TreeNode *root)
{
    if (root == NULL)
        return;
    else
    {
        inorder(root->left);
        cout << root->JourneyCode << endl;
        inorder(root->right);
    }
}

void BST::traverse(int typeOfTraversal)
{
    if (typeOfTraversal == 0)
        preorder(root);
    else if (typeOfTraversal == 1)
        postorder(root);
    else
        inorder(root);
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *current = root;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound, TreeNode *root)
{
    if (root == NULL)
        return 0;

    else if (root->price == lowerPriceBound && root->price == upperPriceBound)
        return 1;

    else if (root->price >= lowerPriceBound && root->price <= upperPriceBound)
        return countJourneysInPriceBound(lowerPriceBound, upperPriceBound, root->left) +
               countJourneysInPriceBound(lowerPriceBound, upperPriceBound, root->right) + 1;
    else if (root->price < lowerPriceBound)
        return countJourneysInPriceBound(lowerPriceBound, upperPriceBound, root->right);
    else
        return countJourneysInPriceBound(lowerPriceBound, upperPriceBound, root->left);
}
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    return BST::countJourneysInPriceBound(lowerPriceBound, upperPriceBound, root);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
    ofstream outfile;
    outfile.open("filename.txt");
    outfile.close();
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
    if (root != NULL)
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
    if (root != NULL)
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
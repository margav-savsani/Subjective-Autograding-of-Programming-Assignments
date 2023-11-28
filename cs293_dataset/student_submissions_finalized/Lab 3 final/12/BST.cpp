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
    root = NULL;
}
BST::BST(TreeNode *root) { this->root = root; }

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *temp = new TreeNode(JourneyCode, price);
    if (root == NULL)
    {
        root = temp;
        return true;
    }
    else if (price >= root->price)
    {
        if (root->right == NULL)
        {
            root->right = temp;
            return true;
        }
        BST rightsubTree(root->right);
        return rightsubTree.insert(JourneyCode, price);
    }
    else
    {
        if (root->left == NULL)
        {
            root->left = temp;
            return true;
        }
        BST leftsubTree(root->left);
        return leftsubTree.insert(JourneyCode, price);
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if (root == NULL)
        return false;
    if (root->price == price && root->JourneyCode == JourneyCode)
    {
        return true;
    }
    else if (price > root->price)
    {
        BST rightsubTree(root->right);
        return rightsubTree.find(JourneyCode, price);
    }
    else if (price < root->price)
    {
        BST rightsubTree(root->right);
        return rightsubTree.find(JourneyCode, price);
    }
    else
    {
        return false;
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if (root == NULL)
    {
        return false;
    }
    else if (root->JourneyCode == JourneyCode && root->price == price)
    {
        if (root->right == NULL && root->left == NULL)
        {
            root = NULL;
            return true;
        }
        else if (root->left != NULL && root->right == NULL)
        {
            root->left->parent = root->parent;
            if (root->parent != NULL)
            {
                if (root->parent->left == root)
                {
                    root->parent->left = root->left;
                }
                else
                {
                    root->parent->right = root->left;
                }
            }
            return true;
        }
        else if (root->left == NULL && root->right != NULL)
        {
            root->right->parent = root->parent;
            if (root->parent != NULL)
            {
                if (root->parent->right == root)
                {
                    root->parent->right = root->right;
                }
                else
                {
                    root->parent->left = root->right;
                }
            }
            return true;
        }
        else
        {
            TreeNode *C = root->right;
            while (C->left != NULL)
            {
                C = C->left;
            }
            C->parent->left = C->right;
            if (C->right != NULL)
            {
                C->right->parent = C->parent;
            }
            root->JourneyCode = C->JourneyCode;
            root->price = C->price;
            return true;
        }
    }
    else if (price >= root->price)
    {
        BST *rightsubTree = new BST(root->right);
        return rightsubTree->remove(JourneyCode, price);
    }
    else
    {
        BST *leftsubTree = new BST(root->left);
        return leftsubTree->remove(JourneyCode, price);
    }
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if (root == NULL)
    {
        return;
    }
    BST *rightsubTree = new BST(root->right);
    BST *leftsubTree = new BST(root->left);
    if (typeOfTraversal == 1)
    {
        leftsubTree->traverse(typeOfTraversal);
        rightsubTree->traverse(typeOfTraversal);
        cout << root->price << endl;
    }
    if (typeOfTraversal == 0)
    {
        cout << root->price << endl;
        leftsubTree->traverse(typeOfTraversal);
        rightsubTree->traverse(typeOfTraversal);
    }
    if (typeOfTraversal == 2)
    {
        leftsubTree->traverse(typeOfTraversal);
        cout << root->price << endl;
        rightsubTree->traverse(typeOfTraversal);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *temp = root;
    while (temp->left != nullptr)
    {
        temp = temp->left;
    }
    return temp->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{

    TreeNode *temp = root;
    if (temp->price > upperPriceBound)
    {
        return temp->left->countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound);
    }

    else if (temp->price < lowerPriceBound)
    {
        return temp->right->countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound);
    }

    if (temp->price < upperPriceBound && temp->price > lowerPriceBound)
    {
        int a = temp->left->countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound);
        int b = temp->right->countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound);
        return a + b + 1;
    }
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename)
{
    ifstream file(filename);
    if (root == nullptr)
    {
        file >> "#" >> endl;
    }
    file >> root->JourneyCode >> root->price >> endl;

    BST *rightsubTree = new BST(root->right);
    BST *leftsubTree = new BST(root->left);
    leftsubTree->customStore(file);
    file >> "$" >> endl;
    rightsubTree->customStore(file);
    file >> "@" >> endl;
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

void BST::customLoad(int flag, string filename)
{
    ifstream file(filename);
    string w;
    file >> w;
    if (w == "#")
    {
        root = nullptr;
    }
    else
    {
        root->JourneyCode = stoi(w);
        file >> w;
        root->price = stoi(w);
    }
    TreeNode *sub = root;
    while (file >> w)
    {
        file >> w;
        if (w == "@")
        {
            sub = sub->parent;
        }
        else if (w != "#")
        {
            if (w != "$")
            {
                sub->left = new TreeNode();
                sub->left->JourneyCode = stoi(w);
                file >> w;
                sub->left->price = stoi(w);
                sub->left->parent = sub;
                sub = sub->left
            }
            else
            {
                file >> w;
                if (w != "#")
                {
                    sub->right = new TreeNode();
                    sub->right->JourneyCode = stoi(w);
                    file >> w;
                    sub->right->price = stoi(w);
                    sub->right->parent = sub;
                    sub = sub->right
                }
                else
                {
                    sub->right = nullptr;
                    sub = sub->parent;
                }
            }
        }
        else if (w == "#")
        {
            file >> w;
            if (w != "#")
            {
                sub->right = new TreeNode();
                sub->right->JourneyCode = stoi(w);
                file >> w;
                sub->right->price = stoi(w);
                sub->right->parent = sub;
                sub = sub->right
            }
            else
            {
                sub->right = nullptr;
            }
        }
        if (flag == LOAD_LEFT_SUBTREE)
        {
            if (sub == root)
            {
                root = root->left;
                return;
            }
        }
    }
    return;
}

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

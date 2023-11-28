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
    this->root = nullptr;
}
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Return True, if the ticket with same JourneyCode is found, false otherwise
bool BST::Check(int JourneyCode)
{
    if (root == nullptr)
        return false;
    else if (root->JourneyCode == JourneyCode)
        return true;
    BST leftTree(root->left);
    BST rightTree(root->right);
    return leftTree.Check(JourneyCode) || rightTree.Check(JourneyCode);
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *element = new TreeNode(JourneyCode, price);
    // if (Check(JourneyCode))
    //     return false;
    if (root == nullptr)
    {
        root = element;
        return true;
    }
    else if (root->JourneyCode == JourneyCode)
        return false;
    else if (root->price >= price)
    {
        if (root->left == nullptr)
        {
            root->left = element;
            element->parent = root;
            return true;
        }
        BST leftTree(root->left);
        return leftTree.insert(JourneyCode, price);
    }
    else
    {
        if (root->right == nullptr)
        {
            root->right = element;
            element->parent = root;
            return true;
        }
        BST rightTree(root->right);
        return rightTree.insert(JourneyCode, price);
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if (root == nullptr)
        return false;
    else if (root->price == price && root->JourneyCode == JourneyCode)
        return true;
    else if (root->price >= price)
    {
        if (root->left == nullptr)
            return false;
        BST leftTree(root->left);
        return leftTree.find(JourneyCode, price);
    }
    else
    {
        if (root->right == nullptr)
            return false;
        BST rightTree(root->right);
        return rightTree.find(JourneyCode, price);
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if (root == nullptr)
        return false;
    else if (root->price == price && root->JourneyCode == JourneyCode)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            if (root->parent != nullptr)
            {
                if (root->parent->right == root)
                    root->parent->right = nullptr;
                else
                    root->parent->left = nullptr;
            }
            root = nullptr;
            return true;
        }
        else if (root->left == nullptr)
        {
            if (root->parent == nullptr)
            {
                root->right->parent = nullptr;
                root = root->right;
                return true;
            }
            root->right->parent = root->parent;
            if (root->parent->right == root)
                root->parent->right = root->right;
            else
                root->parent->left = root->right;
            root = root->right;
            return true;
        }
        else if (root->right == nullptr)
        {
            if (root->parent == nullptr)
            {
                root->left->parent = nullptr;
                root = root->left;
                return true;
            }
            root->left->parent = root->parent;
            if (root->parent->right == root)
                root->parent->right = root->left;
            else
                root->parent->left = root->left;
            root = root->left;
            return true;
        }
        else
        {
            TreeNode *element = root->left;
            while (element->right != nullptr)
                element = element->right;
            root->JourneyCode = element->JourneyCode;
            root->price = element->price;
            if (element->parent->left == element)
            {
                element->parent->left = element->left;
                if (element->left != nullptr)
                    element->left->parent = element->parent;
            }
            else
            {
                element->parent->right = element->left;
                if (element->left != nullptr)
                    element->left->parent = element->parent;
            }
        }
        return true;
    }
    else if (root->price >= price)
    {
        if (root->left == nullptr)
            return false;
        BST leftTree(root->left);
        return leftTree.remove(JourneyCode, price);
    }
    else
    {
        if (root->right == nullptr)
            return false;
        BST rightTree(root->right);
        return rightTree.remove(JourneyCode, price);
    }
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if (root == nullptr)
        return;
    BST leftTree(root->left);
    BST rightTree(root->right);
    if (typeOfTraversal == PRE_ORDER)
    {
        cout << root->JourneyCode << endl;
        leftTree.traverse(PRE_ORDER);
        rightTree.traverse(PRE_ORDER);
    }
    else if (typeOfTraversal == POST_ORDER)
    {
        leftTree.traverse(POST_ORDER);
        rightTree.traverse(POST_ORDER);
        cout << root->JourneyCode << endl;
    }
    else if (typeOfTraversal == IN_ORDER)
    {
        leftTree.traverse(IN_ORDER);
        cout << root->JourneyCode << endl;
        rightTree.traverse(IN_ORDER);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *element = root;
    while (element->left != nullptr)
        element = element->left;
    return element->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    if (root == nullptr)
        return 0;
    if (root->price >= lowerPriceBound && root->price <= upperPriceBound)
    {
        BST leftTree(root->left);
        BST rightTree(root->right);
        return 1 + leftTree.countJourneysInPriceBound(lowerPriceBound, upperPriceBound) + rightTree.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    }
    else if (root->price > upperPriceBound)
    {
        BST leftTree(root->left);
        return leftTree.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    }
    else
    {
        BST rightTree(root->right);
        return rightTree.countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
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
    ofstream file(filename);
    if (root == nullptr)
    {
        file << "$" << endl;
        return;
    }
    BST leftTree(root->left);
    BST rightTree(root->right);
    file << root->JourneyCode << " " << root->price << endl;
    leftTree.customStore(filename);
    file << "#" << endl;
    rightTree.customStore(filename);
    file << "@" << endl;
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
    string word;
    file >> word;
    if (word == "$")
    {
        root = nullptr;
        return;
    }
    else
    {
        TreeNode *temp = new TreeNode();
        temp->JourneyCode = stoi(word);
        file >> word;
        temp->price = stoi(word);
        root = temp;
    }
    TreeNode *element = root;
    while (file >> word)
    {
        if (word == "@")
            element = element->parent;
        else if (word != "$")
        {
            if (word != "#")
            {
                element->left = new TreeNode();
                element->left->JourneyCode = stoi(word);
                file >> word;
                element->left->price = stoi(word);
                element->left->parent = element;
                element = element->left;
            }
            else
            {
                file >> word;
                if (word != "$")
                {
                    element->right = new TreeNode();
                    element->right->JourneyCode = stoi(word);
                    file >> word;
                    element->right->price = stoi(word);
                    element->right->parent = element;
                    element = element->right;
                }
                else{
                    element->right = nullptr;
                }
            }
        }
        else if (word == "$")
        {
            file >> word;
            if (word != "$")
            {
                element->right = new TreeNode();
                element->right->JourneyCode = stoi(word);
                file >> word;
                element->right->price = stoi(word);
                element->right->parent = element;
                element = element->right;
            }
            else
            {
                element->right = nullptr;
            }
        }
        if (flag == LOAD_LEFT_SUBTREE)
        {
            if (element == root)
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

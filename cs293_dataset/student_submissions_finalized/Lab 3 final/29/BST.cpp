#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <arijit.h>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST() { root = NULL; }
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{

    if (root == NULL) // check if this root is the top root
    {
        root = new TreeNode(JourneyCode, price); // assign new space to it
        return true;
    }
    if (root->JourneyCode == JourneyCode && root->price == price) // if journeycode is already exist then return false
    {
        return false;
    }
    else if (root->price > price) // if root price is greater then price then
    {                             // new node will be inserted in left of the root
        if (root->left != NULL)   // if left is not NULL go
        {
            BST B(root->left);
            return B.insert(JourneyCode, price); // consider this as a new tree and insert inside this
        }
        else // if left is NULL
        {    // create a new node at left and assign its price journey and parent
            TreeNode *A = new TreeNode(JourneyCode, price, NULL, NULL, root);
            root->left = A;
        }
    }
    else // if price is not less then root then insert right similary
    {
        if (root->right != NULL)
        {
            BST B(root->right);
            bool a = B.insert(JourneyCode, price);
        }
        else
        {
            TreeNode *A = new TreeNode(JourneyCode, price, NULL, NULL, root);
            root->right = A;
        }
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if (root == NULL)
    {
        return false;
    }
    if (root->JourneyCode == JourneyCode && root->price == price) // if found return true
    {
        return true;
    }
    else if (root->price > price && root->left != NULL) // if price is less than root then
    {                                                   // check in left of its
        BST B(root->left);
        return B.find(JourneyCode, price);
    }
    else if (root->price <= price && root->right != NULL) // otherwise check in right part of its
    {
        BST B(root->right);
        return B.find(JourneyCode, price);
    }
    return false;
}

bool is_left(TreeNode *Node, TreeNode *root)
{
    if (root->parent == NULL)
    {
        exit(0);
    }
    if (root->parent->right == Node)
    {
        return false;
    }
    else
    {
        return true;
    }
}
void changeFather(TreeNode *A, TreeNode *root)
{
    if (A->parent != NULL)
    {
        if (is_left(A, root))
            A->parent->left = A;
        else
            A->parent->right = A;
    }
}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if (root->JourneyCode == JourneyCode && root->price == price)
    {
        TreeNode *A = root->right;
        TreeNode *L = root->left;
        TreeNode *R = A;

        if (L == NULL && A == NULL)
        {
            if (root->parent != NULL)
            {
                if (root->parent->left == root)
                    root->parent->left = NULL;
                else
                    root->parent->right = NULL;
            }
            else
            {
                root = NULL;
            }
            return true;
        }

        if (A == NULL)
        {
            TreeNode *P = root->parent;
            root->JourneyCode = L->JourneyCode;
            root->left = L->left;
            root->right = L->right;
            root->price = L->price;
            if (root->left != NULL)
                root->left->parent = root;
            if (root->right != NULL)
                root->right->parent = root;
            return true;
        }

        while (A->left != NULL) // goto left untill here is no node
        {                       // and return that price
            A = A->left;
        }
        A->left = L;
        if (root->left != NULL)
            root->left->parent = A;
        R->parent = root->parent;
        if (root->parent != NULL)
        {
            if (root->parent->left == root)
                root->parent->left = root->right;
            else
                root->parent->right = root->right;
        }
        else
        {
            root->left = NULL;
            root->right = NULL;
            delete root;
            root = R;
            root->parent = NULL;
        }
        return true;
    }
    else if (root->price > price && root->left != NULL)
    {
        BST B(root->left);
        return B.remove(JourneyCode, price);
    }
    else if (root->right != NULL)
    {
        BST B(root->right);
        return B.remove(JourneyCode, price);
    }
    return false;
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if (typeOfTraversal == PRE_ORDER)
    {
        if (root != NULL)
        {
            cout << root->JourneyCode << endl;
            BST(root->left).traverse(typeOfTraversal);
            BST(root->right).traverse(typeOfTraversal);
        }
    }
    if (typeOfTraversal == POST_ORDER)
    {
        if (root != NULL)
        {
            BST(root->left).traverse(typeOfTraversal);
            BST(root->right).traverse(typeOfTraversal);
            cout << root->JourneyCode << endl;
        }
    }
    if (typeOfTraversal == IN_ORDER)
    {
        if (root != NULL)
        {
            BST(root->left).traverse(typeOfTraversal);
            cout << root->JourneyCode << endl;
            BST(root->right).traverse(typeOfTraversal);
        }
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *A = root;
    while (A->left != NULL) // goto left untill here is no node
    {                       // and return that price
        A = A->left;
    }
    return A->price;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    int result = 0;

    if (root->left != NULL && root->left->price >= lowerPriceBound)
    {
        result += BST(root->left).countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    }
    if (root->right != NULL && root->right->price <= upperPriceBound)
    {
        result += BST(root->right).countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    }
    if (root->price >= lowerPriceBound && root->price <= upperPriceBound)
    {
        result += 1;
    }
    return result;
}
// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void store(string &s, TreeNode *root)
{

    s += to_string(root->JourneyCode) + "\n";
    // debug(root->JourneyCode);
    // debug(root->price);
    s += to_string(root->price) + "\n";
    if (root->left != NULL)
    {
        store(s, root->left);
    }
    else
    {
        s += "n \n";
    }
    if (root->right != NULL)
    {
        store(s, root->right);
    }
    else
    {
        s += "n \n";
    }
}

void BST::customStore(string filename)
{
    fstream f;
    f.open(filename,ios::out);
    string s;
    store(s, root);
    f << s;
    f.close();
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

void load(fstream &f, TreeNode *&root, TreeNode *parent)
{
    string a;
    f >> a;
    if (a == "n")
    {
        return;
    }
    root = new TreeNode;
    root->parent = parent;
    root->JourneyCode = stoi(a);
    f >> a;
    root->price = stoi(a);
    load(f, root->left, root);
    load(f, root->right, root);
}

void BST::customLoad(int flag, string filename)
{
    fstream f;
    f.open(filename,ios::in);

    if (flag == LOAD_FULL_BST)
    {
        load(f, root, NULL);
        return;
    }
    if (flag == LOAD_LEFT_SUBTREE)
    {
        string a;
        f >> a;
        if (a == "n")
        {
            return;
        }
        f >> a;
        load(f, root, NULL);
    }
}
// Please use the following code to replace the last part of
// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

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
        result.push_back(to_string(root->JourneyCode) + "\n");
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

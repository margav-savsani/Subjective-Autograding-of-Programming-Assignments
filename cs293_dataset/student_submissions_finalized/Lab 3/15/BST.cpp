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
    root = new TreeNode;
    root = NULL;
}
BST::BST(TreeNode *root)
{
    this->root = new struct TreeNode;
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if (root == nullptr)
    {
        root = new struct TreeNode(JourneyCode, price);
        root->parent = NULL;
        return true;
    }
    TreeNode *k = root;
    TreeNode *naya = new struct TreeNode(JourneyCode, price);
    while (true)
    {
        if ((naya->price) >= (k->price))
        {
            if (k->right == NULL)
            {
                k->right = naya;
                naya->parent = k;
                return true;
            }
            else
            {
                k = k->right;
            }
        }
        if ((naya->price) < (k->price))
        {
            if (k->left == NULL)
            {
                k->left = naya;
                naya->parent = k;
                return true;
            }
            else
            {
                k = k->left;
            }
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if (root == NULL)
    {
        return false;
    }
    TreeNode *k = root;
    while (true)
    {

        if ((price) < (k->price))
        {
            if (k->left == NULL)
            {
                return false;
            }
            else
            {
                k = k->left;
            }
        }
        else if ((price) > (k->price))
        {
            if (k->right == NULL)
            {
                return false;
            }
            else
                k = k->right;
        }
        if (price == k->price)
        {
            if (k->JourneyCode == JourneyCode)
            {
                return true;
            }
            else if (k->right == NULL)
            {
                return false;
            }
            k = k->right;
        }
    }
}

// // Functions that traverse the BST in various ways!
// // type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// // Print on cout the journey codes at nodes of the BST in the same order as
// // they are encountered in the traversal order
// // Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if (root == nullptr)
    {
        return;
    }
    BST left(root->left);
    BST right(root->right);
    if (typeOfTraversal == PRE_ORDER)
    {
        cout << root->price << endl;
        left.traverse(typeOfTraversal);
        right.traverse(typeOfTraversal);
    }
    else if (typeOfTraversal == POST_ORDER)
    {
        left.traverse(typeOfTraversal);
        right.traverse(typeOfTraversal);
        cout << root->price << endl;
    }
    else if (typeOfTraversal == IN_ORDER)
    {
        left.traverse(typeOfTraversal);
        cout << root->price << endl;
        right.traverse(typeOfTraversal);
    }
}

bool BST::remove(int JourneyCode, int price)
{
    if (root == nullptr)
    {
        return false;
    }
    TreeNode *k = root;

    while ((k != NULL) && (k->JourneyCode != JourneyCode || k->price != price))
    {
        if (price >= k->price)
        {
            if (k->right == NULL)
            {
                k = NULL;
                break;
            }
            else
                k = k->right;
        }
        if (price < k->price)
        {
            if (k->left == NULL)
            {
                k = NULL;
                break;
            }
            else
                k = k->left;
        }
    }
    if (k == nullptr)
    {
        return false;
    }
    TreeNode *y, *x;
    x = new TreeNode;
    y = new TreeNode;
    if (k->left == nullptr || k->right == nullptr)
    {
        y = k;
    }
    else
    {
        y = minforsuccessor(k->right);
    }
    if (y->left != nullptr)
    {
        x = y->left;
    }
    else
    {
        x = y->right;
    }
    if (x != nullptr)
    {
        x->parent = y->parent;
    }
    if (y->parent == nullptr)
    {
        root = x;
    }
    else if (y->parent->left == y)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    if (y != k)
    {
        k->JourneyCode = y->JourneyCode;
        k->price = y->price;
    }
    return true;
}
// Returns the price of the cheapest journey
int BST::getMinimum()
{
    if (root == NULL)
    {
        return 0;
    }
    TreeNode *k = root;
    while (k->left != NULL)
    {
        k = k->left;
    }
    return k->price;
}

TreeNode *BST::minforsuccessor(TreeNode *N)
{
    while (N->left != nullptr)
    {
        N = N->left;
    }
    return N;
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    int count = 0;
    if (root == NULL)
    {
        return 0;
    }
    else if (root->price < lowerPriceBound)
    {
        TreeNode *curr = root;
        root = root->right;
        count = countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = curr;
        return count;
    }
    else if (root->price > upperPriceBound)
    {
        TreeNode *curr = root;
        root = root->left;
        count = countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = curr;
        return count;
    }
    else
    {
        TreeNode *curr = root;
        root = root->left;
        count = 1 + countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = curr->right;
        count = count + countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
        root = curr;
        return count;
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
    ofstream outfile;
    outfile.open(filename, ios_base::out | ios_base::app);
    if (root == NULL)
    {
        outfile << -1 << endl;
    }
    else
    {
        outfile << root->JourneyCode << " " << root->price << endl;
        TreeNode *curr = root;
        root = root->left;
        customStore(filename);
        root = curr->right;
        customStore(filename);
        root = curr;
    }
    outfile.close();
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
bool BST::customLoadRecursive(ifstream &infile)
{
    int k;
    
    if (infile >> k)
    {
        if (k == -1)
        {
            return 0;
        }
        else
        {
            int m;
            infile >> m;
            root->JourneyCode = k;
            root->price = m;
            TreeNode *curr = root;
            root->left = new TreeNode;
            root->right = new TreeNode;
            root = root->left;
            if (!customLoadRecursive(infile))
            {
                curr->left = NULL;
            }
            root = curr->right;
            if (!customLoadRecursive(infile))
            {
                curr->right = NULL;
            }
            root = curr;
            return 1;
        }
    }
    return 1;
}

void BST::customLoad(int flag, string filename)
{
    ifstream infile;
    infile.open(filename);
    if (flag == LOAD_FULL_BST)
    {
        root = new TreeNode;
        customLoadRecursive(infile);
    }
    if (flag == LOAD_LEFT_SUBTREE)
    {
        int m, n;
        infile >> m;
        infile >> n;
        root = new TreeNode;
        customLoadRecursive(infile);
    }
}
    // int k;
    // root = new TreeNode;
    // infile>>k;
    // if(k==-1){
    //     return;
    // }
    // else{
    //     root->JourneyCode=k;
    //     int m;
    //     infile>>m;
    //     root->price=m;
    // }
    // TreeNode* curr=root;
    // root=root->left;
    // customLoad(flag,filename);
    // root=curr->right;
    // customLoad(flag,filename);

    // TreeNode *now_at = root;
    // now_at->parent = NULL;
    // int next = 0; // 0 for left 1 for right 2 for up
    // bool right_child_of_parent=false;
    // while (infile >> k)
    // {
    //     if (k == -1)
    //     {

    //         now_at=now_at->right;
    //         int furthernulls=0;

    //     }
    //     else
    //     {
    //         now_at->JourneyCode = k;
    //         int m;
    //         infile >> m;
    //         now_at->price = m;
    //         now_at=now_at->left;
    //     }
    // }


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

        result.push_back(isLeft ? "├──" : "└──");

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

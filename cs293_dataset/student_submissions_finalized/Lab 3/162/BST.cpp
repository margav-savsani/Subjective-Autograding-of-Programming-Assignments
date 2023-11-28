// #include <bits/stdc++.h>
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
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
TreeNode *BST::createNewNode(TreeNode *node, int JourneyCode, int price)
{

    TreeNode *newNode = new TreeNode();
    newNode->price = price;
    newNode->JourneyCode = JourneyCode;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = node;

    return newNode;
}

bool BST::insert(int JourneyCode, int price)
{
    // TreeNode* prevNode = root;
    if (root == NULL)
    {
        // cout<<"Insert Root!"<<endl;
        root = new TreeNode();
        root->left = NULL;
        root->parent = NULL;
        root->right = NULL;
        root->JourneyCode = JourneyCode;
        root->price = price;
        return true;
    }

    TreeNode *parent = root;
    TreeNode *node = root;

    while (node != NULL)
    {

        if (node->JourneyCode == JourneyCode)
        {
            //  cout<<"same code"<<endl;
            return false;
        }
        else
        {
            if (node->price > price)
            {
                // cout<<node->JourneyCode<<endl;
                parent = node;
                node = node->left;
            }
            else
            {
                // cout<<node->JourneyCode<<endl;
                parent = node;
                node = node->right;
            }
        }
    }

    if (parent->JourneyCode == JourneyCode)
    {
        //  cout<<"same code"<<endl;
        return false;
    }

    if (parent->price > price)
    {
        // cout<<parent->JourneyCode<<endl;
        parent->left = createNewNode(parent, JourneyCode, price);
        return true;
    }
    else
    {
        // cout<<parent->JourneyCode<<endl;
        parent->right = createNewNode(parent, JourneyCode, price);
        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{

    TreeNode *node = root;
    // if(node->price == price && node->JourneyCode == JourneyCode) return true;

    while (node != NULL && !(node->price == price && node->JourneyCode == JourneyCode))
    {
        // Search for the element in the left subtree
        // cout<<node->JourneyCode<<endl;
        // cout<<node->price<<endl;
        if (node->price > price)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    if (node == NULL)
        return false;
    if (node->price == price && node->JourneyCode == JourneyCode)
    {
        return true;
    }

    return false;
}

TreeNode *BST::findSucessor(TreeNode *node)
{
    if (node->right != NULL)
    {   TreeNode* ptr = node->right;
        while (ptr->left != NULL)
        {
            ptr= ptr->left;
        }
        return ptr;
        
    }
    else
    {

        TreeNode *parent = node->parent;
        TreeNode *child = node;
        while (parent != NULL && parent->left != child)
        {
            child = parent;
            parent = child->parent;
        }
        if (parent == NULL)
            return NULL;
        else
        {
            return parent;
        }
    }
}

bool BST::removeRecursive(TreeNode *ptr, int JourneyCode, int price)
{
    // if(root->JourneyCode == JourneyCode && root->price = price)
    // {
    //     if(root->right !=NULL)
    //     {
    //         root->right-
    //     }
    // }
    if (ptr == NULL)
    {
        // cout<<"CALLED HERE N"<<endl;
        return false;
    }
    if (ptr->left == NULL && ptr->right == NULL)
    {
        // cout<<"Called HERE 2"<<endl;
        if (ptr->JourneyCode == JourneyCode && ptr->price == price)
        {
            // cout<<"Called HERE 3"<<endl;
            if (ptr == root)
            {
                root = NULL;
                return true;
            }
            if (ptr->parent->left == ptr)
            {
                // cout<<"Called HERE 4"<<endl;
                ptr->parent->left = NULL;
            }
            else if (ptr->parent->right == ptr)
            {
                // cout<<"Called HERE 4"<<endl;
                ptr->parent->right = NULL;
            }
            // cout<<"Called HERE 5"<<endl;
            ptr->parent = NULL;
            delete ptr;

            return true;
        }
        return false;
    }
    if (ptr->price > price)
    {
        return removeRecursive(ptr->left, JourneyCode, price);
    }
    else if (ptr->price < price)
    {
        return removeRecursive(ptr->right, JourneyCode, price);
    }
    else
    {

        TreeNode *successor = findSucessor(ptr);
        if (successor != NULL)
        {
            ptr->price = successor->price;
            ptr->JourneyCode = successor->JourneyCode;
            // cout<<"Called HERE"<<" "<<(successor==NULL) <<endl;
            return removeRecursive(successor, successor->JourneyCode, successor->price);
        }
        else
        {
            
        }
        // else
        // {
        //     root = root->
        // }
    }
    // return false;
}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *node = root;
    return removeRecursive(node, JourneyCode, price);
}

void BST::PreOrder(TreeNode *node)
{
    if (node == NULL)
        return;
    cout << node->JourneyCode << endl;
    PreOrder(node->left);
    PreOrder(node->right);
}
void BST::InOrder(TreeNode *node)
{
    if (node == NULL)
        return;

    InOrder(node->left);
    cout << node->JourneyCode << endl;
    InOrder(node->right);
}
void BST::PostOrder(TreeNode *node)
{
    if (node == NULL)
        return;

    PostOrder(node->left);
    PostOrder(node->right);
    cout << node->JourneyCode << endl;
}
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    switch (typeOfTraversal)
    {
    case PRE_ORDER:
        PreOrder(root);
        break;
    case POST_ORDER:
        PostOrder(root);
        break;
    case IN_ORDER:
        InOrder(root);
        break;
    default:
        break;
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    TreeNode *p = root;
    while (p->left != NULL)
    {
        p = p->left;
    }
    return p->price;

    return 0;
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

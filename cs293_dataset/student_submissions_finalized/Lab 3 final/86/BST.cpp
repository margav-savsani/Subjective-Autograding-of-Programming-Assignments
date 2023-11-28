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
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
int getmin(TreeNode *T)
{
    if (T->left == NULL)
        return T->price;
    else
        return getmin(T->left);
}
void pretraversal(TreeNode *T)
{
    if (T == NULL)
        return;
    else
    {
        cout << T->JourneyCode << endl;
        pretraversal(T->left);
        pretraversal(T->right);
        return;
    }
}
void posttraversal(TreeNode *T)
{
    if (T == NULL)
        return;
    else
    {   
        posttraversal(T->left);
        posttraversal(T->right);
        cout << T->JourneyCode << endl;
        return;
    }
}
void intraversal(TreeNode *T)
{
    if (T == NULL)
        return;
    else
    {
        intraversal(T->left);
        cout << T->JourneyCode << endl;
        intraversal(T->right);
        return;
    }
}
TreeNode *getmaxnode(TreeNode *T)
{
    if (T->right == NULL)
        return T;
    else
        return getmaxnode(T->right);
}
TreeNode *BST::search(TreeNode *T, int price)
{
    if (T == NULL)
    {
        return NULL;
    }
    if (T->price == price)
        return T;
    if (T->price < price)
    {
        return search(T->right, price);
    }
    else
        return search(T->left, price);
}
TreeNode *BST::predecessor(TreeNode *T, int price)
{
    if (T == NULL)
        return NULL;
    if (T->price == price)
    {
        if (T->left == NULL)
            return NULL;
        else
            return getmaxnode(T->left);
    }
    else
    {
        if (price < T->price)
            return predecessor(T->left, price);
        else
            return predecessor(T->right, price);
    }
}
int BST::routes(TreeNode *T,int lower, int upper) 
{
    if(T == NULL) return 0;
    if((T->price == lower)&&(T->price == upper)) return 1;
    if((T->price <= upper)&&(T->price >= lower))
    {
        return 1+routes(T->left,lower,upper)+routes(T->right,lower,upper);
    }
    else if(T->price < lower) return routes(T->right,lower,upper);
    else return routes(T->left,lower,upper);
}
bool BST::insert(int JourneyCode, int price)
{
    if (search(root, price) != NULL)
    {
        return false;
    }
    else
    {
        TreeNode *newnode = new TreeNode;
        newnode->JourneyCode = JourneyCode;
        newnode->price = price;
        newnode->parent = NULL;
        newnode->left = NULL;
        newnode->right = NULL;
        if (root == NULL)
        {
            root = new TreeNode;
            root->parent = NULL;
            root->JourneyCode = JourneyCode;
            root->price = price;
            return true;
        }
        TreeNode *T = root;
        TreeNode *temp = new TreeNode;
        while (T != NULL)
        {
            temp = T;
            if (price < T->price)
                T = T->left;
            else
                T = T->right;
        }
        if (price < temp->price)
        {
            temp->left = newnode;
            newnode->parent = temp;
            return true;
        }
        else
        {
            temp->right = newnode;
            newnode->parent = temp;
            return true;
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if (search(root, price) == NULL)
        return false;
    else
    {
        TreeNode *found = search(root, price);
        if (found->JourneyCode == JourneyCode)
            return true;
        else
            return false;
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if (!find(JourneyCode, price))
        return false;
    else
    {
        TreeNode *found = search(root, price);
        if (found == root)
        {
            if ((found->right == NULL) && (found->left == NULL))
            {
                root = NULL;
                found = new TreeNode;
                return true;
            }
            else if ((found->right == NULL) || (found->left == NULL))
            {
                if (found->left == NULL)
                {
                    root = found->right;
                    found->right->parent = NULL;
                    found = new TreeNode;
                    return true;
                }
                else
                {
                    root = found->left;
                    found->left->parent = NULL;
                    found = new TreeNode;
                    return true;
                }
            }
            else
            {
                TreeNode *temp = predecessor(root, found->price);
                if(temp->parent == found)
                {
                    temp->parent = NULL;
                    temp->right = found->right;
                    found->right->parent = temp;
                    root = temp;
                    found = new TreeNode;
                    return true;
                }
                else if (temp->left == NULL)
                {
                    root = temp;
                    temp->parent->right = NULL;
                    temp->parent = NULL;
                    found->right->parent = temp;
                    found->left->parent = temp;
                    temp->left = found->left;
                    temp->right = found->right;
                    found = new TreeNode;
                    return true;
                }
                else
                {
                    root = temp;
                    temp->parent->right = temp->left;
                    temp->left->parent = temp->parent;
                    temp->left = found->left;
                    found->left->parent = temp;
                    temp->parent = NULL;
                    temp->right = found->right;
                    found->right->parent = temp;
                    found = new TreeNode;
                    return true;
                }
            }
        }
        if ((found->right == NULL) && (found->left == NULL))
        {
            if (found == root)
            {
                root = new TreeNode;
                return true;
            }
            TreeNode *parent = found->parent;
            if (parent->right == found)
            {
                parent->right = NULL;
                found = new TreeNode;
                return true;
            }
            else
            {
                parent->left = NULL;
                found = new TreeNode;
                return true;
            }
        }
        else if ((found->right == NULL) || (found->left == NULL))
        {
            if (found->right == NULL)
            {
                TreeNode *temp = found->parent;
                if (temp->left == found)
                {
                    temp->left = found->left;
                    found->left->parent = temp;
                    found = new TreeNode;
                    return true;
                }
                else
                {
                    temp->right = found->left;
                    found->left->parent = temp;
                    found = new TreeNode;
                    return true;
                }
            }
            else
            {

                TreeNode *temp = found->parent;
                if (temp->left == found)
                {
                    temp->left = found->right;
                    found->right->parent = temp;
                    found = new TreeNode;
                    return true;
                }
                else
                {
                    temp->right = found->right;
                    found->right->parent = temp;
                    found = new TreeNode;
                    return true;
                }
            }
        }
        else
        {
            TreeNode *temp = predecessor(root, found->price);
            if (temp->left == NULL)
            {
                if (temp->parent != root)
                {
                    temp->parent->right = NULL;
                }
                else
                {
                    root = temp;
                }
                if (found->parent != NULL)
                {
                    if (found->parent->right == found)
                    {
                        found->parent->right = temp;
                    }
                    else
                    {
                        found->parent->left = temp;
                    }
                }
                temp->parent = found->parent;
                found->right->parent = temp;
                found->left->parent = temp;
                temp->left = found->left;
                temp->right = found->right;
                found = new TreeNode;
                return true;
            }
            else
            {
                if (temp->parent != found)
                {
                    temp->parent->right = temp->left;
                    temp->left->parent = temp->parent;
                    temp->left = found->left;
                    found->left->parent = temp;
                }
                if (found->parent != NULL)
                {
                    if (found->parent->right == found)
                    {
                        found->parent->right = temp;
                    }
                    else
                    {
                        found->parent->left = temp;
                    }
                }
                temp->right = found->right;
                found->right->parent = temp;
                temp->parent = found->parent;
                found = new TreeNode;
                return true;
            }
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
        pretraversal(root);
        return;
    }
    else if (typeOfTraversal == 1)
    {
        posttraversal(root);
        return;
    }
    if (typeOfTraversal == 2)
    {
        intraversal(root);
        return;
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    return getmin(root);
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) 
{ 
    return routes(root,lowerPriceBound,upperPriceBound);
}

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

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
    root = new TreeNode;
}
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    if(root->JourneyCode == JourneyCode) return false;
    if(root->price == 0)
    {
        root->JourneyCode = JourneyCode;
        root->price = price;
        return true;
    }
    
    if(price >= root->price)
    {
        if(root->right == nullptr)
        {
            TreeNode *right = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            (*root).right = right;
            return true;
        }
        else
        {
            TreeNode *curr = root;
            root = root->right;
            bool val = BST::insert(JourneyCode, price);
            root = curr;
            return val;
        }
    }

    else
    {
        if(root->left == nullptr)
        {
            TreeNode *left = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            root->left = left;
            return true;
        }    
        else
        {
            TreeNode *curr = root;
            root = root->left;
            bool val = BST::insert(JourneyCode, price);
            root = curr;
            return val;
        }
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if(root->JourneyCode == JourneyCode && root->price == price) return true;

    if(price >= root->price)
    {
        if(root->right == nullptr) return false;
        else
        {
            TreeNode *curr = root;
            root = root->right;
            bool val = BST::find(JourneyCode, price);
            root = curr;
            return val;
        }
    }

    else
    {
        if(root->left == nullptr) return false;
        else
        {
            TreeNode *curr = root;
            root = root->left;
            bool val = BST::find(JourneyCode, price);
            root = curr;
            return val;
        }
    }
}
//----------------------ADDITIONAL FUNCTIONS ADDED BY ME------------------------
TreeNode* BST::getMin(TreeNode *n)
{
    if(n->left == nullptr) return n;
    else
    {
        return BST::getMin(n->left);
    }
}

TreeNode* BST::findNode(int JourneyCode, int price)
{
    TreeNode* val = nullptr;
    if(root->JourneyCode == JourneyCode && root->price == price) return root;

    if(price >= root->price)
    {
        TreeNode* curr = root;
        root = root->right;
        val = BST::findNode(JourneyCode, price);
        root = curr;
        return val;
    }

    else
    {
        TreeNode* curr = root;
        root = root->left;
        val = BST::findNode(JourneyCode, price);
        root = curr;
        return val;
    }

    return val;
}
//---------------------------------------------------------------------------

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode* n = BST::findNode(JourneyCode, price);
    if(n == nullptr) return false;
    


    if(n == root)
    {
       if(n->left == nullptr && n->right != nullptr) 
       {
            n->right->parent = nullptr;
            root = n->right;
       }
       if(n->left!= nullptr && n->right == nullptr)
       {
            n->left->parent = nullptr;
            root = n->left;
       }

       if(n->left==nullptr && n->right==nullptr)
       {
            root = new TreeNode();
       }
       delete n;
       return true;
    }

    if(n->left == nullptr && n->right == nullptr)
    {
        if(n->price >= n->parent->price)
        {
            n->parent->right = nullptr;
        }
        else
        {
            n->parent->left = nullptr;
        }
        delete n;
        return true;
    }

    if(n->left == nullptr && n->right != nullptr)
    {
        if(n->price >= n->parent->price)
        {
            n->parent->right = n->right;
            n->right->parent = n->parent;
        }
        else
        {
            
            n->parent->left = n->right;
            n->right->parent = n->parent;
        }
        delete n;
        return true;
    }

    if(n->left != nullptr && n->right == nullptr)
    {
        if(n->price >= n->parent->price)
        {
            n->parent->right = n->left;
            n->left->parent = n->parent;
        }
        else
        {
            n->parent->left = n->left;
            n->left->parent = n->parent;
        }
        delete n;
        return true;
    }

    if(n->left != nullptr && n->right != nullptr)
    {
        cout<<"Double child delete"<<endl;
        TreeNode *replacement = BST::getMin(n->right);
        if(n->price>= n->parent->price)
        {
            n->parent->right = replacement;
            replacement->left = n->left;
            replacement->parent->left = replacement->right;
            replacement->right = n->right;
            replacement->parent = n->parent;

        }

        else
        {
            n->parent->left = replacement;
            replacement->left = n->left;
            replacement->parent->left = replacement->right;
            replacement->right = n->right;
            replacement->parent = n->parent;

        }
        delete n;
        return true;
    }

    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal) {return; }

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    if(root->left==nullptr) return root->price;
    else
    {
        TreeNode *curr = root;
        root = root->left;
        int val = BST::getMinimum();
        root = curr;
        return val;
    }
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {return 0; }

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
 
void BST::customLoad (int flag, string filename) { return; }


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



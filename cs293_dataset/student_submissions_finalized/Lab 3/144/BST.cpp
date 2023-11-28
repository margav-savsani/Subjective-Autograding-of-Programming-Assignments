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
    root = nullptr;
}
BST::BST(TreeNode *root)
{
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
    this->root = root;
}

// Returns true if journey with journey code is found.
bool BST::find(int JourneyCode, TreeNode *node_ptr)
{
    if (node_ptr == NULL)
        return false;

    if (node_ptr->JourneyCode == JourneyCode)
        return true;

    return (find(JourneyCode, node_ptr->left) || find(JourneyCode, node_ptr->right));
};

bool BST::find(int JourneyCode, int price, TreeNode *node_ptr)
{
    if (node_ptr == NULL)
        return false;

    if (node_ptr->JourneyCode == JourneyCode && node_ptr->price == price)
        return true;

    return (find(JourneyCode, node_ptr->left) || find(JourneyCode, node_ptr->right));
};

void BST::traverse(int typeOfTraversal, TreeNode *node_ptr)
{
    switch (typeOfTraversal)
    {
    case PRE_ORDER:
        if (node_ptr == NULL)
            return;
        std::cout << node_ptr->price;
        traverse(typeOfTraversal, node_ptr->left);
        traverse(typeOfTraversal, node_ptr->right);
        return;
        break;

    case POST_ORDER:
        if (node_ptr == NULL)
            return;
        traverse(typeOfTraversal, node_ptr->left);
        traverse(typeOfTraversal, node_ptr->right);
        std::cout << node_ptr->price;
        return;
        break;

    case IN_ORDER:
        if (node_ptr == NULL)
            return;
        traverse(typeOfTraversal, node_ptr->left);
        std::cout << node_ptr->price;
        traverse(typeOfTraversal, node_ptr->right);
        return;
        break;

    default:
        break;
    }

    return;
}

// Returns true if
//  Returns false, if given JourneyCode is already present in the BST
//  Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{

    TreeNode *temp = new TreeNode(JourneyCode, price);

    if (root == nullptr)
    {
        root = temp;
        root->parent = nullptr;
        return true;
    }

    if (find(JourneyCode, root))
        return false;

    TreeNode *next_ptr;
    TreeNode *parent_to_add = root;

    if (price <= root->price)
    {
        next_ptr = root->left;
    }

    else
        next_ptr = root->right;

    while (next_ptr != nullptr)
    {
        parent_to_add = next_ptr;

        if (price <= parent_to_add->price)
        {
            next_ptr = parent_to_add->left;
        }

        else
            next_ptr = parent_to_add->right;
    }

    if (price <= parent_to_add->price)
    {
        parent_to_add->left = temp;
        temp->parent = parent_to_add;
    }

    else
    {
        parent_to_add->right = temp;
        temp->parent = parent_to_add;
    }

    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    return find(JourneyCode, price, root);
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool BST::remove(int JourneyCode, int price)
{
    if (!find(JourneyCode, price))
        return false;


    TreeNode *ptr = root;

    while (true)
    {
        if (ptr->JourneyCode == JourneyCode)
            break;

        if (price <= ptr->price)
        {
            ptr = ptr->left;
        }

        else
        {
            ptr = ptr->right;
        }
    }


    if (ptr->left == NULL && ptr->right == NULL)
    {
        if (ptr == root)
        {
            delete root;
            root = nullptr;
        }

        else
        {
            TreeNode *parent = ptr->parent;

            if (parent->left == ptr)
                parent->left = nullptr;
            else
                parent->right = nullptr;
            delete ptr;
        }

        return true;
    }

    if (ptr->left == NULL || ptr->right == NULL){
        if(ptr == root){
            TreeNode* next_ptr;
            if (ptr->left == NULL){
                root = ptr->right;
                root->parent = nullptr;
            }

            else{
                ptr->left = root;
                root->parent = nullptr;
            }

            delete ptr;
        }

        else{
            TreeNode* parent = ptr->parent;

            if (ptr->left == NULL){
                if(parent->left == ptr){
                    parent->left = ptr->right;
                    ptr->right->parent = parent;
                }

                else{
                    parent->right = ptr->right;
                    ptr->right->parent = parent;
                }
            }

            else{
               if(parent->left == ptr){
                    parent->left = ptr->left;
                    ptr->left->parent = parent;
                }

                else{
                    parent->right = ptr->left;
                    ptr->left->parent = parent;
                } 
            }

            delete ptr;
        }
        return true;
    }

    else{
        TreeNode* next_ptr = ptr->left;

        while(next_ptr->right != NULL){
            next_ptr = next_ptr->right;      
        }

        int temp_price = next_ptr->price;
        int temp_journey = next_ptr->JourneyCode;

        remove(next_ptr->JourneyCode, next_ptr->price);

        ptr->price = temp_price;
        ptr->JourneyCode = temp_journey;

        return true;
    }
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    traverse(typeOfTraversal, root);
    std::cout << '\n';
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    if (root == NULL)
    {
        return 0;
    }

    TreeNode *ptr = root;

    while (ptr->left != NULL)
    {
        ptr = ptr->left;
    }

    return ptr->price;
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

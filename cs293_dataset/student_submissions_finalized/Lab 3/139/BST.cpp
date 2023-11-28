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
    // root = new TreeNode();
}
BST::BST(TreeNode *root)
{
    this->root = root;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    TreeNode *y = nullptr;
    TreeNode *x = this->root;
    // traversing through the tree (x as the place about to be inserted, y as parent of the x).
    while (x != nullptr)
    {
        y = x;
        if (x->JourneyCode == JourneyCode && x->price == price)
        {
            return false;
        }
        if (price < x->price)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    // constructing new element:
    TreeNode *about_to_insert;
    about_to_insert = new TreeNode(JourneyCode, price);
    about_to_insert->parent = y;
    // first element to be added(root even not defined, we have to insert root).
    if (y == nullptr)
    {
        this->root = about_to_insert;
    }
    // else,adding new element depending upon parent node
    else if (about_to_insert->price <= y->price)
    {
        y->left = about_to_insert;
    }
    else if (about_to_insert->price > y->price)
    {
        y->right = about_to_insert;
    }
    return true;
}

TreeNode *BST::getMin(TreeNode *root)
{
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}

TreeNode *BST::getMax(TreeNode *root)
{
    while (root->right != nullptr)
    {
        root = root->right;
    }
    return root;
}

TreeNode *BST::getPredecessor(TreeNode *node)
{
    // if left subtree is non-empty: simply maximum of left subtree.
    if (node->left != nullptr)
    {
        return getMax(node->left);
    }
    // else, we have to traverse back and find the next most minimum than node in that tree.
    TreeNode *predecessor = node->parent;
    // traversing upwards:
    while (predecessor != nullptr && node == predecessor->left)
    {
        node = predecessor;
        predecessor = predecessor->parent;
    }
    // returns predecessor if found, else returns nullptr;
    return predecessor;
}

TreeNode *BST::getSuccessor(TreeNode *node)
{
    // if right subtree is non-empty: simply minimum of right subtree.
    if (node->right != nullptr)
    {
        return getMin(node->right);
    }
    // else, we have to traverse back and find the next most maximum than node.
    TreeNode *successor = node->parent;
    // traversing upwards:
    while (successor != nullptr && node == successor->right)
    {
        node = successor;
        successor = successor->parent;
    }
    // returns successor if found, else returns nullptr;
    return successor;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode *node = this->root;
    // traversing through the tree
    while (node != nullptr)
    {
        if (JourneyCode == node->JourneyCode && price == node->price)
        {
            return true;
        }
        else
        {
            if (price <= node->price)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
    }
    return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *node = this->root;
    // traversing through the tree
    while (node != nullptr)
    {
        if (JourneyCode == node->JourneyCode && price == node->price)
        {
            // deletion of the corresponding element from the tree:

            // 1.element had no children
            if (node->left == nullptr && node->right == nullptr)
            {
                if (node->parent->left == node)
                {
                    node->parent->left = nullptr;
                }
                else
                {
                    node->parent->right = nullptr;
                }
                node = nullptr;
                return true;
            }

            // 2.element had one children
            else if (node->left == nullptr)
            {
                node->parent = node->right;
                if (node->parent->left == node)
                {
                    node->parent->left = nullptr;
                }
                else
                {
                    node->parent->right = nullptr;
                }
                node = nullptr;
                return true;
            }
            else if (node->right == nullptr)
            {
                node->parent = node->left;
                if (node->parent->left == node)
                {
                    node->parent->left = nullptr;
                }
                else
                {
                    node->parent->right = nullptr;
                }
                node = nullptr;
                return true;
            }

            // 3.element had two children
            else
            {
                TreeNode *node_successor = getSuccessor(node);
                node->JourneyCode = node_successor->JourneyCode;
                node->price = node_successor->price;
                cout << node_successor->JourneyCode << endl;
                if (node_successor->parent->left == node_successor)
                {
                    node_successor->parent->left = nullptr;
                }
                else
                {
                    node_successor->parent->right = nullptr;
                }
                node_successor = nullptr;
                return true;
            }
        }
        else
        {
            if (price <= node->price)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
    }
    return false;
    // if (!find(JourneyCode, price))
    // {
    //     return false;
    // }
    // else
    // {
    //     TreeNode *y, *x, *z;
    //     z = new TreeNode(JourneyCode, price);
    //     if (z->left == nullptr || z->right == nullptr)
    //     {
    //         y = z;
    //     }
    //     else
    //         y = getSuccessor(z);

    //     if (y->left != nullptr)
    //     {
    //         x = y->left;
    //     }
    //     else
    //     {
    //         x = y->right;
    //     }
    //     if (x != nullptr)
    //     {
    //         x->parent = y->parent;
    //     }
    //     if (y->parent == nullptr)
    //     {
    //         root = x;
    //     }
    //     else if (y == y->parent->left)
    //     {
    //         y->parent->left = x;
    //     }
    //     else
    //     {
    //         y->parent->right = x;
    //     }
    //     if (y != z)
    //     {
    //         z->price = y->price;
    //         z->JourneyCode = y->JourneyCode;
    //     }
    //     return true;
    // }
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::print_preorder(TreeNode *node)
{
    if (node == nullptr)
        return;
    else
    {
        cout << node->JourneyCode << endl;
        print_preorder(node->left);
        print_preorder(node->right);
    }
}

void BST::print_postorder(TreeNode *node)
{
    if (node == nullptr)
        return;
    else
    {
        print_postorder(node->left);
        print_postorder(node->right);
        cout << node->JourneyCode << endl;
    }
}

void BST::print_inorder(TreeNode *node)
{
    if (node == nullptr)
        return;
    else
    {
        print_inorder(node->left);
        cout << node->JourneyCode << endl;
        print_inorder(node->right);
    }
}

void BST::traverse(int typeOfTraversal)
{
    if (typeOfTraversal == PRE_ORDER)
    {
        print_preorder(this->root);
    }
    else if (typeOfTraversal == POST_ORDER)
    {
        print_postorder(this->root);
    }
    else if (typeOfTraversal == IN_ORDER)
    {
        print_inorder(this->root);
    }
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    return getMin(this->root)->price;
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
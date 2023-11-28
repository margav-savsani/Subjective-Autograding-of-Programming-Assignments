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

BST::BST(){
    root = nullptr;
}
BST::BST(TreeNode *root){
    this->root = root;
    root->parent = nullptr;
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price){
    if (find(JourneyCode, price)){
        return false;
    }
    else{
        TreeNode *tmp = root;
        TreeNode *parent = nullptr;
        bool dir;
        while (tmp != nullptr){
            if (tmp->price >= price){
                parent = tmp;
                tmp = tmp->left;
                dir = true;
            }
            else{
                parent = tmp;
                tmp = tmp->right;
                dir = false;
            }
        }
        if (parent != nullptr){
            TreeNode tmp_1 = TreeNode(JourneyCode, price, nullptr, nullptr, parent);
            tmp = &tmp_1;
            if (dir){
                parent->left = tmp;
            }
            else{
                parent->right = tmp;
            }
        }
        else{
            TreeNode root_1 = TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
            root = &root_1;
        }
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price){
    TreeNode *tmp = root;
    while (tmp != nullptr){
        if (tmp->price == price){
            if (tmp->JourneyCode == JourneyCode){
                return true;
            }
            tmp = tmp-> left;
        }
        else if (tmp->price > price){
            tmp = tmp->left;
        }
        else{
            tmp = tmp->right;
        }
    }
    return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
    TreeNode *tmp = root;
    if (tmp->JourneyCode == JourneyCode && tmp->price == price){
        if (root->left == nullptr && root->right == nullptr){
            root = nullptr;
        }
        else if (root->left != nullptr && root->right == nullptr){
            root = root->left;
            root->parent = nullptr;
        }
        else if (root->left == nullptr && root->right != nullptr){
            root = root->right;
            root->parent = nullptr;
        }
        else{
            TreeNode *tmp1 = root->left;
            TreeNode *pred = nullptr;
            while (tmp1 != nullptr){
                pred = tmp1;
                tmp1 = tmp1->right;
            }
            TreeNode *pred_parent =pred->parent;
            pred_parent->right = pred->left;
            root = pred;
            root->left = tmp->left;
            root->right = tmp->right;
        }
    }
    else{
        TreeNode *node = nullptr;
        while(tmp != nullptr){
            if (tmp->price == price){
                if (tmp->JourneyCode == JourneyCode){
                    node = tmp;
                }
                tmp = tmp-> left;
            }
            else if (tmp->price > price){
                tmp = tmp->left;
            }
            else{
                tmp = tmp->right;
            }
        }
        if (node == nullptr){
            return false;
        }
        TreeNode *parent = node->parent;
        if (node->left == nullptr && node->right == nullptr){
            if (parent->left == node) parent->left = nullptr;
            else parent->right = nullptr;
        }
        else if (node->left != nullptr && node->right == nullptr){
            if (parent->left == node) parent->left = node->left;
            else parent->right = node->left;
        }
        else if (node->left == nullptr && node->right != nullptr){
            if (parent->left == node) parent->left = node->right;
            else parent->right = node->right;
        }
        else{
            TreeNode *tmp1 = node->left;
            TreeNode *pred = nullptr;
            while (tmp1 != nullptr){
                pred = tmp1;
                tmp1 = tmp1->right;
            }
            TreeNode *pred_parent =pred->parent;
            pred_parent->right = pred->left;
            if (parent->left == node){
                parent->left = pred;
                pred->left = node->left;
                pred->right = node->right;
            }
            else{
                parent->right = pred;
                pred->left = node->left;
                pred->right = node->right;
            }
        }
    }
    return true;
}
	
// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal){
    t_traverse(root, typeOfTraversal);
    return;
}

// This is an extra function created by me to make the 'traverse' function work as desired

void BST::t_traverse(TreeNode *start, int typeOfTraversal){
    TreeNode *tmp = start;
    if (typeOfTraversal == PRE_ORDER){
        while (tmp != nullptr){
            cout << tmp->JourneyCode << endl;
            t_traverse(tmp->left, typeOfTraversal);
            t_traverse(tmp->right, typeOfTraversal);
        }
    }
    else if (typeOfTraversal == IN_ORDER){
        while (tmp != nullptr){
            t_traverse(tmp->left, typeOfTraversal);
            cout << tmp->JourneyCode << endl;
            t_traverse(tmp->right, typeOfTraversal);
        }
    }
    else if (typeOfTraversal == POST_ORDER){
        while (tmp != nullptr){
            t_traverse(tmp->left, typeOfTraversal);
            t_traverse(tmp->right, typeOfTraversal);
            cout << tmp->JourneyCode << endl;
        }
    }
    return;
}

// Returns the price of the cheapest journey
int BST::getMinimum(){
    TreeNode *tmp = root;
    if (tmp == nullptr){
        return 0;
    }
    TreeNode *parent = nullptr;
    while (tmp != nullptr){
        parent = tmp;
        tmp = tmp->left;
    }
    return parent->price;
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

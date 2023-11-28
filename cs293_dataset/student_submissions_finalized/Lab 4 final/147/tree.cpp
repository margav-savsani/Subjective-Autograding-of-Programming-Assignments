// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance(){
    return root ? root->getImbalance(): 0;
}

TreeNode *BST::insert(int journeyCode, int price, TreeNode *parent, bool left){
        
    // O(1)
    TreeNode *to_insert = new TreeNode(journeyCode, price, parent);
    if (parent) 
        if (left) parent->left = to_insert; else parent->right = to_insert;

    // else parent is nullptr which indicates that we must insert into the root(empty tree).
    else{
        assert(!root);
        root = to_insert;
        return to_insert;
    }

    // O(h)
    // go up the path and update all ancestors' shortest and longest path variables
    TreeNode *ancestor = parent;
    while (ancestor){
        // i is the distance from the ancestor to this leaf.
        if (ancestor->left && ancestor->right) 
            ancestor->shortestPathLength = 1 + min(ancestor->left->shortestPathLength, ancestor->right->shortestPathLength);
        else ancestor->shortestPathLength = 0; 
        
        assert(ancestor->left || ancestor->right);
        ancestor->longestPathLength = 1 + max((ancestor->left) ? ancestor->left->longestPathLength: 0, (ancestor->right) ? ancestor->right->longestPathLength: 0);
        // the above is valid as long as ancestor is not a leaf, which is everytime.
        // if (ancestor->longestPathLength == 1) ancestor->longestPathLength = 0; // if ancestor is a leaf, change longestPathLength to 0.
        ancestor = ancestor->parent; // move upwards.
    }
    return to_insert; // a pointer to the newly inserted node.
}


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
        cout << "(" << root->JourneyCode << "," << root->shortestPathLength << "," << root->longestPathLength << 
        ")" << endl;
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
        result.push_back(to_string(root->JourneyCode) + "\n");
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


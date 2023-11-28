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

void TreeNode::update_path()
{
    if (this->parent->left->longestPathLength > this->parent->right->longestPathLength)   
    this->parent->longestPathLength = this->parent->left->longestPathLength +1;
    else this->parent->longestPathLength = this->parent->right->longestPathLength + 1;
    if (this->parent->left->shortestPathLength < this->parent->right->shortestPathLength) this->parent->shortestPathLength = this->parent->left->shortestPathLength +1;
    else this->parent->shortestPathLength = this->parent->right->shortestPathLength + 1;
    if (this->parent != nullptr) this->parent->update_path();
}

bool TreeNode::insert(int JourneyCode, int price)
{
    if (this == nullptr)
    {
        this->JourneyCode = JourneyCode;
        this->price = price;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        shortestPathLength = 0;
        longestPathLength = 0;
        return true;
    }
    else if (this->price > price) 
    {
        if (this->left == nullptr)
        {
            this->left->JourneyCode = JourneyCode;
            this->left->price = price;
            this->left->parent = this;
            this->left->longestPathLength = 0;
            this->right->longestPathLength = 0;
            this->left->update_path();
            return true;
        }
        else return this->left->insert(JourneyCode, price);
    }
    else if (this->price == price)
    {
        if (this->JourneyCode == JourneyCode) return false;
        else if (this->right == nullptr)
        {
            this->right->JourneyCode = JourneyCode;
            this->right->price = price;
            this->right->parent = this;
            this->right->update_path();
            return true;
        }
        else return this->right->insert(JourneyCode, price);
    }
    else 
    {
        if (this->right == nullptr) 
        {
            this->right->JourneyCode = JourneyCode;
            this->right->price = price;
            this->right->parent = this;
            this->update_path();
            return true;
        }
        else return this->right->insert(JourneyCode, price);
    }
}

bool TreeNode::find(int JourneyCode, int price)
{
    if (this == nullptr)
    {
        return false;
    }
    else if (this->price > price) return (this->left->find(JourneyCode, price));
    else if (this->price == price)
    {
        if (this->JourneyCode == JourneyCode) return true;
        else return this->right->find(JourneyCode, price);
    }
    else return this->right->find(JourneyCode, price);
}

int BST::getImbalance()
{
    if (root == nullptr)
        return 0;
    else
        return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace/augment it with appropriate code,
    // similar to what you had done in lab assignment 3.

    return root->insert(JourneyCode, price);

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting

}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // You can look at the implementation of insert to code this part up.

    root->find(JourneyCode, price);

    return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // Recall from CS 213 lectures about the various ways in which the
    // BST can be restructured when a node is deleted. You can implement
    // any of these alternatives.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to nodes whose position in the BST is affected
    // by the remove.

    return false;
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

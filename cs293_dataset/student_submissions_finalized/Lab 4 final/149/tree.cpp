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

void inorder(TreeNode *t)
{
    if (t == nullptr)
        return;
    inorder(t->left);
    inorder(t->right);
}

int BST::getImbalance()
{
    if (root == nullptr)
        return 0;
    else
        return root->getImbalance();
}

bool addNode(TreeNode *t, int code, int price)
{
    if (t->JourneyCode == 0)
    {
        t->price = price;
        t->JourneyCode = code;
        return true;
    }
    else if (t->JourneyCode > code)
    {
        if (t->left == nullptr)
        {
            t->left = new TreeNode();
            t->left->parent = t;
            t->left->price = price;
            t->left->JourneyCode = code;
            return true;
        }
        else
        {
            return addNode(t->left, code, price);
        }
    }
    else if (t->JourneyCode < code)
    {
        if (t->right == nullptr)
        {
            t->right = new TreeNode();
            t->right->parent = t;
            t->right->price = price;
            t->right->JourneyCode = code;
            return true;
        }
        else
        {
            return addNode(t->right, code, price);
        }
    }
}

int shortPath(TreeNode *t, int c)
{
    if (t == nullptr)
        return c;
    c++;
    int left = shortPath(t->left, c);
    int right = shortPath(t->right, c);
    return min(left, right);
}

int longPath(TreeNode *t, int c)
{
    if (t == nullptr)
        return c;
    c++;
    int left = longPath(t->left, c);
    int right = longPath(t->right, c);
    return max(left, right);
}

void BST::updatePath(TreeNode *t)
{
    if (t == nullptr)
        return;
    t->longestPathLength = longPath(t, 0);
    t->shortestPathLength = shortPath(t, 0);
    updatePath(t->left);
    updatePath(t->right);
}

bool BST::insert(int JourneyCode, int price)
{
    if (root == nullptr)
    {
        root = new TreeNode(JourneyCode, price);
        root->parent = nullptr;
        return true;
    }
    else
        return addNode(root, JourneyCode, price);
}

TreeNode *findNode(TreeNode *t, int code, int price)
{
    if (t == nullptr)
    {
        return t;
    }
    else if (t->price == price && t->JourneyCode == code)
    {
        return t;
    }
    else if (t->JourneyCode > code)
    {
        return findNode(t->left, code, price);
    }
    else
    {
        return findNode(t->right, code, price);
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    TreeNode *t = findNode(root, JourneyCode, price);
    if (t == nullptr)
        // cout << "3546" << endl;
        return false;
    else
        return true;
    // You can look at the implementation of insert to code this part up.

    return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

TreeNode *findChild(TreeNode *t)
{
    if (t->left == nullptr)
        return t;
    else
    {
        return findChild(t->left);
    }
}

bool BST::remove(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    TreeNode *t = findNode(root, price, JourneyCode);
    if (t == nullptr)
        return false;
    else
    {
        if (t->left == nullptr && t->right == nullptr)
        {
            if (t->parent->left == t)
            {
                t->parent->left = nullptr;
            }
            else
                t->parent->right = nullptr;
            return true;
        }
        else if (t->right == nullptr && t->left != nullptr)
        {
            if (t->parent->left == t)
            {
                t->parent->left = t->left;
                t->left->parent = t->parent;
            }
            else
            {
                t->parent->right = t->left;
                t->left->parent = t->parent;
            }
        }
        else if (t->right != nullptr && t->left == nullptr)
        {
            if (t->parent->left == t)
            {
                t->parent->left = t->right;
                t->right->parent = t->parent;
            }
            else
            {
                t->parent->right = t->right;
                t->left->parent = t->parent;
            }
        }
        else
        {
            TreeNode *x = findChild(t->right);
            x->parent->left = nullptr;
            x->parent = t->parent;
            x->left = t->left;
            x->right = t->right;
        }
        updatePath(root);
        return true;
    }
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

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

    struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;

    while (currNode != nullptr)
    {
        if (currNode->JourneyCode < JourneyCode)
        {
            parentOfCurrNode = currNode;
            currNode = currNode->right;
        }
        else if (currNode->JourneyCode > JourneyCode)
        {
            parentOfCurrNode = currNode;
            currNode = currNode->left;
        }
        else
        {   currNode->JourneyCode == JourneyCode;
            return false;
        }
    }
    if(parentOfCurrNode->JourneyCode>JourneyCode){
        currNode=new TreeNode(JourneyCode,price);
        parentOfCurrNode->left=currNode;
        currNode->parent=parentOfCurrNode;
        currNode->longestPathLength=0;
        currNode->shortestPathLength=0;
    }
    else{
        currNode=new TreeNode(JourneyCode,price);
        parentOfCurrNode->right=currNode;
        currNode->parent=parentOfCurrNode;
        currNode->longestPathLength=0;
        currNode->shortestPathLength=0;
    }
    int curr_length=1;

    while(true){
        if(parentOfCurrNode->longestPathLength<curr_length){
            parentOfCurrNode->longestPathLength=curr_length;
            parentOfCurrNode=parentOfCurrNode->parent;
        }
        else break;
    }
    int curr_length=1;
    while(true){
        if(parentOfCurrNode->shortestPathLength>curr_length){
            parentOfCurrNode->shortestPathLength=curr_length;
            parentOfCurrNode=parentOfCurrNode->parent;
        }
        else break;
    }
        // JourneyCode is not present in the BST.  We must now
        // insert an appropriate child of parentOfCurrNode.
        // Please implement this part yourself.
        //
        // Do not forget to update shortestPathLength and
        // longestPathLength of (possibly all) BST nodes in the
        // path from the root to the new node you are inserting
    
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if (root == NULL)
    {
        return false;
    }
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // You can look at the implementation of insert to code this part up.

    TreeNode *k = root;
    while (true)
    {

        if ((JourneyCode) < (k->JourneyCode))
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
        else if ((JourneyCode) > (k->JourneyCode))
        {
            if (k->right == NULL)
            {
                return false;
            }
            else
                k = k->right;
        }
        if (JourneyCode == k->JourneyCode)
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

TreeNode *BST::minforsuccessor(TreeNode *N)
{
    while (N->left != nullptr)
    {
        N = N->left;
    }
    return N;
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

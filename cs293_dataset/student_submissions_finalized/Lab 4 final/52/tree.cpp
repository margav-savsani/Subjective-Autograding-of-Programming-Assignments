// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns the imbalance of the root node of the BST
int BST::getImbalance()
{
    if (root == nullptr)
        return 0;
    else
        return root->getImbalance();
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace/augment it with appropriate code,
    // similar to what you had done in lab assignment 3.
    TreeNode *currNode = root; 
    TreeNode *parentOfCurrNode = nullptr;
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
        { // currNode->JourneyCode == JourneyCode
            return false;
        }
    }
    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    TreeNode* newNode = new TreeNode(JourneyCode, price);
    newNode->parent = parentOfCurrNode;
    newNode->shortestPathLength = 0;
    newNode->longestPathLength = 0;

    if(parentOfCurrNode == nullptr){
        root = newNode;
    }
    else{
        if(JourneyCode < parentOfCurrNode->JourneyCode){
            parentOfCurrNode->left = newNode;
        }
        else{
            parentOfCurrNode->right = newNode;
        }
    }


    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    TreeNode* y = parentOfCurrNode;
    while(y != nullptr){
        if(y->updatePathLengths())
            y = y->parent;
        else
            break;
    }

    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // You can look at the implementation of insert to code this part up.

    TreeNode *x = root;
    while (x != nullptr && x->JourneyCode != JourneyCode)
    {
        if (JourneyCode < x->JourneyCode)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    if (x == nullptr)
        return false;
    else
        return x->price == price;
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

    if(root == nullptr) return false;

    TreeNode* updateFrom;

    // Special case for root
    if(root->JourneyCode == JourneyCode){
        TreeNode* x = root;
        // Case 1: Both child are null
        if(x->left == nullptr && x->right == nullptr){
            root = nullptr;
            delete x;
        }
        // Case 2: Left child is null
        else if(x->left == nullptr){
            root = x->right;
            x->right->parent = root;
            delete x;
        }
        // Case 3: Right child is null
        else if(x->right == nullptr){
            root = x->left;
            x->left->parent = root;
            delete x;
        }
        // Case 4: No child is null
        else{
            // Get successor
            TreeNode* z = x->right;
            while (z->left != nullptr){
                z = z->left;
            }

            updateFrom = z->parent;

            // Replace at root
            x->JourneyCode = z->JourneyCode;
            x->price = z->price;

            // Delete successor
            if(z->left == nullptr && z->right == nullptr){
                if(z->parent->left == z) z->parent->left = nullptr;
                else if(z->parent->right == z) z->parent->right = nullptr;
                delete z;
            }
            else{
                if(z->parent->left == z) z->parent->left = z->right;
                else if(z->parent->right == z) z->parent->right = z->right;
                z->right->parent = z->parent;
                delete z;
            }

        }

        
        while(updateFrom != nullptr && updateFrom->updatePathLengths()){
            updateFrom = updateFrom->parent;
        }

        return true;
    }
    
    TreeNode* x = root;
    // Find the node with matching journeyCode
    while(x != nullptr && (x->JourneyCode != JourneyCode)){
        if(JourneyCode < x->JourneyCode){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    if(x == nullptr) return false;
    else{
        TreeNode* y = x->parent;
        // Case 1: Both child are null
        if(x->left == nullptr && x->right == nullptr){
            if(y->left == x) y->left = nullptr;
            else if(y->right == x) y->right = nullptr;
            delete x;
            updateFrom = y;
        }
        // Case 2: Left child is null
        else if(x->left == nullptr){
            if(y->left == x) y->left = x->right;
            else if(y->right == x) y->right = x->right;
            x->right->parent = y;
            delete x;
            updateFrom = y;
        }
        // Case 3: Right child is null
        else if(x->right == nullptr){
            if(y->left == x) y->left = x->left;
            else if(y->right == x) y->right = x->left;
            x->left->parent = y;
            delete x;
            updateFrom = y;
        }
        // Case 4: No child is null
        else{
            // Get successor
            TreeNode* z = x->right;
            while (z->left != nullptr){
                z = z->left;
            }

            updateFrom = z->parent;
            
            // Replace at current node
            x->JourneyCode = z->JourneyCode;
            x->price = z->price;

            // Delete successor
            if(z->left == nullptr && z->right == nullptr){
                if(z->parent->left == z) z->parent->left = nullptr;
                else if(z->parent->right == z) z->parent->right = nullptr;
                delete z;
            }
            else{
                if(z->parent->left == z) z->parent->left = z->right;
                else if(z->parent->right == z) z->parent->right = z->right;
                z->right->parent = z->parent;
                delete z;
            }

        }

        while(updateFrom != nullptr && updateFrom->updatePathLengths()){
            updateFrom = updateFrom->parent;
        }

        return true;
    }


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

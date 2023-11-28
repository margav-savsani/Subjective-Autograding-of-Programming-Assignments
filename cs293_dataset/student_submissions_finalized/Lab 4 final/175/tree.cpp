// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

int BST::longest_path(TreeNode *start){
    if (start != nullptr){
        return 1 + max(longest_path(start->left), longest_path(start->right));
    }
    else{
      return 0;
    }
}

int BST::shortest_path(TreeNode *start){
    if (start != nullptr){
        if (start->left == nullptr && start->right != nullptr){
            return 1 + shortest_path(start->right);
        }
        else if (start->left != nullptr && start->right == nullptr){
            return 1 + shortest_path(start->left);
        }
        else{
            return 1 + min(shortest_path(start->left), shortest_path(start->right));
        }
    }
    else{
      return 0;
    }
}

int BST::getImbalance()
{
    return longest_path(root) - shortest_path(root);
}

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace/augment it with appropriate code,
    // similar to what you had done in lab assignment 3.

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    
    if (find(JourneyCode, price)){ // this checks if the ticket is already present or not
        return false;
    }
    else{
        TreeNode *tmp = root;
        TreeNode *parent = nullptr;
        bool dir;       // 'dir' gives the direction of traversing which is used in line 50
        while (tmp != nullptr){
            if (tmp->JourneyCode >= JourneyCode){ // Even if the JourneyCode is equal, I go to left subtree
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
        if (parent != nullptr){ // the 'non-root' case
            if (dir){
                parent->left = new TreeNode(JourneyCode, price, nullptr, nullptr, parent);
            }
            else{
                parent->right = new TreeNode(JourneyCode, price, nullptr, nullptr, parent);
            }
        }
        else{ // the 'root' case
            root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
        }
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
    TreeNode *tmp = root;
    while (tmp != nullptr){
        if (tmp->JourneyCode == JourneyCode){
            if (tmp->price == price){ // return true only if the ticket is found 
                return true;
            }
            tmp = tmp->left; // I go to the left subtree even if JourneyCodes are equal since that's how I have implemented the 'insert' function
        }
        else if (tmp->JourneyCode > JourneyCode){
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

    TreeNode *tmp = root;
    if (tmp == nullptr){ // the 'null-tree' case
        return false;
    }
    else if (tmp->JourneyCode == JourneyCode && tmp->price == price){ // the 'root' case starts here and goes upto line 127
        if (root->left == nullptr && root->right == nullptr){ // zero childs
            root = nullptr;
        }
        else if (root->left != nullptr && root->right == nullptr){ // one child
            root = root->left;
            root->parent = nullptr;
        }
        else if (root->left == nullptr && root->right != nullptr){ // one child
            root = root->right;
            root->parent = nullptr;
        }
        else{               // two childs
            TreeNode *tmp1 = root->left;
            TreeNode *pred = nullptr;
            while (tmp1 != nullptr){
                pred = tmp1;        // finding the predecessor
                tmp1 = tmp1->right;
            }
            if (pred == root->left){ // a separate check to improve the function
                TreeNode *pred_child = pred->left;
                root->JourneyCode = pred->JourneyCode;
                root->price = pred->price;
                root->left = pred_child;
                if (pred_child != nullptr){
                    pred_child->parent = root;
                }
            }
            else{               // swapping the root and the predecessor
                TreeNode *pred_parent =pred->parent;
                pred_parent->right = pred->left;
                root = pred;
                root->left = tmp->left;
                root->right = tmp->right;
            }
        }
    }
    else{                   // the 'non-root' case
        TreeNode *node = nullptr; // finding the 'node' to be deleted
        while(tmp != nullptr){
            if (tmp->JourneyCode == JourneyCode){
                if (tmp->price == price){
                    node = tmp;
                }
                tmp = tmp-> left;
            }
            else if (tmp->JourneyCode > JourneyCode){
                tmp = tmp->left;
            }
            else{
                tmp = tmp->right;
            }
        }
        if (node == nullptr){ // if no 'node' found, the ticket is not present
            return false;
        }
        TreeNode *parent = node->parent;
        if (node->left == nullptr && node->right == nullptr){ // zero childs
            if (parent->left == node) parent->left = nullptr;
            else parent->right = nullptr;
        }
        else if (node->left != nullptr && node->right == nullptr){ // one child
            if (parent->left == node) parent->left = node->left;
            else parent->right = node->left;
        }
        else if (node->left == nullptr && node->right != nullptr){ // one child
            if (parent->left == node) parent->left = node->right;
            else parent->right = node->right;
        }
        else{                   // two childs
            TreeNode *tmp1 = node->left;
            TreeNode *pred = nullptr; // finding the predecessor
            while (tmp1 != nullptr){
                pred = tmp1;
                tmp1 = tmp1->right;
            }
            if (pred == node->left){ // a separate check to improve the function
                TreeNode *pred_child = pred->left;
                node->JourneyCode = pred->JourneyCode;
                node->price = pred->price;
                node->left = pred_child;
                if (pred_child != nullptr){
                    pred_child->parent = node;
                }
            }
            else{                           // swapping the root and the predecessor
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
    }
    return true;
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


#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST() {
    root = nullptr;
}
BST::BST(TreeNode *root) {
    this->root = root;
}

int BST::getImbalance(){
    if (root == nullptr) return 0;
    else return root->getImbalance();
}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price, int &comparisons) {
    if(find(JourneyCode, price, comparisons))        // cant insert if already present
        return false;
    TreeNode *new_node, *null_node, *parent;
    new_node = new TreeNode(JourneyCode, price);
    if(root == nullptr)
        root = new_node;    // inserting the first node of empty tree
    else {                  
        parent = nullptr;
        null_node = root;
        while(null_node != nullptr) {       // finding the position for new node to be inserted
            parent = null_node;
            if(JourneyCode < null_node->JourneyCode)
                null_node = null_node->left;
            else
                null_node = null_node->right;
            comparisons++;
        }
        if(JourneyCode < parent->JourneyCode)
            parent->left = new_node;
        else
            parent->right = new_node;
        comparisons++;

        new_node->parent = parent;
        
        int path=1;
        TreeNode* ancestor = new_node->parent;
        while(ancestor != nullptr) {
            path++;
            if (ancestor->shortestPathLength == 1 && ancestor->left!=nullptr && ancestor->right!=nullptr)
                ancestor->shortestPathLength = 2;
            else
                ancestor->shortestPathLength = min(ancestor->shortestPathLength, path);
            ancestor->longestPathLength = max(ancestor->longestPathLength, path);
            
            ancestor = ancestor->parent;
        }
    }
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price, int &comparisons) {
    TreeNode* node = root;
    while(node != nullptr) {
        if(price == node->price && JourneyCode == node->JourneyCode) {
            return true; comparisons++;}
        else if(JourneyCode < node->JourneyCode){
            node = node->left; comparisons++;}
        else
            node = node->right;
    }
    return false;
}

// Finds the element and returns the pointer to the node (if found), else
TreeNode* BST::find(int &JourneyCode, int &price) {          // a is just to distinguish the signatures
    TreeNode* node = root;
    while(node != nullptr) {
        if(price == node->price && JourneyCode == node->JourneyCode)
            return node;
        else if(JourneyCode < node->JourneyCode)
            node = node->left;
        else
            node = node->right;
    }
    return nullptr;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool BST::remove(int JourneyCode, int price) {
    TreeNode* node = new TreeNode();
    node = find(JourneyCode, price);

    if(!node)       // node to be deleted not present
        return false;

    TreeNode *x,*y;
    if (node->left == nullptr || node->right == nullptr)  y = node;
    else    y = successor(node);

    TreeNode* ancestor = y->parent;

    if (y->left != nullptr)     x = y->left;
    else                        x = y->right;

    if (x!=nullptr)    x->parent = y->parent;

    if (y->parent == nullptr)       root = x;
    else if (y == y->parent->left)  y->parent->left = x;
    else                            y->parent->right = x;

    if (y!=node) {
        node->JourneyCode = y->JourneyCode;
        node->price = y->price;
        node->longestPathLength = y->longestPathLength;
        node->shortestPathLength = y->shortestPathLength;
    }


    while(ancestor != nullptr) {
        if (ancestor->left == nullptr && ancestor->right == nullptr)
            ancestor->shortestPathLength = ancestor->longestPathLength = 1;

        else if (ancestor->left == nullptr) {
            ancestor->shortestPathLength = 1;
            ancestor->longestPathLength = ancestor->right->longestPathLength + 1;
        }
        else if (ancestor->right == nullptr) {
            ancestor->shortestPathLength = 1;
            ancestor->longestPathLength = ancestor->left->longestPathLength + 1;
        }
        else {
            ancestor->shortestPathLength = min(ancestor->left->shortestPathLength, ancestor->right->shortestPathLength) + 1;
            ancestor->longestPathLength = max(ancestor->left->longestPathLength, ancestor->right->longestPathLength) + 1;
        }
        ancestor = ancestor->parent;
    }
    return true;
}

// finds the successor of a node
TreeNode* BST::successor(TreeNode* node) {
    TreeNode* suc = node;
    if (node->right != nullptr) {
        suc = suc->right;
        while (suc->left != nullptr) 
        suc = suc->left;
        return suc;
    }
    else {
        suc = node->parent;
        while (suc!=nullptr && node==suc->right) {
            node = suc;
            suc = suc->parent;
        }
        return suc;
    }
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

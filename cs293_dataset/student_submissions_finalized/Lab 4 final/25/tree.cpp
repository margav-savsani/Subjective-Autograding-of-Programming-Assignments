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
        { // currNode->JourneyCode == JourneyCode
            return false;
        }
    }
    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    if (parentOfCurrNode->JourneyCode < JourneyCode){
        parentOfCurrNode->left = new TreeNode(JourneyCode, price, nullptr, nullptr, parentOfCurrNode);
    }
    else {
        parentOfCurrNode->right = new TreeNode(JourneyCode, price, nullptr, nullptr, parentOfCurrNode);
    }
    
    // The shortestPathLength  and longestPathLength are updated efficiently 
    // once when the getImbalance() function is called

    return true;
}

TreeNode* BST::getNode(int JourneyCode, int price){
    TreeNode* rootptr = root;
    while(rootptr!=nullptr){
        if (JourneyCode<rootptr->JourneyCode){
            rootptr = rootptr->left;
        }
        else if (price==rootptr->price && JourneyCode==rootptr->JourneyCode){
            return rootptr;
        }
        else {rootptr = rootptr->right;}
    }
    if (rootptr==nullptr) return nullptr;
    return ((rootptr->JourneyCode==JourneyCode && rootptr->price==price) ? rootptr : nullptr);
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // You can look at the implementation of insert to code this part up.


    if (getNode(JourneyCode, price)!=nullptr){
        return true;
    }
    return false;
}

TreeNode* BST::twochild_successor(TreeNode* node){
    TreeNode* curr = node->right;
    TreeNode* left = curr->left;
    while(left!=nullptr){
        curr = left;
        left = left->left;
    }
    return curr;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
    TreeNode* del = getNode(JourneyCode, price);
    if (del==nullptr){
        return false;
    }
    // If node has no children, simply delete the node
    if (del->right==nullptr && del->left==nullptr){
        TreeNode* p = del->parent;
        if (p==nullptr){root=nullptr; delete del; return true;}
        char c = (p->left==del ? 'l' : 'r');
        delete del;
        if (c=='l'){
            p->left=nullptr;
        }
        else {p->right=nullptr;}
        return true;
    }

    // If the node has one child
    if (del->right==nullptr || del->left==nullptr){
        TreeNode *p = del->parent;
        TreeNode *child = (del->right==nullptr ? del->left : del->right);
        if (p==nullptr){root = child; child->parent=nullptr; delete del; return true;}
        char c = (p->left==del ? 'l' : 'r');
        delete del;
        if (c=='l'){
            p->left = child;
            child->parent = p;
        }
        else {
            p->right = child;
            child->parent = p;
        }
        return true;
    }
    // If the node has 2 children
    TreeNode* succ = twochild_successor(del);
    // We know that succ has only a right child or no child.

    // Copying successor into the node to be deleted
    del->JourneyCode = succ->JourneyCode;
    del->price = succ->price;
    // Deleting successor, easier to delete than node which has 2 children
    TreeNode* child = succ->right; //could be nullptr
    TreeNode* succ_parent = succ->parent;
    if (succ_parent->left==succ){
        succ_parent->left = child;
    }
    else {
        succ_parent->right=child;
    }
    if (child!=nullptr) {child->parent = succ_parent;}
    delete succ;
    return true;
}

// In a post-order traversal fashion, compute longest paths for each node
int updateLongest(TreeNode* root){
    if (root==nullptr){
        return 0;
    }
    int left = updateLongest(root->left);
    int right = updateLongest(root->right);
    
    return 1 + max(left, right);
}

// In a post-order traversal fashion, compute shortest paths for each node
int updateShortest(TreeNode* root){
    if (root==nullptr){
        return 0;
    }
    int left = updateShortest(root->left);
    int right = updateShortest(root->right);
    return 1 + min(left, right);
}

int TreeNode::getImbalance()
    {
        // Returns how imbalanced the paths starting from this node to the
        // leaves are.  A case of perfect balance would result in the
        // longest and shortest path lengths being equal, so their difference
        // will be 0 (i.e. 0 imbalance).
        // Think about when would we have a case of large imbalance.

        shortestPathLength = updateShortest(this);
        longestPathLength = updateLongest(this);
        return (longestPathLength - shortestPathLength);
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

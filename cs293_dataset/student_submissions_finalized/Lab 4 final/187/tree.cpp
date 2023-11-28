// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
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

bool BST::find(int JourneyCode, int price)
{
    TreeNode *x;
    bool c;
    x = root;
    while (x != NULL)
    {
        if (x->JourneyCode == JourneyCode && x->price == price)
        {
            c = true;
        }
        else
        {
            c = false;
            if (x->JourneyCode < JourneyCode)
            {
                x = x->right;
            }
            else
            {
                x = x->left;
            }
        }
    }
    return c;
}

bool BST::insert(int JourneyCode, int price)
{
    TreeNode *x, *y, *z;
    bool c;
    x = root;
    y = NULL;
    z = new TreeNode(JourneyCode, price);
    if (root == NULL)
    {
        root = z;
        c = true;
    }
    while (x != NULL)
    {
        y = x;
        if (x->JourneyCode == JourneyCode)
        {
            c = false;
        }
        else
        {
            c = true;
        }
        if (x->JourneyCode < JourneyCode)
        {
            x = x->right;
        }
        else if(x->JourneyCode > JourneyCode)
        {
            x = x->left;
        }
    }
    z->parent = y;
    if (y == NULL)
    {
        root = z;
    }
    else if (z->JourneyCode < y->JourneyCode)
    {
        y->left = z;
    }
    else if(z->JourneyCode > y->JourneyCode)
    {
        y->right = z;
    }
    while(z != NULL){
        if(z->parent->shortestPathLength == z->shortestPathLength-1){
            z->shortestPathLength++;
        }
        if(z->longestPathLength == z->parent->longestPathLength+1){
            z->longestPathLength++;
        }
        if(z->shortestPathLength == z->longestPathLength){
            z->longestPathLength++;
        }
    }
    return c;
}
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
TreeNode *search(TreeNode *a,int JourneyCode, int price){
        if(a->JourneyCode == JourneyCode){
        return a;
        }
        if(a->JourneyCode > JourneyCode){
            return search(a->left,JourneyCode,price);
        }
        else{
            return search(a->right,JourneyCode,price);
        }
}
TreeNode* minValueNode(TreeNode* node)
{
    TreeNode* current = node;
    while (current && current->left != NULL)
        current = current->left;
  
    return current;
}
  
  TreeNode *deleteNode( TreeNode *A,int JourneyCode)
{
    // base case
    if (A == NULL)
        return A;
  
    // If the key to be deleted is 
    // smaller than the root's
    // key, then it lies in left subtree
    if (JourneyCode < A->JourneyCode)
        A->left = deleteNode(A->left, JourneyCode);

    else if (JourneyCode > A->JourneyCode)
        A->right = deleteNode(A->right, JourneyCode);

    else {
        if (A->left==NULL and A->right==NULL)
            return NULL;
    
        else if (A->left == NULL) {
            TreeNode* temp = A->right;
            free(A);
            return temp;
        }
        else if (A->right == NULL) {
            TreeNode* temp = A->left;
            free(A);
            return temp;
        }
  
        TreeNode* temp = minValueNode(A->right);
        A->JourneyCode = temp->JourneyCode;
        A->right = deleteNode(A->right, temp->JourneyCode);
    }
    return A;
}
bool BST::remove(int JourneyCode, int price){
    if(find(JourneyCode,price)){
        TreeNode *z = search(root,JourneyCode,price);
        deleteNode(z,JourneyCode);
        return true;
    }
    else{
        return false;
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

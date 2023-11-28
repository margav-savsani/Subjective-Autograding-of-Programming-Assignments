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
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
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
    while (x != NULL && (x->price != price || x->JourneyCode != JourneyCode))
    {
        if (price > x->price)
        {
            x = x->right;
        }
        else
        {
            x = x->left;
        }
    }
    if (x == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  
    TreeNode *x = root;
    TreeNode *y;
    while (x != NULL && (x->price != price || x->JourneyCode != JourneyCode))
    {
        y = x;
        if (price > x->price)
        {
            x = x->right;
        }
        else
        {
            x = x->left;
        }
    }
    if (x == NULL)
    {
        return false;
    }
    if (x->right == NULL && x->left == NULL)
    {
        if (y->right == x)
        {
            y->right = NULL;
        }
        else
        {
            y->left = NULL;
        }
        x->parent = NULL;
    }
    else if (x->right == NULL)
    {
        if (x == root)
        {
            root = x->left;
            root->parent = NULL;
        }
        else if (y->right == x)
        {

            y->right = x->left;
            x->parent = NULL;
            x->left->parent = y;
        }
        else
        {
            y->left = x->left;
            x->parent = NULL;
            x->left->parent = y;
        }
    }
    else if (x->left == NULL)
    {
        if (x == root)
        {
            root = x->right;
            root->parent = NULL;
        }
        else if (y->right == x)
        {
            y->right = x->right;
            x->parent = NULL;
            x->right->parent = y;
        }
        else
        {
            y->left = x->right;
            x->parent = NULL;
            x->right->parent = y;
        }
    }
    else
    {
        TreeNode *succ = x->right;
        TreeNode *succ_p = x;
        while (succ->left != NULL)
        {
            succ_p = succ;
            succ = succ->left;
        }
        if (succ_p == x)
        {
            if (y->right == x)
            {
                y->right = succ;
                succ_p->parent = y;
                succ->left = x->left;
                x->left->parent = succ;
            }
            else
            {
                y->left = succ;
                succ_p->parent = y;
                succ->left = x->left;
                x->left->parent = succ;
            }
            return true;
        }
        succ->left = x->left;
        succ->right = x->right;
        succ->parent = y;
        if (succ_p->right == succ)
        {
            succ_p->right = NULL;
        }
        else
        {
            succ_p->left = NULL;
        }
        succ_p->parent = NULL;
        succ->left = x->left;
        x->left->parent = succ;
        x->left = NULL;
        succ->right = x->right;
        x->right->parent = succ;
        x->right = NULL;
        succ->parent = y;
        x->parent = NULL;

        if (y->right == x)
        {

            y->right = succ;
        }
        else
        {
            y->left = succ;
        }
    }
    return true;
    
  return false;
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


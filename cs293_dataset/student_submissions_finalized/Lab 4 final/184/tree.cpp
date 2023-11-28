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
  
  TreeNode *y = nullptr;
    TreeNode *x = root;
    // We need to create z as a pointer so that the same address is not pointed every time when the function is called.
    TreeNode *z = new TreeNode(JourneyCode, price);

    while (x != nullptr)
    {
        y = x;
        if (z->JourneyCode == x->JourneyCode && z->price == x->price)
        {
            return false;
        }
        if (z->price < x->price)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == nullptr)
    {
        root = z;
    }
    else if (z->price < y->price)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    return true;

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
  bool found = false;
    TreeNode *x = root;
    TreeNode *z = new TreeNode(JourneyCode, price);
    while (x != nullptr)
    {
        if (x->price == z->price && x->JourneyCode == z->JourneyCode)
        {
            found = true;
            break;
        }
        else if (z->price < x->price)
        {
            x = x->left;
        }
        else if (z->price > x->price)
        {
            x = x->right;
        }
    }
    return found;
}

// finds the node that has the given attributes.
TreeNode *BST::find_node(int JourneyCode, int price)
{
    bool found = false;
    TreeNode *x = root;
    TreeNode *z = new TreeNode(JourneyCode, price);
    while (x != nullptr)
    {
        if (x->price == z->price && x->JourneyCode == z->JourneyCode)
        {
            found = true;
            break;
        }
        else if (z->price < x->price)
        {
            x = x->left;
        }
        else if (z->price > x->price)
        {
            x = x->right;
        }
    }
    if (found)
        return x;
    else
        return nullptr;
}

// finds the successor of the given node as input.
TreeNode *BST::successor(TreeNode *n)
{
    TreeNode *x = n->right;
    TreeNode *min = nullptr;
    while (x != nullptr)
    {
        min = x;
        x = root->left;
    }

    if (n->right != nullptr)
        return min;

    TreeNode *y = n->parent;
    while (y != nullptr && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
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
  TreeNode *y = nullptr;
    TreeNode *x = nullptr;
    TreeNode *z = find_node(JourneyCode, price);
    if (z != nullptr)
    {
        if (root == nullptr)
            return false;
        else
        {
            if (z->left == nullptr || z->right == nullptr)
                y = z;
            else
                y = successor(z);

            if (y->left != nullptr)
                x = y->left;
            else
                x = y->right;

            if (x != nullptr)
                x->parent = y->parent;

            if (y->parent == nullptr)
                root = x;
            else if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;

            if (y != z)
            {
                z->JourneyCode = y->JourneyCode;
                z->price = y->price;
            }
            return true;
        }
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


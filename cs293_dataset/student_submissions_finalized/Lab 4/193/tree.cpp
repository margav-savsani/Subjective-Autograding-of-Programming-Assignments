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

  if (parentOfCurrNode->JourneyCode > JourneyCode)
  {
    currNode = new TreeNode(JourneyCode, price, NULL, NULL, parentOfCurrNode);
    parentOfCurrNode->left = currNode;
  }
  else
  {
    currNode = new TreeNode(JourneyCode, price, NULL, NULL, parentOfCurrNode);
    parentOfCurrNode->right = currNode;
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
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  TreeNode *x = root; // STARTING FROM ROOT NODE
  while (x != NULL && ((x->JourneyCode != JourneyCode)))
  {
    // SEARCH TILL THE EXACT STATION IS FOUND
    // OR WE REACH A NULL.
    if (JourneyCode < (x->JourneyCode))
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  if (x == NULL)
  { // IF NO SUCH NODE
    return false;
  }
  else
  { // TRUE IF NODE IS FOUND.
    return true;
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
  TreeNode *x = this->root; // STARTING FROM ROOT NODE
    while (x != NULL && ((x->JourneyCode != JourneyCode) || (x->JourneyCode != JourneyCode)))
    {
        // SEARCH TILL THE EXACT STATION IS FOUND
        // OR WE REACH A NULL.
        if (JourneyCode < (x->JourneyCode))
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    } // Finally x would be the element returned from our search
    if (x == NULL)
    { // IF NO SUCH NODE
        return false;
    }
    else
    { // TRUE IF NODE IS FOUND.
        TreeNode *y = new TreeNode;
        TreeNode *z = new TreeNode;
        if (x->left == NULL || x->right == NULL)
        {
            // If there is no left or right child of x
            // That means atmost one child for x.
            y = x; // y is the node to be deleted.
        }
        else
        {
            y = successor(x); // IF not then x has two child and we assign y as the successor of x.
        }
        if (y->left != NULL)
        { // If no left child of y then assign z as the left child of y.
            z = y->left;
        }
        else
        {
            z = y->right; // otherwise z is the right child
        }
        if (z != NULL)
        {
            z->parent = y->parent;
        }
        if (y->parent == NULL)
        {
            this->root = z; // if y is the root
        }
        else if (y == y->parent->left)
        {
            y->parent->left = z;
        }
        else
        {
            y->parent->right = z;
        }
        if (y != x)
        {
            x->JourneyCode = y->JourneyCode;
            x->JourneyCode = y->JourneyCode; // Copying all the content
        }
        return true;
    }
    return false;
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

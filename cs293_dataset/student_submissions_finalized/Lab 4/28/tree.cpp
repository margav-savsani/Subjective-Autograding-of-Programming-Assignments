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
      return false;
    TreeNode *x = root;

    while ((x != NULL) && ((x->JourneyCode != JourneyCode) || (x->price != price)))
    {
      if (x->JourneyCode > JourneyCode)
        x = x->left;
      else
        x = x->right;
    }
    return (x != NULL);

    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // You can look at the implementation of insert to code this part up.

    // return false;
  }

  TreeNode *findadd(int JourneyCode, int price)
  {
    TreeNode *x = root;
    while ((x != NULL) && ((x->JourneyCode != JourneyCode) || (x->price != price)))
    {
      if (x->JourneyCode > JourneyCode)
        x = x->left;
      else
        x = x->right;
    }
    return (x);
  }

  // Returns false, if JourneyCode isn't present
  // Deletes the corresponding entry and returns True otherwise
  bool BST::remove(int JourneyCode, int price)
  {

    TreeNode *z = findadd(JourneyCode, price);
    if (z == nullptr)
    {
      return false;
    }
    if (z == root)
    {
      if (z->left == nullptr && z->right == nullptr)
      {
        root = nullptr;
        return true;
      }
      else if (z->left != nullptr && z->right == nullptr)
      {
        root = z->left;
        return true;
      }
      else if (z->left == nullptr && z->right != nullptr)
      {
        root = z->right;
        return true;
      }
    }
    if (z->left == nullptr && z->right == nullptr)
    {
      TreeNode *y = z->parent;
      if (y->left == z)
      {
        y->left = nullptr;
      }
      else
        y->right = nullptr;
      return true;
    }
    else if (z->left == nullptr)
    {
      TreeNode *y = z->parent;
      if (y->left == z)
      {
        TreeNode *x = z->right;
        x->parent = y;
        y->left = x;
      }
      else
      {
        TreeNode *x = z->right;
        x->parent = y;
        y->right = x;
      }
      return true;
    }
    else if (z->right == nullptr)
    {
      TreeNode *y = z->parent;
      if (y->left == z)
      {
        TreeNode *x = z->left;
        x->parent = y;
        y->left = x;
      }
      else
      {
        TreeNode *x = z->left;
        x->parent = y;
        y->right = x;
      }
      return true;
    }
    else
    {
      TreeNode *y = successor(z);
      remove(y->JourneyCode, y->price);
      z->JourneyCode = y->JourneyCode;
      z->price = y->price;
      return true;
    }
  }

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

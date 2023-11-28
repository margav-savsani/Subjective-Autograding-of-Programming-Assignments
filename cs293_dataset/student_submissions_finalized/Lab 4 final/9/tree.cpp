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
  else if (root->getImbalance() > 0)
    return root->getImbalance();
  else
    return -root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.

  TreeNode *start = root;
  TreeNode *previous = NULL;

  if (!start)
  {
    root = new TreeNode(JourneyCode, price);
    return 1;
  }
  if (start->JourneyCode == JourneyCode)
  {
    return 0;
  }

  while (start)
  {
    previous = start;
    if (start->JourneyCode > JourneyCode)
    {
      start = start->left;
      root->longestPathLength++;
    }
    else
    {
      start = start->right;
      root->shortestPathLength++;
    }
  }

  if (JourneyCode < previous->JourneyCode)
  {
    TreeNode *newnode = new TreeNode(JourneyCode, price);
    previous->left = newnode;
    previous->left->parent = previous;
  }
  else
  {
    TreeNode *newnode = new TreeNode(JourneyCode, price);
    previous->right = newnode;
    previous->right->parent = previous;
  }
  return 1;
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
  TreeNode *node = root;
  if (!node)
  {
    return 0;
  }
  if ((price == node->price) and (JourneyCode == node->JourneyCode))
  {
    return 1;
  }
  if (JourneyCode < node->JourneyCode)
  {
    return (BST(node->left).find(JourneyCode, price));
  }
  else
  {
    return (BST(node->right).find(JourneyCode, price));
  }
  return 1;
  // You can look at the implementation of insert to code this part up.

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

  if (find(JourneyCode, price) == 0)
  {
    return 0;
  }
  TreeNode *node = root;

  if (JourneyCode < node->JourneyCode)
  {
    BST(node->left).remove(JourneyCode, price);
  }
  else if (price > root->price)
    BST(node->right).remove(JourneyCode, price);

  else
  {
    // node has no child
    if (!node->left and !node->right)
    {
      if (!node->parent)
      {
        node = NULL;
        return 1;
      }
      if (node->parent->JourneyCode > node->JourneyCode)
      {
        node->parent->left = NULL;
      }
      else
      {
        node->parent->right = NULL;
      }
      node = NULL;
    }

    // node with only one child
    else if (!node->left)
    {
      struct TreeNode *temp = node->right;
      temp->parent = node->parent;
      if (!node->parent)
      {
        node = temp;
        node->parent = NULL;
        return 1;
      }
      else if (node->parent->JourneyCode > node->JourneyCode)
      {
        node->parent->left = temp;
      }
      else
      {
        node->parent->right = temp;
      }
    }
    else if (!node->right)
    {
      struct TreeNode *temp = root->left;
      if (!node->parent)
      {
        node = temp;
        return 1;
      }
      else if (node->parent->JourneyCode > node->JourneyCode)
      {
        node->parent->left = temp;
      }
      else
      {
        node->parent->right = temp;
      }
    }

    // node with two children
    else
    {
      struct TreeNode *temp = root->right;
      while (temp->left)
      {
        temp = temp->left;
      }
      if (node->parent->JourneyCode > node->JourneyCode)
      {
        node->parent->left = temp;
      }
      else
      {
        node->parent->right = temp;
      }
      temp->right = root->right;
      temp->left = root->left;
      if (temp->parent->JourneyCode > temp->JourneyCode)
      {
        temp->parent->left = NULL;
      }
      else
      {
        temp->parent->right = NULL;
      }
      temp->parent = root->parent;
    }
  }
  return 1;
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

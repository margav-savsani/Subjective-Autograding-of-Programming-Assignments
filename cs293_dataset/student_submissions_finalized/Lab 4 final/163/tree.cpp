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
  TreeNode *element = new TreeNode(JourneyCode, price);
  TreeNode *prev = nullptr;
  TreeNode *temp = root;
  while (temp != nullptr)
  {
    if (temp->JourneyCode == JourneyCode)
      return false;
    prev = temp;
    if (temp->JourneyCode >= JourneyCode)
    {
      temp = temp->left;
    }
    else
    {
      temp = temp->right;
    }
  }
  if (prev == nullptr)
    temp = root = element;
  else if (prev->JourneyCode >= JourneyCode)
  {
    element->parent = prev;
    prev->left = element;
    temp = element;
  }
  else
  {
    element->parent = prev;
    prev->right = element;
    temp = element;
  }
  int path = 0;
  while (temp != root)
  {
    temp = temp->parent;
    path++;
    if (temp->shortestPathLength > path)
      temp->shortestPathLength = path;
    if (temp->longestPathLength < path)
      temp->longestPathLength = path;
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

  if (root == nullptr)
    return false;
  else if (root->price == price && root->JourneyCode == JourneyCode)
    return true;
  else if (root->price >= price)
  {
    if (root->left == nullptr)
      return false;
    BST leftTree(root->left);
    return leftTree.find(JourneyCode, price);
  }
  else
  {
    if (root->right == nullptr)
      return false;
    BST rightTree(root->right);
    return rightTree.find(JourneyCode, price);
  }
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
  if (root == nullptr)
    return false;
  else if (root->price == price && root->JourneyCode == JourneyCode)
  {
    if (root->left == nullptr && root->right == nullptr)
    {
      if (root->parent != nullptr)
      {
        if (root->parent->right == root)
          root->parent->right = nullptr;
        else
          root->parent->left = nullptr;
      }
      root = nullptr;
      return true;
    }
    else if (root->left == nullptr)
    {
      if (root->parent == nullptr)
      {
        root->right->parent = nullptr;
        root = root->right;
        return true;
      }
      root->right->parent = root->parent;
      if (root->parent->right == root)
        root->parent->right = root->right;
      else
        root->parent->left = root->right;
      root = root->right;
      return true;
    }
    else if (root->right == nullptr)
    {
      if (root->parent == nullptr)
      {
        root->left->parent = nullptr;
        root = root->left;
        return true;
      }
      root->left->parent = root->parent;
      if (root->parent->right == root)
        root->parent->right = root->left;
      else
        root->parent->left = root->left;
      root = root->left;
      return true;
    }
    else
    {
      TreeNode *element = root->left;
      while (element->right != nullptr)
        element = element->right;
      root->JourneyCode = element->JourneyCode;
      root->price = element->price;
      if (element->parent->left == element)
      {
        element->parent->left = element->left;
        if (element->left != nullptr)
          element->left->parent = element->parent;
      }
      else
      {
        element->parent->right = element->left;
        if (element->left != nullptr)
          element->left->parent = element->parent;
      }
    }
    return true;
  }
  else if (root->price >= price)
  {
    if (root->left == nullptr)
      return false;
    BST leftTree(root->left);
    return leftTree.remove(JourneyCode, price);
  }
  else
  {
    if (root->right == nullptr)
      return false;
    BST rightTree(root->right);
    return rightTree.remove(JourneyCode, price);
  }

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

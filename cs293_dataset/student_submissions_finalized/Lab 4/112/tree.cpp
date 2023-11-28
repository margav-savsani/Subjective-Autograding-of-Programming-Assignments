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
  return myInsert(JourneyCode, price, root);
}

bool BST::myInsert(int JourneyCode, int price, TreeNode *insertInMe)
{
  if (insertInMe == nullptr)
  {
    root = new TreeNode(JourneyCode, price);
    return true;
  }
  if (insertInMe->JourneyCode == JourneyCode)
  {
    return false;
  }
  if (JourneyCode < insertInMe->JourneyCode)
  {
    if (journeyExists(insertInMe->right, JourneyCode))
    {
      return false;
    }
    if (insertInMe->left == nullptr)
    {
      insertInMe->left = new TreeNode(JourneyCode, price);
      insertInMe->left->parent = insertInMe;
      // Need to modify the shortest and longest path lengths of all nodes in the path
      return true;
    }
    return myInsert(JourneyCode, price, insertInMe->left);
  }
  else
  {
    if (journeyExists(insertInMe->left, JourneyCode))
    {
      return false;
    }
    if (insertInMe->right == nullptr)
    {
      insertInMe->right = new TreeNode(JourneyCode, price);
      insertInMe->right->parent = insertInMe;
      // Need to modify the shortest and longest path lengths of all nodes in the path
      return true;
    }
    return myInsert(JourneyCode, price, insertInMe->right);
  }
}

bool BST::journeyExists(TreeNode *searchMe, int JourneyCode)
{
  if (searchMe == nullptr)
  {
    return false;
  }
  if (searchMe->JourneyCode == JourneyCode)
  {
    return true;
  }
  if (JourneyCode < searchMe->JourneyCode)
  {
    return journeyExists(searchMe->left, JourneyCode);
  }
  else
  {
    return journeyExists(searchMe->right, JourneyCode);
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

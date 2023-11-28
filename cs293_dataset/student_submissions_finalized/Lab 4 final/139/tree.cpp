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
  {
    InsertAllPaths();
    longestPathLength = *max_element(Paths.begin(), Paths.end());
    shortestPathLength = *min_element(Paths.begin(), Paths.end());
    return longestPathLength - shortestPathLength;
  }
}

int BST::Lenght(TreeNode *leaf)
{
  int lenght = 0;
  while (leaf != this->root)
  {
    lenght++;
    leaf = leaf->parent;
  }
  return lenght;
}

void BST::InsertAllPaths()
{
  Paths.clear();
  InsertAllLeafLengths(this->root);
}
void BST::InsertAllLeafLengths(TreeNode *node)
{
  if (node == nullptr)
    return;
  if (node->left == nullptr && node->right == nullptr)
  {
    Paths.push_back(Lenght(node));
    return;
  }
  if (node->left != nullptr)
    InsertAllLeafLengths(node->left);
  if (node->right != nullptr)
    InsertAllLeafLengths(node->right);
}

bool BST::insert(int JourneyCode, int price)
{
  TreeNode *y = nullptr;
  TreeNode *x = this->root;
  // traversing through the tree (x as the place about to be inserted, y as parent of the x).
  while (x != nullptr)
  {
    y = x;
    if (x->JourneyCode == JourneyCode && x->price == price)
    {
      return false;
    }
    if (JourneyCode <= x->JourneyCode)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  // constructing new element:
  TreeNode *about_to_insert = new TreeNode(JourneyCode, price);
  about_to_insert->parent = y;
  // first element to be added(root even not defined, we have to insert root).
  if (y == nullptr)
  {
    this->root = about_to_insert;
  }
  // else,adding new element depending upon parent node
  else if (about_to_insert->JourneyCode <= y->JourneyCode)
  {
    y->left = about_to_insert;
  }
  else if (about_to_insert->JourneyCode > y->JourneyCode)
  {
    y->right = about_to_insert;
  }
  return true;
}
TreeNode *BST::getSuccessor(TreeNode *node)
{
  // if right subtree is non-empty: simply minimum of right subtree.
  if (node->right != nullptr)
  {
    return getMin(node->right);
  }
  // else, we have to traverse back and find the next most maximum than node.
  TreeNode *successor = node->parent;
  // traversing upwards:
  while (successor != nullptr && node == successor->right)
  {
    node = successor;
    successor = successor->parent;
  }
  // returns successor if found, else returns nullptr;
  return successor;
}
TreeNode *BST::getMin(TreeNode *root)
{
  while (root->left != nullptr)
  {
    root = root->left;
  }
  return root;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  TreeNode *node = this->root;
  // traversing through the tree
  while (node != nullptr)
  {
    if (JourneyCode == node->JourneyCode && price == node->price)
      return true;
    else
    {
      if (JourneyCode <= node->JourneyCode)
        node = node->left;
      else
        node = node->right;
    }
  }
  return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  TreeNode *node = this->root;
  // traversing through the tree
  while (node != nullptr)
  {
    if (JourneyCode == node->JourneyCode && price == node->price)
    {
      // deletion of the corresponding element from the tree:

      // 1.element had no children
      if (node->left == nullptr && node->right == nullptr)
      {
        if (node->parent->left == node)
        {
          node->parent->left = nullptr;
        }
        else
        {
          node->parent->right = nullptr;
        }
        node = nullptr;
        return true;
      }

      // 2.element had one children
      else if (node->left == nullptr)
      {
        if (node->parent->left == node)
        {
          node->parent->left = node->right;
        }
        else
        {
          node->parent->right = node->right;
        }
        node->right->parent = node->parent;
        node = nullptr;
        return true;
      }
      else if (node->right == nullptr)
      {
        if (node->parent->right == node)
        {
          node->parent->right = node->left;
        }
        else
        {
          node->parent->left = node->left;
        }
        node->left->parent = node->parent;
        node = nullptr;
        return true;
      }

      // 3.element had two children
      else
      {

        TreeNode *node_successor = getSuccessor(node);
        node->JourneyCode = node_successor->JourneyCode;
        node->price = node_successor->price;
        if (node_successor->parent == node)
        {
          if (node_successor->right != nullptr)
          {
            node_successor->right->parent = node;
            node->right = node_successor->right;
          }
          else
            node->right = nullptr;
          node_successor = nullptr;

          return true;
        }
        if (node_successor->parent->right == node_successor)
        {
          node_successor->parent->right = nullptr;
        }
        else
          node_successor->parent->left = nullptr;
        if (node_successor->right != nullptr)
        {
          node_successor->right->parent = node_successor->parent;
          node_successor->parent->left = node_successor->right;
        }
        node_successor = nullptr;
        return true;
      }
    }
    else
    {
      if (JourneyCode <= node->JourneyCode)
      {
        node = node->left;
      }
      else
      {
        node = node->right;
      }
    }
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

// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <stdlib.h>
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

int BST::get_lpath(int l)
{
  if (root == NULL)
  {
    return 0;
  }
  else if (root->left == NULL && root->right != NULL)
  {
    l++;
    BST rightsubtree(root->right);
    return rightsubtree.get_lpath(l);
  }
  else if (root->left != NULL && root->right == NULL)
  {
    l++;
    BST leftsubtree(root->right);
    return leftsubtree.get_lpath(l);
  }
  else if (root->left != NULL && root->right != NULL)
  {
    l++;
    BST rightsubtree(root->right);
    BST leftsubtree(root->right);
    leftsubtree.get_lpath(l);
    rightsubtree.get_lpath(l);
    if (leftsubtree.get_lpath(l) >= rightsubtree.get_lpath(l))
    {
      return leftsubtree.get_lpath(l);
    }
    else
    {
      return rightsubtree.get_lpath(l);
    }
  }
  else if (root->left == NULL && root->right == NULL)
  {
    return l;
  }
  return -1;
}

int BST::get_spath(int s)
{
  if (root == NULL)
  {
    return 0;
  }
  if (root->left == NULL && root->right == NULL)
  {
    return s;
  }
  else
  {
    s++;
    BST rightsubtree(root->right);
    BST leftsubtree(root->right);
    leftsubtree.get_spath(s);
    rightsubtree.get_spath(s);
    if (leftsubtree.get_lpath(s) <= rightsubtree.get_lpath(s))
    {
      return leftsubtree.get_spath(s);
    }
    else
    {
      return rightsubtree.get_spath(s);
    }
  }
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
    currNode->JourneyCode = JourneyCode;
    currNode->price = price;
    int s = 0;
    int l = 0;
    currNode->shortestPathLength = get_spath(s);
    currNode->longestPathLength = get_lpath(l);
    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
  }
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
  if (root == NULL)
    return false;
  if (root->price == price && root->JourneyCode == JourneyCode)
  {
    return true;
  }
  else if (JourneyCode > root->JourneyCode)
  {
    BST rightsubTree(root->right);
    return rightsubTree.find(JourneyCode, price);
  }
  else if (JourneyCode < root->JourneyCode)
  {
    BST rightsubTree(root->right);
    return rightsubTree.find(JourneyCode, price);
  }
  else
  {
    return false;
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
  if (root == NULL)
  {
    return false;
  }
  else if (root->JourneyCode == JourneyCode && root->price == price)
  {
    if (root->right == NULL && root->left == NULL)
    {
      root = NULL;
      return true;
    }
    else if (root->left != NULL && root->right == NULL)
    {
      root->left->parent = root->parent;
      if (root->parent != NULL)
      {
        if (root->parent->left == root)
        {
          root->parent->left = root->left;
        }
        else
        {
          root->parent->right = root->left;
        }
      }
      return true;
    }
    else if (root->left == NULL && root->right != NULL)
    {
      root->right->parent = root->parent;
      if (root->parent != NULL)
      {
        if (root->parent->right == root)
        {
          root->parent->right = root->right;
        }
        else
        {
          root->parent->left = root->right;
        }
      }
      return true;
    }
    else
    {
      TreeNode *C = root->right;
      while (C->left != NULL)
      {
        C = C->left;
      }
      C->parent->left = C->right;
      if (C->right != NULL)
      {
        C->right->parent = C->parent;
      }
      root->JourneyCode = C->JourneyCode;
      root->price = C->price;
      return true;
    }
  }
  else if (JourneyCode >= root->JourneyCode)
  {
    BST *rightsubTree = new BST(root->right);
    return rightsubTree->remove(JourneyCode, price);
  }
  else
  {
    BST *leftsubTree = new BST(root->left);
    return leftsubTree->remove(JourneyCode, price);
  }
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
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

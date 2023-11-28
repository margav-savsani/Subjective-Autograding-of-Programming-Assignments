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

  if (currNode == NULL)
  {
    currNode = new TreeNode(JourneyCode, price);
    return 1;
  }

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
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // You can look at the implementation of insert to code this part up.
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
    else if (JourneyCode > root->JourneyCode)
    {
      BST(node->right).remove(JourneyCode, price);
    }
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
        if (node->parent->price > node->price)
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
        if (!node->parent)
        {
          node = temp;
          return 1;
        }
        else if (node->parent->price > node->price)
        {
          node->parent->left = temp;
        }
        else
        {
          node->parent->right = temp;
        }
        free(root);
        node = temp;
      }
      else if (!node->right)
      {
        struct TreeNode *temp = root->left;
        if (!node->parent)
        {
          node = temp;
          return 1;
        }
        else if (node->parent->price > node->price)
        {
          node->parent->left = temp;
        }
        else
        {
          node->parent->right = temp;
        }
        free(root);
        node = temp;
      }

      // node with two children
      else
      {
        struct TreeNode *temp = root->right;
        while (temp->left)
        {
          temp = temp->left;
        }
        if (node->parent->price > node->price)
        {
          node->parent->left = temp;
        }
        else
        {
          node->parent->right = temp;
        }
        temp->right = root->right;
        temp->left = root->left;
        if (temp->parent->price > temp->price)
        {
          temp->parent->left = NULL;
        }
        else
        {
          temp->parent->right = NULL;
        }
        temp->parent = root->parent;
        free(root);
        node = temp;
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

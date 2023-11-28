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

  // struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;

  // while (currNode != nullptr) {
  //   if (currNode->JourneyCode < JourneyCode) {
  //     parentOfCurrNode = currNode;
  //     currNode = currNode->right;
  //   }
  //   else if (currNode->JourneyCode > JourneyCode) {
  //     parentOfCurrNode = currNode;
  //     currNode = currNode->left;
  //   }
  //   else { // currNode->JourneyCode == JourneyCode
  //     return false;
  //   }

  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting

  // return true;
  // Checking firstly if element is already present or not
  if (find(JourneyCode, price))
  {
    return false;
  }

  // Now we know that it surely isn't present
  // Firstly finding the location where we need it to be there, and then adding(inserting at that location)
  TreeNode *finder, *parent = NULL;
  finder = root;
  while (finder != NULL)
  {
    parent = finder;
    if (finder->price >= price)
    {
      finder = finder->left;
    }
    else if (finder->price < price)
    {
      finder = finder->right;
    }
  }

  // Handling the case of same price but different journey code too, by putting that in the left tree
  TreeNode *element = new TreeNode(JourneyCode, price);
  if (parent != NULL)
  {
    element->parent = parent;
    if (parent->price >= price)
    {
      parent->left = element;
    }
    else
    {
      parent->right = element;
    }
  }
  else
  {
    root = element;
    element->parent = NULL;
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

  // return false;

  // finder is my pointer which iterates the tree to find the element to be searched for
  TreeNode *finder;
  finder = root;
  while (finder != NULL)
  {
    if (finder->price == price)
    {
      if (finder->JourneyCode == JourneyCode)
      {
        return true;
      }
      else
      {
        finder = finder->left;
      }
    }
    else if (finder->price > price)
    {
      finder = finder->left;
    }
    else if (finder->price < price)
    {
      finder = finder->right;
    }
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

  // return false;

  // Firstly checking if given pair exist in the tree or not, if not return false
  if (!find(JourneyCode, price))
  {
    return false;
  }

  // Else first finding the pointer to the pair that is to be deleted
  TreeNode *finder;
  finder = root;
  while (true)
  {
    if (finder->price == price)
    {
      if (finder->JourneyCode == JourneyCode)
      {
        break;
      }
      else
      {
        finder = finder->left;
      }
    }
    else if (finder->price > price)
    {
      finder = finder->left;
    }
    else if (finder->price < price)
    {
      finder = finder->right;
    }
  }

  // Now we know that finder is pointing to the node we need to delete
  // Have to implement the different cases of deletion

  // Leaf node
  if (finder->left == NULL && finder->right == NULL)
  {
    // Just making sure that parent is not null, before accessing parent pointer
    if ((finder->parent) != NULL)
    {
      if ((finder->parent)->right == finder)
      {
        (finder->parent)->right = NULL;
      }
      else
      {
        (finder->parent)->left = NULL;
      }
    }
    else
    {
      root = NULL;
    }
    // USED TO SAVE SPACE
    // delete finder;
    return true;
  }

  // Having one child
  else if (finder->left != NULL && finder->right == NULL)
  {
    // Just making sure that parent is not null, before accessing parent pointer
    if ((finder->parent) != NULL)
    {
      if ((finder->parent)->right == finder)
      {
        (finder->parent)->right = finder->left;
        (finder->left)->parent = finder->parent;
      }
      else
      {
        (finder->parent)->left = finder->left;
        (finder->left)->parent = finder->parent;
      }
    }
    // Making sure above that all the pointer reference changes are being done properly, that is parents are pointed correctly \
        parents childs are handled properly etc.
    else
    {
      root = finder->left;
      (finder->left)->parent = NULL;
    }
    // USED TO SAVE SPACE
    // delete finder;
    return true;
  }
  else if (finder->left == NULL && finder->right != NULL)
  {
    // similar case to above else if
    if ((finder->parent) != NULL)
    {
      if ((finder->parent)->right == finder)
      {
        (finder->parent)->right = finder->right;
        (finder->right)->parent = finder->parent;
      }
      else
      {
        (finder->parent)->left = finder->right;
        (finder->right)->parent = finder->parent;
      }
    }
    else
    {
      root = finder->right;
      (finder->right)->parent = NULL;
    }
    // USED TO SAVE SPACE
    // delete finder;
    return true;
  }

  // Having two children
  // using predecessor method
  else
  {
    TreeNode *pred;
    // Here predecessor is forsure the right most element in the left sub-tree, NOTE can be equal to price value of deleted one
    pred = finder->left;
    // cout << "fnder" << finder->JourneyCode << endl;
    // cout << "pred" << pred->JourneyCode << endl;
    while (pred->right != NULL)
    {
      pred = pred->right;
    }
    // cout << "pred" << pred->JourneyCode << endl;
    // Since our pred would be no more after deletion, lets store its inner values in new node
    int jc = pred->JourneyCode;
    int p = pred->price;
    // Need to properly delete elements, can be called recursively
    bool del = remove(jc, p); // No use of this variable, just a placeholder
    finder->JourneyCode = jc;
    finder->price = p;
  }
  return true;
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

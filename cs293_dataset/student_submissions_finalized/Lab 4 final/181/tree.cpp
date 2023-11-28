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

  TreeNode *t = new TreeNode(JourneyCode, price);
  if (root == NULL)
  {
    root = t;
    return true; // adds at root if its null
  }
  TreeNode *temp = new TreeNode();
  temp = root;
  while (temp != NULL)
  {
    if (temp->JourneyCode >= JourneyCode) // if less than root goes to left
    {
      if (temp->JourneyCode == JourneyCode)
      {
        return false; // returns false if already exists
      }
      if (temp->left == NULL)
      {
        TreeNode *t = new TreeNode(JourneyCode, price, NULL, NULL, temp); // new node if its null before
        temp->left = t;
        return true;
      }
      else
        temp = temp->left;
    }
    else if (temp->JourneyCode < JourneyCode) // if greater than root goes to right subtree
    {
      if (temp->JourneyCode == JourneyCode)
      {
        return false; // returns false if it already exists
      }
      if (temp->right == NULL)
      {
        TreeNode *t = new TreeNode(JourneyCode, price, NULL, NULL, temp);
        temp->right = t; // creating new node if the position is null
        return true;
      }
      else
      {
        temp = temp->right;
      }
    }
  }
  return false;

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
  TreeNode *temp = new TreeNode();
  temp = root;
  while (temp != NULL)
  {
    if (temp->price == price && temp->JourneyCode == JourneyCode)
    {
      return true; // if found returns true
    }
    if (temp->price >= price)
    {
      temp = temp->left; // check in left tree if price is less than root's
    }
    else
    {
      temp = temp->right; // check in right subtree if price is more than root's
    }
  }
  return false;
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  TreeNode *temp = new TreeNode();
  temp = root;

  while (temp != NULL)
  {
    if (temp->price == price && temp->JourneyCode == JourneyCode) // finding node position that needs to be removed
    {
      break;
    }
    if (temp->price >= price)
    {
      temp = temp->left;
    }
    else
    {
      temp = temp->right;
    }
  }

  if (temp == NULL)
  {
    return false; // if it not exists returns false
  }

  if (temp->left == NULL && temp->right == NULL) // leaf removal
  {
    if (temp->parent == NULL) // if root is leaf keep it back to null
    {
      root = NULL;
      return true;
    }
    if (temp->parent->right == temp) // if its a right child
    {
      temp->parent->right = NULL; // changing its parent's child to null
      return true;
    }
    else
    {
      temp->parent->left = NULL; // changing its parent's child to null
      return true;
    }
  }

  if (temp->right == NULL) // if right child is null
  {
    temp->left->parent = temp->parent; // changings its left child's parent to its parent's parent
    if (temp->parent == NULL)
    {
      root = root->left; // for root case only replace it with its left child
      return true;
    }
    if (temp == temp->parent->right) // checking if its a right child
    {
      temp->parent->right = temp->left; // changing its parents child with childs left child
    }
    else
    {
      temp->parent->left = temp->left; // changing its parents child with childs right child
    }
    return true;
  }

  if (temp->left == NULL) // if left child is null
  {
    temp->right->parent = temp->parent; // changing its right child's parent with its parent's parent's
    if (temp->parent == NULL)           // if its root
    {
      root = root->right; // replacing it with its right child
      return true;
    }
    else if (temp == temp->parent->right)
    {
      temp->parent->right = temp->right; // changing its parents child with childs left child
      return true;
    }
    else
    {
      temp->parent->left = temp->right; // changing its parents child with childs right child
    }
    return true;
  }

  TreeNode *succesor = new TreeNode(); // succesor to replace
  succesor = temp->right;              // going to right for bigger than temp values
  while (succesor->left != NULL)       // going to left from there for smallest value bigger than temp values
  {
    succesor = succesor->left;
  }
  if (succesor->parent->left == succesor)
  {
    succesor->parent->left = succesor->right; // if succesor is it's left child replace succesors with sucesor right child
  }
  if (succesor->parent->right == succesor)
  {
    succesor->parent->right = succesor->right; // if succesor is it's right child replace succesors with succesor right child
  }
  if (succesor->right != NULL)
  {
    succesor->right->parent = succesor->parent; // if succesor has a right subtree change its parent to succesor parents
  }

  if (temp->parent == NULL)
  {
    temp->JourneyCode = succesor->JourneyCode; // after deleting succesor replacing it with its succesor
    temp->price = succesor->price;             // after deleting succesor replacing it with its succesor
    return true;
  }
  else
  {
    if (temp->parent->left == temp)
    {
      temp->JourneyCode = succesor->JourneyCode; // after deleting succesor replacing it with its succesor
      temp->price = succesor->price;             // after deleting succesor replacing it with its succesor
    }

    else if (temp->parent->right == temp)
    {
      temp->JourneyCode = succesor->JourneyCode; // after deleting succesor replacing it with its succesor
      temp->price = succesor->price;             // after deleting succesor replacing it with its succesor
    }
  }

  return true;
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

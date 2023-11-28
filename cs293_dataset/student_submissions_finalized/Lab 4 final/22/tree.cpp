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
  //   // Do not forget to update shortestPathLength and
  //   // longestPathLength of (possibly all) BST nodes in the
  //   // path from the root to the new node you are inserting

  if (root->JourneyCode == JourneyCode)
    return false;

  if (root->JourneyCode==0) // When we initialize a BST using BST(), the JourneyCode of root node is 0. This makes sure that root is inserted before moving ahead.
  {
    root->JourneyCode = JourneyCode;
    root->price = price;
    root->longestPathLength = 0;
    root->shortestPathLength = 0;
    return true;
  }

  if (JourneyCode >= root->JourneyCode)
  {
    if (root->right == nullptr) // When the right child of root doesn't exist, we create a new one and join them.
    {
      TreeNode *right = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
      (*root).right = right;

      if(root->left == nullptr) root->shortestPathLength = 0; //Since the node doesn't have a left child, that is the shortest path to a leaf node.
      else root->shortestPathLength = std::min(root->left->shortestPathLength, root->right->shortestPathLength) + 1;//As we go up the treewhile exiting recursion, we update the shortestPathLength of each node we encounter. It is the minimum of ShortestPathLength of both its child +1

      //As we go up the tree while exiting recursion, we update the longestPathLength of each node we encounter. It is the maximum of longestPathLength of both its child +1
      if(root->left==nullptr) root->longestPathLength = root->right->longestPathLength + 1;
      else root->longestPathLength = std::max(root->left->longestPathLength, root->right->longestPathLength) + 1;

      return true;
    }
    else
    {
      TreeNode *curr = root;                      // stores the value of our root
      root = root->right;                         // changes root to root->right. This makes our RST the BST
      bool val = BST::insert(JourneyCode, price); // recurses until the upper condition is reached.
      root = curr;                                // This changes our BST from RST to BST.

      if(root->left == nullptr) root->shortestPathLength = 0;//Since the node doesn't have a left child, that is the shortest path to a leaf node.

      //As we go up the treewhile exiting recursion, we update the shortestPathLength of each node we encounter. It is the minimum of ShortestPathLength of both its child +1
      else root->shortestPathLength = std::min(root->left->shortestPathLength, root->right->shortestPathLength) + 1;

      //As we go up the tree while exiting recursion, we update the longestPathLength of each node we encounter. It is the maximum of longestPathLength of both its child +1

      if(root->left==nullptr) root->longestPathLength = root->right->longestPathLength + 1;
      else root->longestPathLength = std::max(root->left->longestPathLength, root->right->longestPathLength) + 1;

      return val;
    }
  }

  else
  {
    if (root->left == nullptr) // When the left child of root doesn't exist, we create a new one and join them.
    {
      TreeNode *left = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
      root->left = left;

      if(root->right == nullptr) root->shortestPathLength = 0;
      else root->shortestPathLength = std::min(root->left->shortestPathLength, root->right->shortestPathLength) + 1;

      if(root->right==nullptr) root->longestPathLength = root->left->longestPathLength + 1;
      else root->longestPathLength = std::max(root->left->longestPathLength, root->right->longestPathLength) + 1;

      return true;
    }
    else
    {
      TreeNode *curr = root;                      // stores the value of our root
      root = root->left;                          // changes root to root->left. This makes our LST the BST
      bool val = BST::insert(JourneyCode, price); // recurses until the upper condition is reached.
      root = curr;                                // This changes our BST from LST to BST.

      if(root->right == nullptr) root->shortestPathLength = 0;
      else root->shortestPathLength = std::min(root->left->shortestPathLength, root->right->shortestPathLength) + 1;

      if(root->right==nullptr) root->longestPathLength = root->left->longestPathLength + 1;
      else root->longestPathLength = std::max(root->left->longestPathLength, root->right->longestPathLength) + 1;

      return val;
    }
  }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  if (root->JourneyCode == JourneyCode && root->price == price)
    return true; // Base Condition

  if (JourneyCode >= root->JourneyCode)
  {
    if (root->right == nullptr)
      return false; // Base condition. We reach the leaf node without finding the required node. i.e., the joureyCode and price pair doesn't exist.
    else
    {
      TreeNode *curr = root;                    // stores value of current root
      root = root->right;                       // Changes root to point to right child to recurse in RST
      bool val = BST::find(JourneyCode, price); // recurses until a Base condition is satisfied.
      root = curr;                              // We come back to our original BST
      return val;
    }
  }

  else
  {
    if (root->left == nullptr)
      return false; // Base condition. We reach the leaf node without finding the required node. i.e., the joureyCode and price pair doesn't exist.
    else
    {
      TreeNode *curr = root;                    // stores value of current root
      root = root->left;                        // Changes root to point to left child to recurse in LST
      bool val = BST::find(JourneyCode, price); // recurses until a Base condition is satisfied.
      root = curr;                              // We come back to our original BST
      return val;
    }
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

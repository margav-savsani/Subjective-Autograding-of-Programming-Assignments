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
  //cout<<"Insert function"<<endl;
  TreeNode *father = nullptr;
  TreeNode *son = root;
  // IMPORTANT- We have to create a new node(dynamic) each and every time to get a different address. If we donot add new, then the node created gets the same address as of root. To overcome this, always create a new node.
  TreeNode *node = new TreeNode(JourneyCode, price);

  while (son != nullptr)
  {
    father = son;

    if ((son->JourneyCode == node->JourneyCode) && (son->price == node->price))
    {
      return false;
    }
    if (node->JourneyCode <= father->JourneyCode)
    {
      son = father->left;
    }
    else
    {
      son = father->right;
    }
  }

  node->parent = father;
  if (father == nullptr)
  {
    root = node;
  }
  else if (node->JourneyCode <= father->JourneyCode)
  {
    father->left = node;
  }
  else
  {
    father->right = node;
  }
  updateShortestPath(root);
  updateLongestPath(root);
  //cout<<"Exit Function"<<endl;
  return true;

  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
}
int BST::updateShortestPath(TreeNode *node)
{

  
  if (node->left == nullptr || node->right == nullptr)
  {
    node->shortestPathLength=1;
    return 1;
  }
  else
  {
    int path1, path2;
    path1 = 1 + updateShortestPath(node->left);
    path2 = 1 + updateShortestPath(node->right);
    if (path1 > path2)
    {
      node->shortestPathLength = path2;
      //cout<<"ShortestPath"<<node->shortestPathLength<<endl;
      return path2;
    }
    else
    {
      node->shortestPathLength = path1;
      //cout<<"ShortestPath"<<node->shortestPathLength<<endl;
      
      return path1;
    }
  }
}
int BST::updateLongestPath(TreeNode *node)
{

  if (node->left == nullptr && node->right == nullptr)
  {
    node->longestPathLength=1;
    return 1;
  }
  else if (node->left == nullptr)
  {
    node->longestPathLength = 1 + updateLongestPath(node->right);
    //cout<<"LongestPath"<<node->longestPathLength<<endl;
    return 1 + updateLongestPath(node->right);
  }
  else if (node->right == nullptr)
  {
    node->longestPathLength = 1 + updateLongestPath(node->left);
    //cout<<"LongestPath"<<node->longestPathLength<<endl;
    return 1 + updateLongestPath(node->left);
  }
  else
  {
    int path1, path2;
    path1 = 1 + updateLongestPath(node->left);
    path2 = 1 + updateLongestPath(node->right);
    if (path1 > path2)
    {
      node->longestPathLength = path1;
      //cout<<"LongestPath"<<node->longestPathLength<<endl;
      return path1;
    }
    else
    {
      node->longestPathLength = path2;
      //cout<<"LongestPath"<<node->longestPathLength<<endl;
      return path2;
    }
  }
}

// Return True, if the ticket with given attributes is found, false otherwise
TreeNode *BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  TreeNode *node = new TreeNode(JourneyCode, price);
  TreeNode *start;
  start = root;
  while (start != NULL)
  {
    // //cout<<"getNode"<<endl;
    if (start->JourneyCode == node->JourneyCode && start->price == node->price)
    {
      // //cout<<"if"<<endl;
      // //cout<<start->JourneyCode<<" "<<start->price<<endl;
      return start;
    }
    else if (node->JourneyCode <= start->JourneyCode)
    {
      start = start->left;
    }
    else
    {
      start = start->right;
    }
  }
  return nullptr;
}

TreeNode *BST::getSuccessor(TreeNode *node)
{
  TreeNode *start = node;
  TreeNode *pstart = start->parent;
  // //cout<<"Succ"<<endl;
  if (start->right != nullptr)
  {
    pstart = start;
    start = start->right;
    while (start->left != nullptr)
    {
      pstart = start;
      start = start->left;
      return start;
    }
    // //cout<<"enter1"<<endl;
  }
  else
  {
    pstart = start->parent;
    while (pstart->left != start)
    {
      start = pstart;
      pstart = pstart->parent;
      return pstart;
    }
  }
  // //cout<<pstart->JourneyCode<<" "<<pstart->price<<endl;
  // return start;
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
  TreeNode *node = find(JourneyCode, price);
  ////cout << node->JourneyCode << " " << node->price << endl;
  TreeNode *x;
  TreeNode *y;
  if (node == nullptr)
  {
    return false;
  }
  else
  {
    if (node->left == nullptr || node->right == nullptr)
    {
      y = node;
    }
    else
    {
      y = getSuccessor(node);
    }
    if (y->left != nullptr)
    {
      x = y->left;
    }
    else
      x = y->right;
    if (x != nullptr)
    {
      x->parent = y->parent;
    }
    if (y->parent == nullptr)
    {
      root = x;
    }
    else if (y = y->parent->left)
    {
      y->parent->left = x;
    }
    else
    {
      y->parent->right = x;
    }
    if (y != node)
    {
      node->JourneyCode = y->JourneyCode;
      node->price = y->price;
    }
  }
  updateLongestPath(root);
  updateShortestPath(root);

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

// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

int BST::getImbalance()
{
  if (root == nullptr)
    return 0;
  else
    return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  TreeNode *currNode = root;
  TreeNode* parentOfCurrNode = nullptr;
  if(root==NULL){
    root = new TreeNode(JourneyCode,price);
    return true;
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
    {
      return false;
    }
  }
  if (parentOfCurrNode->JourneyCode > JourneyCode)
  {
    currNode = new TreeNode(JourneyCode, price, NULL, NULL, parentOfCurrNode);
    parentOfCurrNode->left = currNode;
  }
  else
  {
    currNode = new TreeNode(JourneyCode, price, NULL, NULL, parentOfCurrNode);
    parentOfCurrNode->right = currNode;
  }
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  TreeNode *x = root; // STARTING FROM ROOT NODE
  while (x != NULL && ((x->JourneyCode != JourneyCode)))
  {
    // SEARCH TILL THE EXACT STATION IS FOUND
    // OR WE REACH A NULL.
    if (JourneyCode < (x->JourneyCode))
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  if (x == NULL)
  { // IF NO SUCH NODE
    return false;
  }
  else
  {
    return true;
  }
  return false;
}

bool BST::remove(int JourneyCode, int price)
{
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
  TreeNode *x = this->root; // STARTING FROM ROOT NODE
  while (x != NULL && (x->JourneyCode != JourneyCode))
  {
    // SEARCH TILL THE EXACT STATION IS FOUND
    // OR WE REACH A NULL.
    if (JourneyCode < (x->JourneyCode))
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  } // Finally x would be the element returned from our search
  if (x == NULL)
  { // IF NO SUCH NODE
    return false;
  }
  else
  { // TRUE IF NODE IS FOUND.
    TreeNode *y = new TreeNode;
    TreeNode *z = new TreeNode;
    if (x->left == NULL || x->right == NULL)
    {
      // If there is no left or right child of x
      // That means atmost one child for x.
      y = x; // y is the node to be deleted.
    }
    else
    {
      y = successor(x); // IF not then x has two child and we assign y as the successor of x.
    }
    if (y->left != NULL)
    { // If no left child of y then assign z as the left child of y.
      z = y->left;
    }
    else
    {
      z = y->right; // otherwise z is the right child
    }
    if (z != NULL)
    {
      z->parent = y->parent;
    }
    if (y->parent == NULL)
    {
      this->root = z; // if y is the root
    }
    else if (y == y->parent->left)
    {
      y->parent->left = z;
    }
    else
    {
      y->parent->right = z;
    }
    if (y != x) //Means y is successor of x
    {
      x->JourneyCode = y->JourneyCode;
      x->JourneyCode = y->JourneyCode; // Copying all the content
    }
    return true;
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
int TreeNode::shortestpath(TreeNode* curr){
  if(curr->left == NULL || curr->right == NULL){
      return 0;
  }
  else{
    return (1 + min(shortestpath(curr->left),shortestpath(curr->right)));
  }
}
int TreeNode::longestpath(TreeNode* curr){
  if(curr->left == NULL && curr->right == NULL){
      return 0;
  }
  else{
    if(curr->left == NULL){
      return (1 + longestpath(curr->right));
    }
    else if (curr->right == NULL){
      return (1+ longestpath(curr->left));
    }
    else{
      return (1 + max(longestpath(curr->left),longestpath(curr->right)));
    }
  }
}
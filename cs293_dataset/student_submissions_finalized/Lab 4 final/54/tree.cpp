// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "tree.h"
#include <cmath>

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
int BST::imbalance(){
  return longestdistance(root)-shortestdistance(root);
}

int BST::shortestdistance(TreeNode *x)
{
  if (x->left == NULL)
  {
    if (x->right == NULL)
    {
      return 0;
    }
    return shortestdistance(x->right) + 1;
  }
  if (x->right == NULL)
  {
    return shortestdistance(x->left) + 1;
  }
  x->shortestPathLength = min(shortestdistance(x->left), shortestdistance(x->right)) + 1;
  return x->shortestPathLength;
}

int BST::longestdistance(TreeNode *x)
{
  if (x->left == NULL)
  {
    if (x->right == NULL)
    {
      return 0;
    }
    return longestdistance(x->right) + 1;
  }
  if (x->right == NULL)
  {
    return longestdistance(x->left) + 1;
  }
  x->longestPathLength = (max(longestdistance(x->left), longestdistance(x->right)) + 1);
  return x->longestPathLength;
}

int BST::getImbalance()
{
  if (root == nullptr)
    return 0;
  else
    return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  TreeNode *A = new TreeNode;
  A->price = price;
  A->JourneyCode = JourneyCode;
  A->left = NULL;
  A->right = NULL;
  A->parent = NULL;
  A->shortestPathLength = 0;
  A->longestPathLength = 0;

  if (find(JourneyCode, price))
    return false;
  if (root == NULL)
  {
    root = A;
    shortestdistance(root);
    longestdistance(root);
    return true;
  }
  TreeNode *x = new TreeNode;
  TreeNode *y = new TreeNode;
  x = root;
  while (x != NULL)
  {
    if (price < x->JourneyCode)
    {
      if (x->left == NULL)
      {
        x->left = y;
        y->JourneyCode = JourneyCode;
        y->price = price;
        y->parent = x;
        y->left = NULL;
        y->right = NULL;
        shortestdistance(root);
        longestdistance(root);
        return true;
      }
      x = x->left;
    }
    if (price > x->JourneyCode)
    {
      if (x->right == NULL)
      {
        x->right = y;
        y->JourneyCode = JourneyCode;
        y->price = price;
        y->parent = x;
        y->left = NULL;
        y->right = NULL;
        shortestdistance(root);
        longestdistance(root);
        return true;
      }
      x = x->right;
    }
  }
  return true;
}

bool BST::find(int JourneyCode, int price)
{
  if (root == NULL) {return false;}
  TreeNode *x = new TreeNode;
  x = root;
  while (x != NULL)
  {
    if ((x->JourneyCode == JourneyCode) && (x->price == price))
    {
      return true;
    }
    if (x->JourneyCode > JourneyCode)
    {
      x = x->left;
    }
    else if (x->JourneyCode < JourneyCode)
    {
      x = x->right;
    }
  }
  return false;
}

TreeNode *BST::search(TreeNode *T, int price, int JourneyCode)
{
  while (T != NULL)
  {
    if ((T->JourneyCode == JourneyCode) && (T->price == price))
    {
      return T;
    }
    if (T->JourneyCode > JourneyCode)
    {
      return search(T->left, price, JourneyCode);
    }
    if (T->JourneyCode < JourneyCode)
    {
      return search(T->right, price, JourneyCode);
    }
  }
  return NULL;
}

TreeNode *BST::predecessor(TreeNode *T, int price)
{
  TreeNode *x = T;
  while (x->right != NULL)
  {
    x = x->right;
  }
  return x;
}

bool BST::remove(int JourneyCode, int price)
{
  TreeNode *x = search(root, price, JourneyCode);
  if (x == NULL)
  {
    return false;
  }
  if ((root->JourneyCode == JourneyCode) && (root->price == price))
  {
    if ((root->left == NULL) && (root->right == NULL))
    {
      root = NULL;
      return true;
    }

    if ((root->left == NULL) && (root->right != NULL))
    {
      root = root->right;
      root->parent = NULL;
      return true;
    }
    if ((root->left != NULL) && (root->right == NULL))
    {
      root = root->left;
      root->parent = NULL;
      return true;
    }
    if ((root->left != NULL) && (root->right != NULL))
    {
      TreeNode *pre = predecessor(root->left, root->price);
      int a = 0;
      int b = 0;
      a = pre->price;
      b = pre->JourneyCode;
      remove(b, a);
      root->price = a;
      root->JourneyCode = b;
      shortestdistance(root);
      longestdistance(root);
      return true;
    }
  }
  if (x != root)
  {
    TreeNode *p = x->parent;
    if ((x->left == NULL) && (x->right == NULL))
    {
      if (p->price < price)
      {
        p->right = NULL;
      }
      else
        p->left = NULL;
      x = NULL;
      shortestdistance(root);
      longestdistance(root);
      return true;
    }
    if ((x->left == NULL) && (x->right != NULL))
    {
      if (p->price < price)
        p->right = x->right;
      else
        p->left = x->right;
      x->right->parent = p;
      shortestdistance(root);
      longestdistance(root);
      return true;
    }
    if ((x->left != NULL) && (x->right == NULL))
    {
      if (p->price < x->price)
        p->right = x->left;
      else
        p->left = x->left;
      x->left->parent = p;
      shortestdistance(root);
      longestdistance(root);
      return true;
    }
    if ((x->left != NULL) && (x->right != NULL))
    {
      TreeNode *pre = predecessor(x->left, x->price);
      int a = 0;
      int b = 0;
      a = pre->price;
      b = pre->JourneyCode;
      remove(b, a);
      x->price = a;
      x->JourneyCode = b;
      shortestdistance(root);
      longestdistance(root);
      return true;
    }
  }
  return true;
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string &prefix, bool isLeft = false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
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

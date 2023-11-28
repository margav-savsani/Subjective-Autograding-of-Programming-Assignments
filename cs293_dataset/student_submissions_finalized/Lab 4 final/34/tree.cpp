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
// the below function returns longestpathlength of a node.
int BST::getImbalance()
{
  if (root == nullptr)
    return 0;
  else
  {
    return root->getImbalance();
  }
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  //if root is nullptr then assign value to it first.
  if (root == nullptr)
  {
    root = new struct TreeNode(JourneyCode, price);
    root->longestPathLength = root->shortestPathLength = 0;
  }
  // temp stores the the address of parent of place where we have to store the values.
  else
  {
    struct TreeNode *temp = root;
    while (true)
    {
      if (temp->JourneyCode == JourneyCode && temp->price == price)
      {
        // if we found the JourneyCode then exit.
        return false;
      }
      // the JourneyCode greater than or equal to the temp JourneyCode are stored in right subtree of temp
      else if (temp->JourneyCode < JourneyCode)
      {
        if (temp->right == nullptr)
        {
          temp->right = new struct TreeNode(JourneyCode, price);
          temp->right->shortestPathLength = temp->right->longestPathLength = 0;
          temp->right->parent = temp;
          break;
        }
        else
          temp = temp->right;
      }
      // the JourneyCode less than or equal to the temp JourneyCode are stored in left subtree of temp
      else
      {
        if (temp->left == nullptr)
        {
          temp->left = new struct TreeNode(JourneyCode, price);
          temp->left->shortestPathLength = temp->left->longestPathLength = 0;
          temp->left->parent = temp;
          break;
        }
        else
          temp = temp->left;
      }
    }

    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting

    //the parent of leaf node can have shortest as well as longest path length = 1, hence starting with curr_length = 1
    int curr_length = 1;
    //stop when we reached the root parent.
    while (temp != nullptr)
    {
      //if temp has only one child so shortestPathLength = 0
      if (temp->left == nullptr || temp->right == nullptr)
      {
        temp->shortestPathLength = 0;
      }
      //else min(1+left child shortestPathLength, 1+right child shortestpathLength)
      else
      {
        if (temp->left->shortestPathLength <= temp->right->shortestPathLength)
        {
          temp->shortestPathLength = temp->left->shortestPathLength + 1;
        }
        else
          temp->shortestPathLength = temp->right->shortestPathLength + 1;
      }
      //longestPathLength depends on curr length.
      if (temp->longestPathLength < curr_length)
        temp->longestPathLength = curr_length;
      temp = temp->parent;
      curr_length++;
    }
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
      return true;
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
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  int path_length = 0;
  // while (currNode != nullptr)
  // {
  //   if (currNode->JourneyCode < JourneyCode)
  //   {
  //     parentOfCurrNode = currNode;
  //     currNode = currNode->right;
  //     path_length++;
  //   }
  //   else if (currNode->JourneyCode > JourneyCode)
  //   {
  //     parentOfCurrNode = currNode;
  //     currNode = currNode->left;
  //     path_length++;
  //   }
  //   else
  //   { // currNode->JourneyCode == JourneyCode
  //     break;
  //   }
  // }
  struct TreeNode *temp = root;
  // After the while loop is executed, temp_parent will store the address of parent of node to be deleted.
  struct TreeNode *temp_parent = nullptr;
  while (true)
  {
    if (temp->JourneyCode == JourneyCode && temp->price == price)
    {
      // the temp to be deleted is found
      break;
    }
    else if (temp->price <= price)
    {
      if (temp->right == nullptr)
      {
        // reached the end and temp not found
        return false;
      }
      else
      {
        temp = temp->right;
        temp_parent = temp->parent;
      }
    }
    else
    {
      if (temp->left == nullptr)
      {
        // reached the end and temp not found
        return false;
      }
      else
      {
        temp = temp->left;
        temp_parent = temp->parent;
      }
    }
  }
  // case 1 : the temp is leaf node.
  if (temp->right == nullptr && temp->left == nullptr)
  {
    // this is the case when the temp is root
    if (temp_parent == nullptr)
    {
      root = nullptr;
      return true;
    }
    else
    {
      // temp is removed.
      if (temp_parent->left == temp)
      {
        temp->parent = nullptr;
        temp_parent->left = nullptr;
        return true;
      }
      else
      {
        temp_parent->right = nullptr;
        temp->parent = nullptr;
        return true;
      }
    }
  }
  // case 2 : the temp has only one child.
  else if (temp->right == nullptr || temp->left == nullptr)
  {
    // the case when temp is not root.
    if (temp_parent != nullptr)
    {
      // the child is left child
      if (temp->right == nullptr)
      {
        struct TreeNode *child = temp->left;
        child->parent = temp_parent;
        if (temp_parent->left == temp)
        {
          temp_parent->left = child;
        }
        else
        {
          temp_parent->right = child;
        }
        temp->parent = nullptr;
        temp->left = nullptr;
        return true;
      }
      // the child is right child
      else
      {
        struct TreeNode *child = temp->right;
        child->parent = temp_parent;
        if (temp_parent->left == temp)
        {
          temp_parent->left = child;
        }
        else
        {
          temp_parent->right = child;
        }
        temp->parent = nullptr;
        temp->right = nullptr;
        return true;
      }
    }
    // when temp is root.
    else
    {
      if (temp->right == nullptr)
      {
        root = temp->left;
        temp->left = nullptr;
        root->parent = nullptr;
        return true;
      }
      else
      {
        root = temp->right;
        temp->right = nullptr;
        root->parent = nullptr;
        return true;
      }
    }
  }
  // case 3 : the temp has two child.
  else
  {
    // successor stores the address of successor of temp.
    struct TreeNode *successor = temp->right;
    while (true)
    {
      if (successor->left != nullptr)
      {
        successor = successor->left;
      }
      else
        break;
    }
    // the info of successor and temp are swaped.
    temp->JourneyCode = successor->JourneyCode;
    temp->price = successor->price;
    successor->JourneyCode = JourneyCode;
    successor->price = price;
    temp = successor;
    temp_parent = successor->parent;
    // it is obvious that the successor's left child is nullptr.
    // so it has atmost 1 child.
    // case 1 : it has no child.
    if (temp->right == nullptr)
    {
      if (temp_parent->left == temp)
      {
        temp->parent = nullptr;
        temp_parent->left = nullptr;
        return true;
      }
      else
      {
        temp_parent->right = nullptr;
        temp->parent = nullptr;
        return true;
      }
    }
    // case 2 : it has left child.
    else
    {
      struct TreeNode *child = temp->right;
      child->parent = temp_parent;
      if (temp_parent->left == temp)
      {
        temp_parent->left = child;
      }
      else
      {
        temp_parent->right = child;
      }
      temp->parent = nullptr;
      temp->right = nullptr;
      return true;
    }
  }
  //since the pathlengths of ancestors of deleted node will get affected.
  int curr_length = 1;
  while (temp_parent != nullptr)
    {
      //if temp_parent has only one child so shortestPathLength = 0
      if (temp_parent->left == nullptr || temp_parent->right == nullptr)
      {
        temp_parent->shortestPathLength = 0;
      }
      //else min(1+left child shortestPathLength, 1+right child shortestpathLength)
      else
      {
        if (temp_parent->left->shortestPathLength <= temp_parent->right->shortestPathLength)
        {
          temp_parent->shortestPathLength = temp_parent->left->shortestPathLength + 1;
        }
        else
          temp_parent->shortestPathLength = temp_parent->right->shortestPathLength + 1;
      }
      //longestPathLength depends on curr length.
      if (temp_parent->longestPathLength < curr_length)
        temp_parent->longestPathLength = curr_length;
      temp_parent = temp_parent->parent;
      curr_length++;
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

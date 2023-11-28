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
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    
    // Make a new TreeNode with given journeycode and price

    struct TreeNode* node = new struct TreeNode(JourneyCode, price);
  
    if( root == NULL )
    {
        root = node;
    } 
    else
    {
        node->parent = parentOfCurrNode;
        if(parentOfCurrNode->left == NULL)
        {
          parentOfCurrNode->left = node;    
        }
        else
        {
          parentOfCurrNode->right = node; 
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

  if( root == NULL ) return false;
  
  struct TreeNode *temp = root;
  
  while(temp != NULL)
  {
    if(temp->JourneyCode == JourneyCode) return true;
    if(JourneyCode <= temp->JourneyCode ) temp = temp->left;
    else temp = temp->right;
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
    
  if(root == NULL) return root;
  
  struct TreeNode *node = root, *parent = NULL;
  
  // Finding if Journey code is present in the BST
  bool found = false;
  while(node != NULL)
  {
    if(node->JourneyCode == JourneyCode) {
      found = true;
      break;
    }
    else if(JourneyCode <= node->JourneyCode) {
      parent = node;
      node = node->left;
    } 
    else {
      parent = node;
      node = node->right;
    } 
  }
  
  // If not present return false;
  if(!found) return false;
  
  // Now node is present in BST, so 3 cases arise
  
  // 1 ==> If node has no child, then make parent point to null
  if(node->left == NULL && node->right == NULL)
  {
    // If node to be deleted is not root node, then simple make parent point to null
    if(parent != NULL)
    {
      if(parent->left == node) parent->left = NULL;
      else parent->right = NULL;
      delete node;
    }
    // else node to be deleted is root node
    else
    {
      root = NULL;
    }
    return true;

  }
  // 2==> If only 1 child
  else if(node->left == NULL || node->right == NULL)
  {
    // If node to be deleted is not the root node, then simply change relevant links  
    if(parent != NULL)
    {
      // If only right child
      if(node->left ==  NULL)
      {
        if(parent->left == node)
        {
          parent->left = node->right;
          parent->left->parent = parent;
          delete node;
        }
        else
        {
          parent->right = node->right;
          parent->right->parent = parent;
          delete node;
        }   
      }
      // If only left child
      else
      {
        if(parent->left == node)
        {
          parent->left = node->left;
          parent->left->parent = parent;
          delete node;
        }
        else
        {
          parent->right = node->left;
          parent->right->parent = parent;
          delete node;
        }
      }
    }
    // If node to be deleted is root node, then make root to either left BST or right BST
    else
    {
      if(node->left == NULL)
      {
        root = root->right;
      }
      else
      {
        root = root->left;
      }
    } 
    return true;  
  }
  // 3 ==> If both child are there
  else
  {
    struct TreeNode *temp = node;

    temp = temp->right;

    while(temp->left != NULL) temp = temp->left;
    //Copying data from successor of temp
    int t1 = temp->JourneyCode, t2 = temp->price; 
    bool removeSuccessor = remove(temp->JourneyCode , temp->price); 

    node->price = t2;
    node->JourneyCode = t1;
    return true;
  }
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
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

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}


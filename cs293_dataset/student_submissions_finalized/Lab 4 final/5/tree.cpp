// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

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
 

 struct TreeNode* node = new struct TreeNode(JourneyCode, price);
  
  if( root == NULL )
  { // If node is the first Journey entered, then change root
    root = node;
    return true;
  } 
  
  struct TreeNode* temp = root , *parent = NULL;
  
  // Searching if given journey already exist in the BST
  while(temp != NULL)
  {
    if(temp->JourneyCode == JourneyCode)
    { 
      // If found, then return
      return false;
    }
    else if(JourneyCode < temp->JourneyCode)
    {
      parent = temp;
      temp = temp->left;
    }
    else {
      parent = temp;
      temp = temp->right;
    }   
  }
  
  
  // journey not found, so enter it in BST
  node->parent = parent;
  if(parent->left == NULL && JourneyCode < parent->JourneyCode)
  {
    parent->left = node;    
  }
  else
  {
    parent->right = node; 
  }

  // Now, we move up the Tree from parent node and update the shortestPathLength and longestPathLength. If the shortest path of node was less than that of parent, then parent's shortest path length will be nodes-shortest length + 1. Similarly if node's longest path length was longer than parent's, then parent's longest path will be child's + 1.
  while(parent != nullptr)
  {
    if(parent->shortestPathLength > node->shortestPathLength) parent->shortestPathLength = node->shortestPathLength + 1;
    if(parent->longestPathLength <= node->longestPathLength) parent->longestPathLength = node->longestPathLength + 1;

    node = parent;
    parent = node->parent;
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
    
  return false;
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


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

  if (root == NULL){
    root = new TreeNode(JourneyCode, price);
    root->parent = NULL;
    root->longestPathLength = 1;
    root->shortestPathLength = 1;
    return true;
  }

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
  }
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  
  if (parentOfCurrNode->JourneyCode < JourneyCode){
    parentOfCurrNode->right = new TreeNode(JourneyCode,price,NULL,NULL,parentOfCurrNode);
    currNode = parentOfCurrNode->right;
    
  }
  else{
    parentOfCurrNode->left = new TreeNode(JourneyCode,price,NULL,NULL,parentOfCurrNode);
    currNode = parentOfCurrNode->left;
  }

  currNode->shortestPathLength = 1;
  currNode->longestPathLength = 1;

  TreeNode *earlierNode=currNode;
  currNode = currNode->parent;

  bool nochange_l=false;
  bool nochange_s=false;

  while (currNode != NULL && !(nochange_s && nochange_l)){
    if (currNode->left == earlierNode){
      if (!nochange_l){
        if (currNode->getLongestright() >= currNode->getLongestleft()){
          nochange_l = true;
        }
        else {
          currNode->longestPathLength = currNode->getLongestleft()+1; 
        }
      }

      if (!nochange_s){
        if (currNode->getShortestright() <= currNode->getShortestleft()){
          nochange_s = true;
        }
        else {
          currNode->shortestPathLength = currNode->getShortestleft()+1;
        }
      }
    }
    else if (currNode->right == earlierNode){
      if (!nochange_l){
        if (currNode->getLongestright() < currNode->getLongestleft()){
          nochange_l = true;
        }
        else {
          currNode->longestPathLength = currNode->getLongestright()+1; 
        }
      }

      if (!nochange_s){
        if (currNode->getShortestright() > currNode->getShortestleft()){
          nochange_s = true;
        }
        else {
          currNode->shortestPathLength = currNode->getShortestright()+1;
        }
      }
    }
    earlierNode = currNode;
    currNode = currNode->parent;
  }

  /*while(currNode != NULL){
    TreeNode *r = currNode->right;

    if (!currNode->getLongestleft()){
      currNode->longestPathLength = currNode->right->longestPathLength+1;
    }
    else if (!currNode->getLongestright()){
      currNode->longestPathLength = currNode->left->longestPathLength+1;
    }
    else{
      currNode->longestPathLength = max(currNode->right->longestPathLength+1,currNode->left->longestPathLength+1);
    }

    if (!currNode->getShortestleft()){
      currNode->shortestPathLength = currNode->right->shortestPathLength+1;
    }
    else if (!currNode->getShortestright()){
      currNode->shortestPathLength = currNode->left->shortestPathLength+1;
    }
    else{
      currNode->shortestPathLength = min(currNode->right->shortestPathLength+1,currNode->left->shortestPathLength+1);
    }
    earlierNode = currNode;
    currNode = currNode->parent;
  }*/

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
  TreeNode *currNode=root, *ParentOfcurrNode=NULL; 
  while (currNode !=NULL){
    if (currNode->JourneyCode < JourneyCode){
      ParentOfcurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode){
      ParentOfcurrNode = currNode;
      currNode = currNode->left;
    }
    else {
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


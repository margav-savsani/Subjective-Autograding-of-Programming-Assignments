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
  }
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  currNode = new TreeNode(JourneyCode, price, nullptr, nullptr, parentOfCurrNode,0,0);
  if (parentOfCurrNode->JourneyCode < currNode->JourneyCode) {
    parentOfCurrNode->left = currNode;
  }
  else{
    parentOfCurrNode->right = currNode;
  }
  while(parentOfCurrNode != nullptr){
    if(parentOfCurrNode->shortestPathLength > currNode->shortestPathLength+1) parentOfCurrNode->shortestPathLength = currNode->shortestPathLength+1;
    if(parentOfCurrNode->longestPathLength < currNode->longestPathLength+1) parentOfCurrNode->longestPathLength = currNode->longestPathLength+1;
    currNode=parentOfCurrNode;
    parentOfCurrNode=currNode->parent;
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
      if(currNode->price == price) return true;
      else return false;
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
  while (currNode != nullptr){
    if (JourneyCode == currNode->JourneyCode){
      if (currNode->left == nullptr && currNode-> right == nullptr){
        //cout << "here" << currNode->JourneyCode << " " << currNode->price << endl;
        if(currNode->parent != nullptr){
          if(currNode->price < currNode->parent->price){
            currNode->parent->left = nullptr;
          }
          else{
            currNode->parent->right = nullptr;
          }
        }
        else root = nullptr;
        delete[] currNode;
        currNode = nullptr;
      }
      else if (currNode->left == nullptr || currNode->right == nullptr){
          TreeNode *currNode_parent = currNode->parent;
          TreeNode *currNode_child;

          if(currNode->left != nullptr){
              currNode_child = currNode->left;
          }
          else if (currNode->right != nullptr){
              currNode_child = currNode->right;
          }

          currNode_child->parent = currNode_parent;
          if(currNode->parent != nullptr){
              if(currNode_child->price < currNode_parent->price){
                  currNode_parent->left = currNode_child;
              }
              else{
                  currNode_parent->right = currNode_child;
              }
          }
          else root = currNode_child;
          delete[] currNode;
      }
      else{
          TreeNode *successor = currNode->right;
          while(successor->left != nullptr) successor = successor->left;
          TreeNode *currNode_parent = currNode->parent;
          TreeNode temp(successor->JourneyCode, successor->price, successor->left, successor->right, currNode_parent, successor->shortestPathLength, successor->longestPathLength);
          remove(successor->JourneyCode, successor->price);
          currNode->JourneyCode = temp.JourneyCode;
          currNode->price = temp.price;
      }
      /*
      cout << "PRE" << endl;
      traverse(0);
      cout << "IN" << endl;
      traverse(2);
      */
      return true;
    }
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    else if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
  }
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


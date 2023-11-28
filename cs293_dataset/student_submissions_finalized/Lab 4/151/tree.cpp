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




    currNode = new TreeNode(JourneyCode, price, nullptr, nullptr, parentOfCurrNode);
    currNode->shortestPathLength = 0;
    currNode->longestPathLength = 0;
    
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting
    



    //////////////////////////////////////////////
    //  UPDATE SHORTEST AND LONGEST PATH LENGTH //
    //////////////////////////////////////////////


/*

    int curr_pathLength = 0;

    while(parentOfCurrNode != nullptr){
      curr_pathLength++;

      if(parentOfCurrNode->left == nullptr || parentOfCurrNode->right == nullptr){
        parentOfCurrNode->longestPathLength = currNode->longestPathLength + 1;
      }
    }

*/

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
      return true;
    }
  
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{

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
      
      // case when current node has no children
      if(currNode->right == nullptr && currNode->left == nullptr){
        if(parentOfCurrNode->left == currNode)
          parentOfCurrNode->left = nullptr;
        else
          parentOfCurrNode->right = nullptr;
      }

      // case when the node has only a left child
      else if(currNode->right == nullptr && currNode->left != nullptr){
        if(parentOfCurrNode->left == currNode)
          parentOfCurrNode->left = currNode->left;
        else
          parentOfCurrNode->right = currNode->left;
      }

      // case when the node has only a right child
      else if(currNode->right != nullptr && currNode->left == nullptr){
        if(parentOfCurrNode->left == currNode)
          parentOfCurrNode->left = currNode->right;
        else
          parentOfCurrNode->right = currNode->right;
      }

      // case when node has two children
      // In this case, we have to find the 
      // predecessor (or successor) and make the 
      // parent node point to it instead
      else {
        TreeNode* predecessor = x->left;

        while(predecessor->right != nullptr)
          predecessor = predecessor->right;

        currNode->JourneyCode = predecessor->JourneyCode;
        currNode->price = predecessor->price;

        BST::remove(predecessor->JourneyCode, predecessor->price);
      }



    //////////////////////////////////////////////
    //  UPDATE SHORTEST AND LONGEST PATH LENGTH //
    //////////////////////////////////////////////




      return true;
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


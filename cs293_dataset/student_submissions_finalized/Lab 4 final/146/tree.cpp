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
  //First we check if tree is empty in which case we add root with parent pointing to NULL
  if(root == NULL){
      root = new TreeNode;
      root->parent = NULL;
      root->left = NULL;
      root->right = NULL;
      root->price = price;
      root->JourneyCode = JourneyCode;
      root->longestPathLength=1;
      root->shortestPathLength=1;
      return true;
  }
  struct TreeNode *currNode = root;
  
  while (true) {
    int x = currNode->JourneyCode;
    if (x > JourneyCode) {
      if (currNode->left == NULL){
        currNode->left = new TreeNode;
        currNode->left->parent=currNode;
        currNode->left->JourneyCode=JourneyCode;
        currNode->left->price=price;
        currNode->left->longestPathLength=1;
        currNode->left->shortestPathLength=1;
        currNode = currNode->left; 
        break;
      }
      currNode = currNode->left;
    }
    else if (x < JourneyCode) {
      if (currNode->right == NULL){
        currNode->right = new TreeNode;
        currNode->right->parent = currNode;
        currNode->right->JourneyCode=JourneyCode;
        currNode->right->price=price;
        currNode->right->longestPathLength=1;
        currNode->right->shortestPathLength=1;
        currNode = currNode->right; 
        break;
      }

      currNode = currNode->right;
    }
    else { // currNode->JourneyCode == JourneyCode
      return false;
    }
  }
  //$ We keep updating value of path lengths of currNode->parent
  while(currNode->parent!=NULL){
    currNode->parent->longestPathLength = max(currNode->parent->longestPathLength,currNode->longestPathLength+1);

    if(currNode->parent->right != NULL && currNode->parent->left!=NULL){ //$ Because in other there cases no need to update shortestpathlength
      //$ We check if currNode is left child or right child
      if(currNode->parent->left == currNode){
        currNode->parent->shortestPathLength = min(currNode->shortestPathLength +1 , currNode->parent->right->shortestPathLength +1);
      }
      else if(currNode->parent->right == currNode){
        currNode->parent->shortestPathLength = min(currNode->shortestPathLength +1 , currNode->parent->left->shortestPathLength +1);
      }
    }
    currNode = currNode->parent;
  }
  return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  TreeNode* currNode = root;
  while(currNode!=NULL){
    if(currNode->JourneyCode>JourneyCode) currNode = currNode->left;
    else if(currNode->JourneyCode<JourneyCode) currNode = currNode->right;
    else {
      if(currNode->price == price) return true;
      else return false;
    } 
  }
  
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price){
  TreeNode* currNode = root;
  while(currNode!=NULL){
    if(currNode->JourneyCode>JourneyCode) currNode = currNode->left;
    else if(currNode->JourneyCode<JourneyCode) currNode = currNode->right;
    else {
      if(currNode->price == price){
        if(currNode->left == NULL){
          if(currNode->parent==NULL){
            root = currNode->right;
          }
          else if(currNode->parent->right == currNode){
            currNode->parent->right = currNode->right;
            if(currNode->right!=NULL) currNode->right->parent = currNode->parent;
          }
          else if(currNode->parent->left == currNode){
            currNode->parent->left = currNode->right;
            if(currNode->right!=NULL) currNode->right->parent = currNode->parent;
          }
        }
        else{
          if(currNode->left->right==NULL){
            currNode->left->right=currNode->right;
            currNode->left->parent = currNode->parent;
            if(currNode->right!=NULL) currNode->right->parent = currNode->left;

            if(currNode->parent==NULL){
              root = currNode->left;
            }
            else if(currNode->parent->right == currNode){
              currNode->parent->right = currNode->left;
            }
            else if(currNode->parent->left == currNode){
              currNode->parent->left = currNode->left;
            }
          }
          else{
            TreeNode* pred = currNode->left; //we find the predecessor
            while(pred->right!= NULL) {pred = pred->right;}

            pred->right = currNode->right;
            if(currNode->right != NULL) currNode->right->parent = pred;

            currNode->left->parent = currNode->parent;

            if(currNode->parent==NULL){
              root = currNode->left;
            }
            else if(currNode->parent->left == currNode){
              currNode->parent->left = currNode->left;
            }
            else if(currNode->parent->right == currNode){
              currNode->parent->right = currNode->left;
            }
          }

        }
        updateLengths(root);
        return true;
      }
      else return false;
    } 
  }
  return false;
}

//Updates the length (Not really needed unless deletion is called which mostly won't me). Just created for completeness .

bool BST::updateLengths(TreeNode* root){
  if(root==NULL) return true;
 
  updateLengths(root->left);
  updateLengths(root->right);
  if(root->right!=NULL && root->left!=NULL){
    root->shortestPathLength = min(root->right->shortestPathLength, root->left->shortestPathLength) +1;
    root->longestPathLength = max(root->right->longestPathLength, root->left->longestPathLength) +1;
  } 
  else if (root->right == NULL && root->left == NULL){
    root->shortestPathLength = 1;
    root->longestPathLength = 1;
  } 
  else if (root->right == NULL){
    root->shortestPathLength = 1;
    root->longestPathLength = root->left->longestPathLength+1;
  }
  else{
    root->shortestPathLength = 1;
    root->longestPathLength = root->right->longestPathLength+1;
  }
  return true;
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
        root = curr;
        root = root->right;
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
        result.push_back(root->JourneyCode + "\n");
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


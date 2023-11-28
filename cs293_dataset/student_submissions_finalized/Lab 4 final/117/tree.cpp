// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "tree.h"

BST::BST(){
  root =  new TreeNode();
}

BST::BST(TreeNode* root){
  this->root =  NULL;
}

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
  if (root == nullptr) return 0;
  else return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price){
    if(root->JourneyCode == 0){// if empty tree
        root->JourneyCode = JourneyCode;
        root->price = price;
        return true;
    }
    bool ans = insertRecursive(JourneyCode, price, root);// called a recursive function
}
// same element is inserted in the 
bool BST::insertRecursive(int JourneyCode, int price, TreeNode* myroot){
    if(myroot->JourneyCode == JourneyCode){// if same journey code present, returns false
        return false;
    }
    else if(myroot->JourneyCode <= JourneyCode){// if price of given insert is greater then or equal to the price at a node, the new node will be inserted in the right tree. Note: node with same price is inserted in the right tree
        if(myroot->right == NULL){// if right is null, insert the node
            myroot->right = new TreeNode(JourneyCode,price,NULL, NULL, myroot);
            myroot->right->shortestPathLength =1;
            myroot->right->longestPathLength =1;
            UpdateAncestorlengths(myroot->right);
            return true;
        }
        else return insertRecursive(JourneyCode, price, myroot->right);// else call recursively
    }
    else{// similarly for left
        if(myroot->left == NULL){
            myroot->left = new TreeNode(JourneyCode,price,NULL, NULL, myroot);
            myroot->left->shortestPathLength =1;
            myroot->left->longestPathLength =1;
            UpdateAncestorlengths(myroot->left);
            return true;
        }
        else return insertRecursive(JourneyCode, price, myroot->left);
    }
}

void BST::UpdateAncestorlengths(TreeNode* node){
  if(node == NULL) return;
  TreeNode* mynode = node;
  while(true){
    if(mynode->parent == NULL) return;
    mynode = mynode->parent;
    if(mynode->left == NULL){
      mynode->longestPathLength = mynode->right->longestPathLength+1;
      mynode->shortestPathLength = mynode->right->shortestPathLength+1;
    }
    else if(mynode->right == NULL){
      mynode->longestPathLength = mynode->left->longestPathLength+1;
      mynode->shortestPathLength = mynode->left->shortestPathLength+1;
    }
    else{
      mynode->longestPathLength = 1+ max(mynode->left->longestPathLength , mynode->right->longestPathLength );
      mynode->shortestPathLength = 1+ min(mynode->left->shortestPathLength , mynode->right->shortestPathLength);
    }
  }
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


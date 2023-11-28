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

bool Contains(int jrnycode, int val, TreeNode*& node) {
    if(node == nullptr){
        return false;
    } else if(val == node->price){
        return true;
    } else if(val < node->price){
        return Contains(jrnycode, val, node->left);
    } else{
        return Contains(jrnycode, val, node->right);
    }
}

bool Insert(int jrnycode, int val, TreeNode* node) {
    if(Contains(jrnycode,val, node)==true)return false;

    /*if(val == node->price){
        if(jrnycode == node->JourneyCode)
            return false;
    }*/
    if(val < node->price){
        if(node->left == nullptr){
            node->left = new TreeNode(jrnycode, val);
            return true;
        } else{
            return Insert(jrnycode, val, node->left);
        }
    } else if(val> node->price){
        if(node->right == nullptr){
            node->right = new TreeNode(jrnycode, val);
            return true;
        } else{
            return Insert( jrnycode,val, node->right);
        }
    }
    return false;
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  /*  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  
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
    */

    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting

    bool b = false;
    if(root==nullptr){
        this->root = new TreeNode(JourneyCode,price);
        b = true;
    }
    else {
        b = Insert(JourneyCode,price,this->root);
    }
    return b;
}


// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  return Contains(JourneyCode, price, this->root);
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise

bool Remove(int val, int jrnycode, TreeNode*& node) {
    if(node == nullptr){
        return false;
    } 
    else if (val == node->price && jrnycode == node->JourneyCode){        
        TreeNode* trash = nullptr;
        if(node->left == nullptr && node->right == nullptr){            
            trash = node;
            node = nullptr;
        }
        else if(node->left != nullptr && node->right == nullptr){            
            trash = node;
            node = node->left;
        }
        else if(node->left == nullptr && node->right != nullptr){
            trash = node;
            node = node->right;
        }
        else{            
            TreeNode*& minNode = FindMin(node->right); 
            node->price = minNode->price;
            node->JourneyCode = minNode->JourneyCode;
            Remove(minNode->price, minNode->JourneyCode, minNode);
        }
        if(trash != nullptr) {delete trash;}
        return true;
    }
    else if(val < node->price){
        Remove(val, jrnycode, node->left);
    } else{
        Remove(val,jrnycode, node->right);
    }
    return true;
}

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
    
  return Remove(price, JourneyCode, this->root);
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


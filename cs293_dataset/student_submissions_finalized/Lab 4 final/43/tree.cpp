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
int BST::Short( TreeNode *r){
  if(r->left == nullptr || r->right == nullptr){
    r->shortestPathLength = 1;
    return 1;
  }
  if(Short(r->right)<Short(r->left)){
      r->shortestPathLength = Short(r->right)+1;
      return Short(r->right)+1;
  }
  else{
     r->shortestPathLength = Short(r->left)+1;
     return Short(r->left)+1;
  }
}

int BST::Long(TreeNode *r){
  if(r->left == nullptr && r->right == nullptr){
    r->longestPathLength = 1;
    return 1;
  }
  else if(r->left != nullptr && r->right == nullptr){
    r->longestPathLength = Long(r->left)+1;
    return r->longestPathLength;
  }
  else if(r->left == nullptr && r->right != nullptr){
    r->longestPathLength = Long(r->right)+1;
    return r->longestPathLength;
  }
  if(Long(r->right)<Long(r->left)){
    r->longestPathLength = Long(r->left)+1;
    return r->longestPathLength;
  }
  else{
    r->longestPathLength = Long(r->right)+1;
    return r->longestPathLength;
  }
}
bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
 if((root->JourneyCode == 0)&&(root->price == 0)){
    root->JourneyCode = JourneyCode;
    root->price = price;
    root->parent = nullptr;
    root->longestPathLength = 1;
    root->shortestPathLength = 1;
    return true;
   }
   else if((root->JourneyCode == JourneyCode)&&(root->price == price)){
     return false;
   }
   else if(root->JourneyCode < JourneyCode){
    TreeNode *r;
    if(root->right == nullptr){
        r = new TreeNode(JourneyCode,price);
        root->right = r;
        r->parent = root;
        return true;
    }
    else{
        r = root->right;
        BST m;
        m.root = r;
        return m.insert(JourneyCode,price);
    }
   }
   else if(root->JourneyCode >= JourneyCode){
    TreeNode *r;
    if(root->left == nullptr){
        r = new TreeNode(JourneyCode,price);
        root->left = r;
        r->parent = root;
        return true;
    }
    else{
        r = root->left;
        BST m;
        m.root = r;
        return m.insert(JourneyCode,price);
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
TreeNode* BST::rv(){
  return root;
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


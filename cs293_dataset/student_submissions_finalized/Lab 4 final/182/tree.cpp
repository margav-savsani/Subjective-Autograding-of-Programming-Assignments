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
int shortestpath(TreeNode *A){
int a=0;
while(A->left==nullptr || A->right==nullptr)
  {
    a++;
    if(shortestpath(A->left)>=shortestpath(A->right)) A=A->right;
    else A=A->left;
  }
  return a;
}
int longestpath(TreeNode *A){
int a=0;
while(A->left==nullptr || A->right==nullptr)
  {
    a++;
    if(longestpath(A->left)>=longestpath(A->right)) A=A->left;
    else A=A->right;
  }
  return a;
}
int BST::getImbalance()
{ 
  if (root == nullptr) return 0;
  return root->getImbalance();
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
  if (JourneyCode < parentOfCurrNode->JourneyCode)
    {
        parentOfCurrNode->left = currNode;
        currNode->parent = parentOfCurrNode;
        return true;
    }
  if (JourneyCode > parentOfCurrNode->JourneyCode)
    {
        parentOfCurrNode->right = currNode;
        currNode->parent = parentOfCurrNode;
        return true;
    }
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  // You can look at the implementation of insert to code this part up.
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  while (currNode != nullptr) {
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    if (currNode->JourneyCode == JourneyCode )
      { if(currNode->price == price ) return true ;
        else  return false;
    }
  }
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  if(!find(JourneyCode,price)) return false ;
  struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
  while (currNode != nullptr) {
    if (currNode->JourneyCode == JourneyCode )
    { if (currNode->left == nullptr && currNode->right == nullptr)
        {
          if(parentOfCurrNode->right==currNode) {parentOfCurrNode->right=nullptr;currNode=nullptr;}
          if(parentOfCurrNode->left==currNode) {parentOfCurrNode->left=nullptr;currNode=nullptr;}
          return true;
        }
      if (currNode->left == nullptr || currNode->right == nullptr )
      { if(currNode->right==nullptr)
        { currNode=currNode->left;
          currNode->parent=parentOfCurrNode;
          if(parentOfCurrNode->right==currNode) {parentOfCurrNode->right=currNode;}
          if(parentOfCurrNode->left==currNode) {parentOfCurrNode->left=currNode;}
        }
        if(currNode->left==nullptr)
        { currNode=currNode->right;
          if(parentOfCurrNode->right==currNode) {parentOfCurrNode->right=currNode;}
          if(parentOfCurrNode->left==currNode) {parentOfCurrNode->left=currNode;}
        }
      }
    }
    if (currNode->JourneyCode < JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->right;
    }
    if (currNode->JourneyCode > JourneyCode) {
      parentOfCurrNode = currNode;
      currNode = currNode->left;
    }
    
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


// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <stdlib.h>
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
  else return getLongestPath()-getShortestPath();
}

bool BST::insert(int JourneyCode, int price)
{
  if(root==NULL){
      TreeNode* newNode = new TreeNode(JourneyCode,price);
      root = newNode;
      root->parent=NULL;
      return true;
  }
  if(find(JourneyCode, price)) return false;
  TreeNode* true_root = root;
  if(root->JourneyCode<=JourneyCode){
      if(root->right==NULL){
          TreeNode* newNode = new TreeNode(JourneyCode,price,NULL,NULL,root);
          root->right=newNode;
      }
      else{
          root = true_root->right;
          insert(JourneyCode,price);
          root = true_root;
      }
  }
  else{
      if(root->left==NULL){
          TreeNode* newNode = new TreeNode(JourneyCode,price,NULL,NULL,root);
          root->left=newNode;
      }
      else{
          root = true_root->left;
          insert(JourneyCode,price);
          root = true_root;
      }
  }
  root = true_root;
  return true;
}

int BST::getShortestPath(){
    if(root==NULL) return 1000000000;
    TreeNode* true_root = root;
    root = root->left;
    int l = getShortestPath();
    root = true_root->right;
    int r = getShortestPath();
    root = true_root;
    if(l==1000000000&&r==1000000000) return 1;
    else return min(l,r)+1;
}

int BST::getLongestPath(){
    if(root==NULL) return 0;
    TreeNode* true_root = root;
    root = root->left;
    int l = getLongestPath();
    root = true_root->right;
    int r = getLongestPath();
    root = true_root;
    return max(l,r)+1;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  if(root==NULL) return false;
  if(root->price==price&&root->JourneyCode==JourneyCode) return true;
  TreeNode* true_root = root;
  if(root->price<=price){
      root = true_root->right;
      bool ans = find(JourneyCode,price);
      root = true_root;
      return ans;
  }
  else{
      root = true_root->left;
      bool ans = find(JourneyCode,price);
      root = true_root;
      return ans;
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


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
  else return root->getImbalance();
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
  if(root->price<=price){
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
  return true;
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
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  if(!find(JourneyCode,price)) return false;
  if(root==NULL) return false;
  if(root->JourneyCode==JourneyCode){
      if(root->left==NULL&&root->right==NULL){
          if(root->parent==NULL){
              root=NULL;
              return true;
          }
          else if(root->parent->left==root){
              root->parent->left=NULL;
              root->parent=NULL;
          }
          else if(root->parent->right==root){
              root->parent->right=NULL;
              root->parent=NULL;
          }
      }
      else if(root->left==NULL){
          root->price=root->right->price;
          root->JourneyCode=root->right->JourneyCode;
          root->left=root->right->left;
          root->right=root->right->right;
      }
      else if(root->right==NULL){
          root->price=root->left->price;
          root->JourneyCode=root->left->JourneyCode;
          root->right=root->left->right;
          root->left=root->left->left;
      }
      else{
          TreeNode* successor = root->right;
          while(successor->left!=NULL){
              successor=successor->left;
          }
          int final_price = successor->price;
          int final_code = successor->JourneyCode;
          remove(successor->JourneyCode,successor->price);
          root->price=final_price;
          root->JourneyCode=final_code;
      }
  }
  else if(price>=root->price){
      TreeNode* true_root = root;
      root = true_root->right;
      remove(JourneyCode,price);
      root = true_root;
  }
  else{
      TreeNode* true_root = root;
      root = true_root->left;
      remove(JourneyCode,price);
      root = true_root;
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


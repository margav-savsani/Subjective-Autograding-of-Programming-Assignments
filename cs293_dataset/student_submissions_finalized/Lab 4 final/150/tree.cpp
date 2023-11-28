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
  if (root == NULL) {
     root = new TreeNode(JourneyCode,price);
     return true;
  }
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
      if (parentOfCurrNode->JourneyCode > JourneyCode)
      {
         parentOfCurrNode->left = new TreeNode(JourneyCode,price);
      }
       if (parentOfCurrNode->JourneyCode < JourneyCode)
      {
         parentOfCurrNode->right = new TreeNode(JourneyCode,price);
      }
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
  
  return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
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
    else if (currNode->JourneyCode == JourneyCode ){
        if (currNode->price == price) return true;
        else return false;
    }
    }
  
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
  TreeNode* BST::Mymin( TreeNode* a){
         TreeNode *x = a->right;
            while (x->left != NULL)
            {
                x = x->left;
            }
            if (x->left == NULL)
            {
                return x;
            }
    };
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    TreeNode *x = root;
    TreeNode *y;
    if (x == NULL)
    {
        return false;
    }
    while (x != NULL)
    {
        if (x->JourneyCode > JourneyCode)
        {

            y = x;
            x = x->left;
        }

        else if (x->JourneyCode < JourneyCode)
        {
            y = x;
            x = x->right;
        }
        else if (x->JourneyCode == JourneyCode)
        {
            if (x->price == price)
            {
                break;
            }
            else
            {
                y = x;
                x = x->right;
            }
        }
    }
  
        if (x == NULL)
        {
            return false;
        }
        
        else 
        {
           
            if (x->left == NULL && x->right == NULL)
            {   if (x->JourneyCode == root->JourneyCode)
                 {
                    root =NULL;
                 }
                else
                if (y->left == x)
                {
                    y->left = NULL;
                }
                else if (y->right == x)
                {
                    
                    y->right = NULL;
                }
            }

            else if (x->left == NULL)
            {   if (x->JourneyCode==root->JourneyCode)
                {
                   root = x->right;  
                }
                else if (y->left == x)
                {
                    y->left = x->right;
                }
                else if (y->right == x)
                {
                    y->right = x->right;
                }
            }

            else if (x->right == NULL)
            {
                if (x->JourneyCode==root->JourneyCode)
                {
                   root = x->left;  
                }
                else if (y->left == x)
                {
                    y->left = x->left;
                }
                else if (y->right == x)
                {
                    y->right = x->left;
                }
            }

            else {
              TreeNode* success = Mymin(x);
              remove(success->JourneyCode,success->price);
              x->JourneyCode = success->JourneyCode;
              x->price = success->price; 
            }

            return true;
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



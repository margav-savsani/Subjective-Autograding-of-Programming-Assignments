// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
// #include "choose.cpp"

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
  struct TreeNode *curr = root, *parent = nullptr;
  if ( root == nullptr )  { 
    curr = new TreeNode(JourneyCode, price) ;
    root = curr ; 
    root->shortestPathLength = 1 ; 
    root->longestPathLength = 1 ; 
  } 
  else {
    while (curr != nullptr) {
      if (curr->JourneyCode < JourneyCode) {
      parent = curr;
      curr = curr->right;
    }
    else if (curr->JourneyCode > JourneyCode) {
      parent = curr;
      curr = curr->left;
    }
    else { 
      return false;
    }
   }
    curr = new TreeNode(JourneyCode,price,parent) ;
    if ( parent->JourneyCode < JourneyCode ) parent->right = curr ; 
    else parent->left = curr ; 

   //Shortest and longest path of a leaf is one (base case) . 
   //Order of n / 2^n . 

   curr->shortestPathLength = 1 ; 
   curr->longestPathLength = 1 ; 

   while(parent !=  nullptr ) {
         int previous_shortest = parent->shortestPathLength ; 
         int previous_longest = parent->longestPathLength ; 
         if (parent->left == nullptr ) { 
             parent->shortestPathLength =  1 ; 
             parent->longestPathLength = parent->right->longestPathLength + 1 ; 
         }
         else if (parent->right == nullptr ) { 
             parent->shortestPathLength =  1 ; 
             parent->longestPathLength = parent->left->longestPathLength + 1 ; 
         }
         else { 
              parent->shortestPathLength =  1 + min(parent->left->shortestPathLength , parent->right->shortestPathLength );
              parent->longestPathLength =  1 + max(parent->left->longestPathLength , parent->right->longestPathLength );
         }
         if ( previous_shortest == parent->shortestPathLength && 
              previous_longest == parent->longestPathLength ) break ; 
         parent = parent->parent  ; 
    }
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
  
  return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    
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
        cout << root->JourneyCode << " : "<< root->shortestPathLength <<" : " << root->longestPathLength << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    ") , true);
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


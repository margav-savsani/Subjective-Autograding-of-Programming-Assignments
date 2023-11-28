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

void BST::updatePaths(TreeNode *node){
    node->longestPathLength = 0;
    node->shortestPathLength = 0;
    TreeNode *parent = node->parent ;
    TreeNode *child =  node;
    while (parent != nullptr){
        if (parent->left == nullptr || parent->right == nullptr){
            parent->longestPathLength = 1+child->longestPathLength;
            parent->shortestPathLength = 1+child->shortestPathLength;
        }
        else if (parent->left != nullptr && parent->right != nullptr){
            if (parent->left->longestPathLength > parent->right->longestPathLength){
                parent->longestPathLength = parent->left->longestPathLength + 1;
            }
            else parent->longestPathLength = parent->right->longestPathLength + 1;
            if (parent->left->shortestPathLength > parent->right->shortestPathLength){
                parent->shortestPathLength = parent->right->shortestPathLength + 1;
            }
            else parent->shortestPathLength = parent->left->shortestPathLength + 1;
        }
        child = parent;
        parent = parent->parent;
    }
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
    if (root==nullptr) {
        root = new TreeNode();
        root->JourneyCode = JourneyCode;
        root->price=price;
        return true;
     }
    if(find(JourneyCode, price)){
        return false;
    }
    TreeNode * x = root; 
    TreeNode * y = NULL;
    TreeNode * z = new TreeNode(JourneyCode,price,NULL,NULL,NULL);
    while( x != nullptr){
        y = x;
        if(price < x-> price){
            x = x -> left; 
        }
        else{
            x = x -> right; 
        }
    }
    if ( y == nullptr){
        root = z;
    }
    else if (price >= y -> price) {
        y -> right = z;
        y->right->parent = y ;
    }
    else{
        y -> left = z;
        y->left->parent = y;
    }
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting
  
    updatePaths(z);
    return true;
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    TreeNode * x = root;
    while(x != nullptr){
        if(x -> price == price){
            return (x -> JourneyCode == JourneyCode);
        }
        else{
            if(x -> price > price){
                x = x -> left ;
            }
            else{
                x = x -> right; 
            }
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
        cout << root->JourneyCode <<"S: "<<root->shortestPathLength << "L: "<<root->longestPathLength <<endl;
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


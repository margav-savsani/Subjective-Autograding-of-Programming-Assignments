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
TreeNode* insert2(TreeNode* root, int JourneyCode, int price){



	if( root == NULL){
	
		TreeNode* n= new TreeNode(JourneyCode,price);
		root = n;
		return root;
	}
	
	if( JourneyCode > root->JourneyCode){
	
		root->right = insert2(root->right, JourneyCode, price);

	}
	else if( JourneyCode < root->JourneyCode){
	
		root->left = insert2(root->left, JourneyCode, price);
	}
	
	return root;
}
	
bool BST::insert(int JourneyCode, int price) // inserts elements into tree
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.
  
  
 bool found = find(JourneyCode,price);
	
	if(found) return false;
	
	root = insert2(root, JourneyCode, price);
	root->shortestPathLength = minimum(root);
	root->longestPathLength = maximum(root);;
	return true;
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

bool find2( TreeNode* root, int JourneyCode, int price){ 

	if( root == NULL){
	
		return false;
	}

	if( root->JourneyCode == JourneyCode){
		
			return true;
	}
	
	else if( root->JourneyCode < JourneyCode){
	
		return find2(root->right, JourneyCode, price);
	}
	
	else if( root->JourneyCode > JourneyCode ){
	
		return find2(root->left, JourneyCode, price);
	}
	return false;
	
}
bool BST::find(int JourneyCode, int price) 
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
  if( root == nullptr) return false;
  return find2(root, JourneyCode, price);
}

TreeNode* min2(TreeNode* root){

	if( root == NULL) return NULL;

	if ( root->left == NULL) return root;
	else return min2(root->left);
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
TreeNode* remove2(TreeNode* root, int JourneyCode, int price){ 

	if( root== NULL){
	
		return NULL;
	}

	if( root->JourneyCode < JourneyCode){
	
		root->right = remove2(root->right, JourneyCode, price);
	}
	else if( root->JourneyCode > JourneyCode){
	
		root->left = remove2(root->left, JourneyCode, price);
	}
	else {
	
		if( root->left == NULL && root->right == NULL){
		
			root = NULL;
		}
		else if(  root->left == NULL){
		
			root = root->right;
		}
		else if( root->right == NULL ){
		
			root = root->left;

		}
		else {
		
			struct TreeNode* a = min2(root->right);
			
			root->price = a->price;
			root->JourneyCode = a->JourneyCode;
			root->right = remove2(root->right, a->JourneyCode, a->price);
		}
	}
	
	return root;
}
			
		
bool BST::remove(int JourneyCode, int price)// removes the element from the tree
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
  bool found = find2(root, JourneyCode, price);
	
	if(found == false ){
	
		return false;
		
	}
	else{
	
		root=remove2(root, JourneyCode, price);
		root->shortestPathLength = minimum(root);
		root->longestPathLength = maximum(root);
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


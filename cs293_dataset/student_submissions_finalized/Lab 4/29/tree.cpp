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

	// when root is empty
	if(root == nullptr){
		root = new TreeNode(JourneyCode,price,nullptr,nullptr,nullptr);
		root->shortestPathLength = 0;
		root->longestPathLength = 0;
		return true;
	}

	// root is not empty
	struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;
	int iteration = 0;
	// check for currect place
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
		iteration ++;
	}

	// is Journeycode is not found then
	currNode = new TreeNode(JourneyCode,price,nullptr,nullptr,parentOfCurrNode);
	if (iteration < root-> shortestPathLength ) root->shortestPathLength = iteration;
	if (iteration > root-> longestPathLength ) root->longestPathLength = iteration;
	if(parentOfCurrNode->JourneyCode < JourneyCode) parentOfCurrNode->right = currNode;
	else parentOfCurrNode->left = currNode;
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
bool BST::find(int JourneyCode, int price){
	if (root == NULL) return false;
	if(root->JourneyCode == JourneyCode && root->price == price) return true;
	else if (root->JourneyCode > JourneyCode && root->left != NULL){ // if price is less than root then
		return BST(root->left).find(JourneyCode, price);
	}
	else if (root->price <= price && root->right != NULL){ // otherwise check in right part of its
		return BST(root->left).find(JourneyCode, price);
	}
	return false;
}
	
// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if (root->JourneyCode == JourneyCode && root->price == price){
		if(root->left == nullptr){
			if(root->right == nullptr){
				if(root->parent == nullptr);
				else if(root->parent->left == root) root->parent->left = nullptr;
				else root->parent->right = nullptr;
				root = nullptr;
			}
			else{
				if(root->parent == nullptr){
					root = root->right;
					root->parent = nullptr;
				}
				else{
					if(root->parent->left == root) root->parent->left = root->right;
					else root->parent->right = root->right;
					root->right->parent = root->parent;
				}
			}
		}
		else{
			TreeNode * pre = root->left;
			while(pre != nullptr) pre = pre->right;
			if(pre->parent->left == pre) pre->parent->left = pre->left;
			else pre->parent->right = pre->left;
			if(pre->left != nullptr) pre->left->parent = pre->parent;
		}
		return true;
    }
    else if (root->JourneyCode > JourneyCode && root->left != NULL){
        return BST(root->left).remove(JourneyCode, price);
    }
    else if (root->right != NULL){
        return BST(root->right).remove(JourneyCode, price);
    }
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

